#include <iostream>
#include <fstream>
#include <string>
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
                string value_bitstring = bitset<36>(value).to_string();
                for (unsigned int bit = 0; bit < bitmask.size(); bit++) {
                    if (bitmask[bit] != 'X') {
                        value_bitstring[bit] = bitmask[bit];
                    }
                }
                value = bitset<36>(value_bitstring).to_ullong();

                // Save value to address
                try {

                    memory.at(address) = value;
                }
                catch (out_of_range& e) {

                    memory.insert(pair<uint64_t, uint64_t>(address, value));
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