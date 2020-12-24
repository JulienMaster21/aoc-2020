#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_16.txt", ios::in);

    if (input_file.is_open()) {

        string line;
        map<string, vector<unsigned int>> ranges = {};
        enum processes { fields, own_ticket, nearby_tickets };
        int currently_processing = fields;
        unsigned int ticket_scanning_error_rate = 0;
        while (getline(input_file, line)) {

            // Check if current line is a blank line
            if (line.empty()) {
                currently_processing++;
                continue;
            }

            // Process line
            if (currently_processing == fields) {

                // Get field name
                size_t colon_index = line.find(':');
                string field_name = line.substr(0, colon_index);

                // Get ranges
                size_t or_index = line.find(" or ");
                string first_range = line.substr(colon_index + 2, or_index - colon_index - 2);
                size_t first_dash = first_range.find('-');
                unsigned int first_minimum = stoi(first_range.substr(0, first_dash));
                unsigned int first_maximum = stoi(first_range.substr(first_dash + 1));
                string second_range = line.substr(or_index + 4);
                size_t second_dash = second_range.find('-');
                unsigned int second_minimum = stoi(second_range.substr(0, second_dash));
                unsigned int second_maximum = stoi(second_range.substr(second_dash + 1));

                // Add range to ranges
                ranges.insert(pair<string, vector<unsigned int>>(field_name,
                                                               { first_minimum,
                                                                    first_maximum,
                                                                    second_minimum,
                                                                    second_maximum }));
            }
            else if (currently_processing == own_ticket) {
                continue;
            }
            else if (currently_processing == nearby_tickets) {
                // Skip the header
                if (line == "nearby tickets:") {
                    continue;
                }

                vector<unsigned int> ticket_fields = {};

                // Get values
                size_t substring_start = 0;
                for (unsigned int index = 0; index < line.size(); index++) {

                    char character = line.at(index);

                    if (character == ',') {
                        ticket_fields.push_back(stoi(line.substr(substring_start, index)));
                        substring_start = index + 1;
                    }
                }
                // Get last value
                ticket_fields.push_back(stoi(line.substr(substring_start)));

                // Check values
                for (unsigned int field : ticket_fields) {

                    unsigned int amount_of_valid_ranges = 0;
                    unsigned int amount_of_invalid_ranges = 0;

                    for (pair<string, vector<unsigned int>> range : ranges) {

                        // Define range
                        unsigned int first_minimum = range.second[0];
                        unsigned int first_maximum = range.second[1];
                        unsigned int second_minimum = range.second[2];
                        unsigned int second_maximum = range.second[3];

                        if (field < first_minimum or
                            (field > first_maximum and
                            field < second_minimum) or
                            field > second_maximum) {
                            amount_of_invalid_ranges++;
                        }
                        else {
                            amount_of_valid_ranges++;
                        }
                    }

                    // If field is not valid for any range add it to the ticket scanning error rate
                    if (amount_of_valid_ranges < 1) {
                        ticket_scanning_error_rate += field;
                    }
                }
            }
        }

        // Print result
        cout << "The ticket scanning error rate is: " << ticket_scanning_error_rate << "\n";
    }
    input_file.close();

    return 0;
}