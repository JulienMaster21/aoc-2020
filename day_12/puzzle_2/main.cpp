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
        signed int ship_x_pos = 0;
        signed int ship_y_pos = 0;
        signed int waypoint_x_pos = 10;
        signed int waypoint_y_pos = 1;
        int manhattan_distance = 0;
        string line;

        while (getline(input_file, line)) {

            char instruction = line.at(0);
            int amount = stoi(line.substr(1));

            if (instruction == 'N') {
                waypoint_y_pos += amount;
            }
            else if (instruction == 'S') {
                waypoint_y_pos -= amount;
            }
            else if (instruction == 'E') {
                waypoint_x_pos += amount;
            }
            else if (instruction == 'W') {
                waypoint_x_pos -= amount;
            }
            else if (instruction == 'L') {
                int turns = amount / 90;
                signed int new_x = 0;
                signed int new_y = 0;
                if (turns > 1) {
                    waypoint_x_pos = -1 * waypoint_x_pos;
                    waypoint_y_pos = -1 * waypoint_y_pos;
                }
                if (turns == 1 or
                    turns == 3) {
                    new_x = -1 * waypoint_y_pos;
                    new_y = waypoint_x_pos;
                    waypoint_x_pos = new_x;
                    waypoint_y_pos = new_y;
                }
            }
            else if (instruction == 'R') {
                int turns = amount / 90;
                signed int new_x = 0;
                signed int new_y = 0;
                if (turns > 1) {
                    waypoint_x_pos = -1 * waypoint_x_pos;
                    waypoint_y_pos = -1 * waypoint_y_pos;
                }
                if (turns == 1 or
                    turns == 3) {
                    new_x = waypoint_y_pos;
                    new_y = -1 * waypoint_x_pos;
                    waypoint_x_pos = new_x;
                    waypoint_y_pos = new_y;
                }
            }
            else if (instruction == 'F') {
                for (int move = 0; move < amount; move++) {
                    ship_x_pos += waypoint_x_pos;
                    ship_y_pos += waypoint_y_pos;
                }
            }
        }

        // Calculate manhattan distance
        manhattan_distance = abs(ship_x_pos) + abs(ship_y_pos);

        // Print result
        cout << "The manhattan distance from the final position to the origin is: " << manhattan_distance << "\n";
    }
    input_file.close();

    return 0;
}