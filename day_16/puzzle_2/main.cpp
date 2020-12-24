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
        vector<vector<unsigned int>> valid_tickets = {};
        vector<unsigned int> my_ticket = {};
        enum processes { fields, own_ticket, nearby_tickets };
        int currently_processing = fields;
        uint64_t product_of_departure_fields = 1;
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
                // Skip the header
                if (line == "your ticket:") {
                    continue;
                }

                // Get values
                size_t substring_start = 0;
                for (unsigned int index = 0; index < line.size(); index++) {

                    char character = line.at(index);

                    if (character == ',') {
                        my_ticket.push_back(stoi(line.substr(substring_start, index)));
                        substring_start = index + 1;
                    }
                }
                // Get last value
                my_ticket.push_back(stoi(line.substr(substring_start)));
            }
            else if (currently_processing == nearby_tickets) {
                // Skip the header
                if (line == "nearby tickets:") {
                    continue;
                }

                bool ticket_is_valid = true;
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

                    // Check if ticket is valid by checking if the field is not valid for any range
                    if (amount_of_valid_ranges < 1) {
                        ticket_is_valid = false;
                    }
                }

                // If ticket is valid then add it to valid tickets
                if (ticket_is_valid) {
                    valid_tickets.push_back(ticket_fields);
                }
            }
        }

        // Define map for all the valid fields for each range
        map<string, vector<unsigned int>> valid_fields_for_ranges = {};
        for (pair<string, vector<unsigned int>> range : ranges) {

            valid_fields_for_ranges.insert(pair<string, vector<unsigned int>>(range.first, {}));
        }

        // Find all the valid fields for each range
        size_t amount_of_fields = valid_tickets[0].size();
        for (pair<string, vector<unsigned int>> range : ranges) {

            // Define range
            unsigned int first_minimum = range.second[0];
            unsigned int first_maximum = range.second[1];
            unsigned int second_minimum = range.second[2];
            unsigned int second_maximum = range.second[3];

            for (unsigned int field = 0; field < amount_of_fields; field++) {

                bool all_values_fit_in_range = true;

                // Check nearby tickets
                for (vector<unsigned int> ticket : valid_tickets) {
                    unsigned int current_value = ticket[field];
                    if (current_value < first_minimum or
                       (current_value > first_maximum and
                        current_value < second_minimum) or
                        current_value > second_maximum) {
                        all_values_fit_in_range = false;
                    }
                }

                if (all_values_fit_in_range) {
                    valid_fields_for_ranges.at(range.first).push_back(field);
                }
            }
        }

        // Find field order
        string field_order[20];
        vector<unsigned int> taken_fields = {};
        for (unsigned int current_size = 1; current_size <= amount_of_fields; current_size++) {

            for (pair<string, vector<unsigned int>> range : valid_fields_for_ranges) {

                if (range.second.size() == current_size) {
                    for (unsigned int field : range.second) {

                        bool is_correct_field = true;
                        for (unsigned int taken_field : taken_fields) {

                            if (taken_field == field) {
                                is_correct_field = false;
                            }
                        }

                        if (is_correct_field) {
                            taken_fields.push_back(field);
                            field_order[field] = range.first;
                        }
                    }
                }
            }
        }

        // Get departure fields on my ticket
        for (unsigned int field = 0; field < size(field_order); field++) {
            string field_name = field_order[field];
            if (field_name.starts_with("departure")) {
                product_of_departure_fields *= my_ticket[field];
            }
        }

        // Print result
        cout << "The product of the departure fields on my ticket is: " << product_of_departure_fields << "\n";
    }
    input_file.close();

    return 0;
}