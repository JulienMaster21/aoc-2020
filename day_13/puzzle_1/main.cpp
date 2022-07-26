#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_13.txt", ios::in);

    if (input_file.is_open()) {
        unsigned int estimate = 0;
        unsigned int departure = 0;
        vector<unsigned int> bus_ids = {};
        unsigned int earliest_bus = 0;
        string line;

        // Get estimate
        getline(input_file, line);
        estimate = stoi(line);

        // Get bus IDs
        getline(input_file, line);
        unsigned int substring_beginning = 0;
        unsigned int substring_ending = 0;
        for (int character = 0; character < line.size(); character++) {

            if (line.at(character) == ',') {
                substring_ending = character;
                string bus_id = line.substr(substring_beginning, substring_ending - substring_beginning);
                if (bus_id != "x") {
                    bus_ids.push_back(stoi(bus_id));
                }
                substring_beginning = character + 1;
            }
        }
        // Get the last bus
        string bus_id = line.substr(substring_beginning, substring_ending - substring_beginning);
        if (bus_id != "x") {
            bus_ids.push_back(stoi(bus_id));
        }

        // Find earliest bus
        bool searching_for_bus = true;
        departure = estimate;
        while (searching_for_bus) {

            // Check if a bus arrived
            for (unsigned int bus : bus_ids) {

                if (departure % bus == 0) {
                    searching_for_bus = false;
                    earliest_bus = bus;
                }
            }

            if (searching_for_bus) {
                // Increment departure
                departure++;
            }
        }

        // Calculate result
        unsigned int wait_time = departure - estimate;
        unsigned int result = earliest_bus * wait_time;

        // Print result
        cout << "The ID of the earliest bus multiplied by the wait time is: " << earliest_bus << " * " << wait_time
            << " = " << result << "\n";
    }
    input_file.close();

    return 0;
}