#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_13.txt", ios::in);

    if (input_file.is_open()) {
        // The earliest timestamp shouldn't happen earlier than 100000000000000
        unsigned long long earliest_timestamp = 100000000000000;
        map<unsigned int, unsigned int> criteria = {};
        string line;

        // Get criteria
        getline(input_file, line);
        getline(input_file, line);
        unsigned int substring_beginning = 0;
        unsigned int substring_ending = 0;
        unsigned int offset = 0;
        for (int character = 0; character < line.size(); character++) {

            if (line.at(character) == ',') {
                substring_ending = character;
                string bus_id = line.substr(substring_beginning, substring_ending - substring_beginning);
                if (bus_id != "x") {
                    criteria[offset] = stoi(bus_id);
                }
                substring_beginning = character + 1;
                offset++;
            }
        }
        // Get the last bus
        string bus_id = line.substr(substring_beginning, substring_ending - substring_beginning);
        if (bus_id != "x") {
            criteria[offset] = stoi(bus_id);
        }

        // Find the highest increment to speed things up
        unsigned int highest_increment = 1;
        for (pair<signed int, signed int> criterion : criteria) {

            signed int difference = criterion.second - criterion.first;
            if (difference > highest_increment and
                difference > 1) {
                highest_increment = difference;
            }
        }

        // Find earliest bus
        bool searching_for_bus = true;
        bool searching_for_first_highest_increment_occurrence = true;
        while (searching_for_bus) {

            cout << "Checking: " << earliest_timestamp << "\n";

            // Check criteria
            bool meets_criteria = true;
            for (pair<unsigned int, unsigned int> criterion : criteria) {


                if (earliest_timestamp + criterion.first % criterion.second != 0) {
                    meets_criteria = false;
                    break;
                }
            }

            // If timestamp meets criteria then stop, otherwise increment
            if (meets_criteria) {
                searching_for_bus = false;
            }
            else {
                if (searching_for_first_highest_increment_occurrence) {
                    if (earliest_timestamp % highest_increment == 0) {
                        searching_for_first_highest_increment_occurrence = false;
                    }
                    else {
                        earliest_timestamp++;
                    }
                }
                else {
                    earliest_timestamp += highest_increment;
                }
            }
        }

        // Print result
        cout << "The earliest timestamp that matches all the criteria is: " << earliest_timestamp << "\n";
    }
    input_file.close();

    return 0;
}