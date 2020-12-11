#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_9.txt", ios::in);

    if (input_file.is_open()) {
        deque<unsigned int> previous_25_numbers = {};
        unsigned int first_invalid_number = 0;
        string line;

        while (getline(input_file, line)) {

            // Get number from line
            unsigned int number = stoi(line);

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
                    break;
                }

                // Update numbers
                previous_25_numbers.pop_front();
                previous_25_numbers.push_back(number);
            }
        }

        // Print result
        cout << "The first invalid number is: " << first_invalid_number << "\n";
    }
    input_file.close();

    return 0;
}