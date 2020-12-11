#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_9.txt", ios::in);

    if (input_file.is_open()) {
        deque<unsigned int> previous_25_numbers = {};
        vector<unsigned int> all_previous_numbers = {};
        unsigned int first_invalid_number = 0;
        string line;

        while (getline(input_file, line)) {

            // Get number from line
            unsigned int number = stoi(line);
            all_previous_numbers.push_back(number);

            // If number is part of preamble only add it
            if (previous_25_numbers.size() < 25) {
                previous_25_numbers.push_back(number);
            }
            else {
                // Check if number is valid
                bool number_is_validated = false;
                for (unsigned int previous_number_1 : previous_25_numbers) {

                    for (unsigned int previous_number_2 : previous_25_numbers) {

                        // The previous numbers need to have different values
                        if (previous_number_1 == previous_number_2) {
                            continue;
                        }

                        // If the sum of both numbers is equal to number, then it is validated
                        if (previous_number_1 + previous_number_2 == number) {
                            number_is_validated = true;
                            goto validation;
                        }
                    }
                }

                // If number isn't valid, then stop
                validation: if (!number_is_validated) {
                    first_invalid_number = number;
                    all_previous_numbers.pop_back();
                    break;
                }

                // Update numbers
                previous_25_numbers.pop_front();
                previous_25_numbers.push_back(number);
            }
        }

        // Find the contiguous set
        vector<unsigned int> contiguous_set;
        for (int previous_number = 0; previous_number < all_previous_numbers.size(); previous_number++) {

            contiguous_set = {};
            unsigned int total = 0;
            unsigned int next_number_to_add = previous_number;
            while (total < first_invalid_number) {

                // Add next number to total
                total += all_previous_numbers[next_number_to_add];
                contiguous_set.push_back(all_previous_numbers[next_number_to_add]);

                // Increment next number
                next_number_to_add++;
            }

            // Check if the correct set is found
            if (total == first_invalid_number) {
                break;
            }
        }

        // Sort the set
        sort(contiguous_set.begin(), contiguous_set.end());

        // Calculate encryption weakness
        unsigned int smallest_value = contiguous_set.front();
        unsigned int largest_value = contiguous_set.back();
        unsigned int encryption_weakness = smallest_value + largest_value;

        // Print result
        cout << "The encryption weakness is: " << encryption_weakness << "\n";
    }
    input_file.close();

    return 0;
}