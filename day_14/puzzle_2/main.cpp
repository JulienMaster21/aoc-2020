#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_14.txt", ios::in);

    if (input_file.is_open()) {
        uint64_t sum_of_all_values = 0;
        // The range of a 36 unsigned integer is 0 - 68719476735
        map<uint64_t, uint64_t> memory = {};
        string bitmask;
        string line;

        while (getline(input_file, line)) {

            // Check if new bitmask is defined
            if (line.starts_with("mask = ")) {

                bitmask = line.substr(7);
            }
            else {
                // Get address
                size_t closing_square_bracket = line.find(']');
                uint64_t address = stoi(line.substr(4, closing_square_bracket - 4));

                // Get value
                size_t equal_sign = line.find('=');
                uint64_t value = stoi(line.substr(equal_sign + 1));

                // Apply bitmask
                string address_bitstring = bitset<36>(address).to_string();
                vector<unsigned int> floating_locations = {};
                for (unsigned int bit = 0; bit < bitmask.size(); bit++) {

                    if (bitmask[bit] == 'X') {
                        floating_locations.push_back(bit);
                        address_bitstring[bit] = 'X';
                    }
                    else if (bitmask[bit] == '1') {
                        address_bitstring[bit] = '1';
                    }
                }

                // Get addresses
                vector<uint64_t> addresses = {};
                unsigned int amount_of_addresses = pow(2, floating_locations.size());
                for (unsigned int current_combination = 0; current_combination < amount_of_addresses; current_combination++) {

                    // Turn current combination into binary string
                    string current_address_string = bitset<36>(current_combination).to_string();

                    // Iterate through floating bits
                    string new_address_string = address_bitstring;
                    uint64_t new_address = 0;
                    unsigned int iteration = 0;
                    for (int index = floating_locations.size() - 1; index > -1; index--) {

                        unsigned int location = floating_locations[index];
                        new_address_string[location] = current_address_string[current_address_string.size() - 1 - iteration];
                        iteration++;
                    }

                    // Add new address
                    new_address = bitset<36>(new_address_string).to_ullong();
                    addresses.push_back(new_address);
                }

                // Save value to addresses
                for (uint64_t address : addresses) {
                    try {

                        memory.at(address) = value;
                    }
                    catch (out_of_range &e) {

                        memory.insert(pair<uint64_t, uint64_t>(address, value));
                    }
                }
            }
        }

        // Count the sum of all the values
        for (pair<uint64_t, uint64_t> address : memory) {

            sum_of_all_values += address.second;
        }

        // Print result
        cout << "The sum of all the values left in memory are: " << sum_of_all_values << "\n";
    }
    input_file.close();

    return 0;
}