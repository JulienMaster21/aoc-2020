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

vector<string> find_amount_of_bags_that_can_contain(const string& bag_name, const vector<Bag>& bags) {

    vector<string> all_bags = {};

    // Get all bags
    for (Bag bag : bags) {

        if (bag.can_contain_directly(bag_name) > 0) {
            all_bags.push_back(bag.name);

            for (const string& new_bag : find_amount_of_bags_that_can_contain(bag.name, bags)) {
                all_bags.push_back(new_bag);
            }
        }
    }

    // Remove duplicates
    sort(all_bags.begin(), all_bags.end());
    vector<string>::iterator it;
    it = unique(all_bags.begin(), all_bags.end());
    all_bags.resize(distance(all_bags.begin(), it));

    return all_bags;
}

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_7.txt", ios::in);

    if (input_file.is_open()) {
        vector<Bag> bags = {};
        vector<string> bags_that_can_contain_shiny_gold_bag = {};
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

        // Check recursively which bags can contain a shiny gold bag
        bags_that_can_contain_shiny_gold_bag = find_amount_of_bags_that_can_contain("shiny gold", bags);

        // Print result
        cout << "The amount of bags that can contain a shiny gold bag is: " <<
                bags_that_can_contain_shiny_gold_bag.size() << "\n";
    }
    input_file.close();

    return 0;
}