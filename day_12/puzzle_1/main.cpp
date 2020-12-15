#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_12.txt", ios::in);

    if (input_file.is_open()) {
        signed int x_pos = 0;
        signed int y_pos = 0;
        int manhattan_distance = 0;
        int directions_length = 4;
        enum directions { north, east, south, west };
        int current_direction = east;
        string line;

        while (getline(input_file, line)) {

            char instruction = line.at(0);
            int amount = stoi(line.substr(1));

            if (instruction == 'N') {
                y_pos += amount;
            }
            else if (instruction == 'S') {
                y_pos -= amount;
            }
            else if (instruction == 'E') {
                x_pos += amount;
            }
            else if (instruction == 'W') {
                x_pos -= amount;
            }
            else if (instruction == 'L') {
                int turns = amount / 90;
                if (current_direction - turns < 0) {
                    current_direction = directions_length + (current_direction - turns);
                }
                else {
                    current_direction -= turns;
                }
            }
            else if (instruction == 'R') {
                int turns = amount / 90;
                if (current_direction + turns >= directions_length) {
                    current_direction = (current_direction + turns) - directions_length;
                }
                else {
                    current_direction += turns;
                }
            }
            else if (instruction == 'F') {
                if (current_direction == north) {
                    y_pos += amount;
                }
                else if (current_direction == south) {
                    y_pos -= amount;
                }
                else if (current_direction == east) {
                    x_pos += amount;
                }
                else if (current_direction == west) {
                    x_pos -= amount;
                }
            }
        }

        // Calculate manhattan distance
        manhattan_distance = abs(x_pos) + abs(y_pos);

        // Print result
        cout << "The manhattan distance from the final position to the origin is: " << manhattan_distance << "\n";
    }
    input_file.close();

    return 0;
}