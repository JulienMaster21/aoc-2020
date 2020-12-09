#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Bag {
    public:
        string name;
        vector<string> can_contain_bags;
        vector<int> can_contain_bags_amounts;

        Bag(string name,
            vector<string> can_contain_bags,
            vector<int> can_contain_bags_amounts) {

            this->name = move(name);
            this->can_contain_bags = move(can_contain_bags);
            this->can_contain_bags_amounts = move(can_contain_bags_amounts);
        }

        int can_contain_directly(const string& bag_name) {

            int found_bag = -1;
            for (int bag_index = 0; bag_index < can_contain_bags.size(); bag_index++) {

                if (can_contain_bags[bag_index] == bag_name) {
                    found_bag = bag_index;
                }
            }

            if (found_bag != -1) {
                return can_contain_bags_amounts[found_bag];
            }
            else {
                return 0;
            }
        }
};

int find_amount_of_bags_needed(const string& bag_name, const vector<Bag>& bags) {

    int needed_bags = 0;
    bool bag_could_be_found = false;

    for (Bag bag : bags) {

        if (bag.name == bag_name and
            !bag.can_contain_bags.empty()) {
            bag_could_be_found = true;

            for (int bag_index = 0; bag_index < bag.can_contain_bags.size(); bag_index++) {
                needed_bags +=  bag.can_contain_bags_amounts[bag_index] +
                                (find_amount_of_bags_needed(bag.can_contain_bags[bag_index], bags) *
                                bag.can_contain_bags_amounts[bag_index]);
            }
            break;
        }
    }

    if (!bag_could_be_found) {
        return 0;
    }

    return needed_bags;
}

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_7.txt", ios::in);

    if (input_file.is_open()) {
        vector<Bag> bags = {};
        int bags_needed_for_a_shiny_gold_bag = 0;
        string line;

        while (getline(input_file, line)) {

            // Construct bag
            string bag_name;
            vector<string> contains_bags = {};
            vector<int> amounts = {};

            int contain_index = line.find("contain");
            bag_name = line.substr(0, contain_index - 6);

            // From 'contain ' until before '.'
            string containing_bags_string = line.substr(contain_index + 8, line.size() - contain_index - 8 - 1);
            if (containing_bags_string != "no other bags") {
                int starting_index = 0;
                int comma_index;
                while ((comma_index = containing_bags_string.find(',', starting_index)) != string::npos) {

                    amounts.push_back(stoi(containing_bags_string.substr(starting_index, 1)));
                    if (amounts[amounts.size() - 1] > 1) {
                        string current_bag = containing_bags_string.substr(starting_index + 2,
                                                                           comma_index - starting_index - 2 - 5);
                        contains_bags.push_back(current_bag);
                    }
                    else {
                        string current_bag = containing_bags_string.substr(starting_index + 2,
                                                                           comma_index - starting_index - 2 - 4);
                        contains_bags.push_back(current_bag);
                    }

                    // Update starting index
                    starting_index = comma_index + 2;
                }

                // Get last bag
                amounts.push_back(stoi(containing_bags_string.substr(starting_index, 1)));
                if (amounts[amounts.size() - 1] > 1) {
                    string current_bag = containing_bags_string.substr(starting_index + 2,
                                                                       containing_bags_string.size() - starting_index - 2 - 5);
                    contains_bags.push_back(current_bag);
                }
                else {
                    string current_bag = containing_bags_string.substr(starting_index + 2,
                                                                       containing_bags_string.size() - starting_index - 2 - 4);
                    contains_bags.push_back(current_bag);
                }
            }

            // Add bag to bags
            Bag bag = Bag(bag_name, contains_bags, amounts);
            bags.push_back(bag);
        }

        // Find out how many bags need to be in a shiny gold bag
        bags_needed_for_a_shiny_gold_bag = find_amount_of_bags_needed("shiny gold", bags);

        // Print result
        cout << "A shiny gold bag needs to contain: " << bags_needed_for_a_shiny_gold_bag << " bags.\n";
    }
    input_file.close();

    return 0;
}