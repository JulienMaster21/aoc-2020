#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_10.txt", ios::in);

    if (input_file.is_open()) {
        vector<unsigned int> adapters = {};
        unsigned int one_jolt_differences = 0;
        unsigned int three_jolt_differences = 0;
        unsigned int product_of_differences = 0;
        string line;

        while (getline(input_file, line)) {

            // Add adapter to adapters
            adapters.push_back(stoi(line));
        }

        // Sort adapters
        sort(adapters.begin(), adapters.end());

        // Take charging outlet into account
        unsigned int charging_outlet_difference = adapters[0] - 0;
        if (charging_outlet_difference == 1) {
            one_jolt_differences++;
        }
        else if (charging_outlet_difference == 3) {
            three_jolt_differences++;
        }

        // Count differences
        for (unsigned int adapter = 0; adapter < adapters.size() - 1; adapter++) {

            // Calculate difference
            unsigned int difference = adapters[adapter + 1] - adapters[adapter];

            if (difference == 1) {
                one_jolt_differences++;
            }
            else if (difference == 3) {
                three_jolt_differences++;
            }
        }

        // Take built-in joltage adapter into account
        three_jolt_differences++;

        // Calculate the product
        product_of_differences = one_jolt_differences * three_jolt_differences;

        // Print result
        cout << "The one jolt differences multiplied by the three jolt differences are: " <<
        one_jolt_differences << " * " << three_jolt_differences << " = " << product_of_differences << "\n";
    }
    input_file.close();

    return 0;
}