#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<unsigned int> find_next_valid_adapters(signed int current_adapter,
                                              const vector<unsigned int>&adapters) {

    vector<unsigned int>valid_adapters = {};

    for (signed int adapter : adapters) {

        signed int difference = adapter - current_adapter;
        if (difference > 0 and
            difference < 4) {
            valid_adapters.push_back(adapter);
        }
    }

    return valid_adapters;
}

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_10.txt", ios::in);

    if (input_file.is_open()) {
        vector<unsigned int> adapters = {};
        unsigned int amount_of_adapter_arrangements = 0;
        signed int outlet_jolt = 0;
        string line;

        while (getline(input_file, line)) {

            // Add adapter to adapters
            adapters.push_back(stoi(line));
        }

        // Sort adapters
        sort(adapters.begin(), adapters.end());

        // Calculate amount of arrangements
        map<signed int, unsigned int> next_adapters;
        for (unsigned int adapter : find_next_valid_adapters(outlet_jolt, adapters)) {
            next_adapters.insert(pair<signed int, unsigned int>(adapter, 1));
        }
        bool calculating_amount_of_arrangements = true;
        while (calculating_amount_of_arrangements) {

            map<signed int, unsigned int> new_next_adapters = {};

            for (pair<const signed int, unsigned int> adapter : next_adapters) {

                for (unsigned int new_adapter : find_next_valid_adapters(adapter.first, adapters)) {

                    if (new_adapter == adapters.back()) {
                        amount_of_adapter_arrangements += adapter.second;
                    }
                    else {
                        try {
                            new_next_adapters.at(new_adapter) += adapter.second;
                        }
                        catch (out_of_range &e) {
                            new_next_adapters.insert(pair<signed int, unsigned int>(new_adapter, adapter.second));
                        }
                    }
                }
            }

            if (new_next_adapters.empty()) {
                calculating_amount_of_arrangements = false;
            }
            else {
                next_adapters = new_next_adapters;
            }
        }

        // Print result
        cout << "There are " << amount_of_adapter_arrangements << " distinct ways to arrange the adapters." << "\n";
    }
    input_file.close();

    return 0;
}