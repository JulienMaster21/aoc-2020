#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_5.txt", ios::in);

    if (input_file.is_open()) {
        vector<int> seats = {};
        int my_seat = 0;
        int seat_id = 0;
        int minimum_row = 0;
        int maximum_row = 127;
        int row = 0;
        int minimum_col = 0;
        int maximum_col = 7;
        int column = 0;
        string line;

        while (getline(input_file, line)) {

            // Get seat row
            for (int row_index = 0; row_index < 7; row_index++) {

                // Get the range between minimum and maximum row
                int range = maximum_row - minimum_row + 1;

                // Reduce range by half
                if (line.at(row_index) == 'F') {
                    maximum_row = maximum_row - (range / 2);
                }
                else if (line.at(row_index) == 'B') {
                    minimum_row = minimum_row + (range / 2);
                }
            }
            if (minimum_row == maximum_row) {
                row = minimum_row;
            }

            // Get seat column
            for (int col_index = 7; col_index < 10; col_index++) {

                // Get the range between minimum and maximum column
                int range = maximum_col - minimum_col + 1;

                // Reduce range by half
                if (line.at(col_index) == 'L') {
                    maximum_col = maximum_col - (range / 2);
                }
                else if (line.at(col_index) == 'R') {
                    minimum_col = minimum_col + (range / 2);
                }
            }
            if (minimum_col == maximum_col) {
                column = minimum_col;
            }

            // Calculate seat ID
            seat_id = (row * 8) + column;
            seats.push_back(seat_id);

            // Reset values
            seat_id = 0;
            minimum_row = 0;
            maximum_row = 127;
            row = 0;
            minimum_col = 0;
            maximum_col = 7;
            column = 0;
        }

        // Sort seats
        sort(seats.begin(), seats.end());

        // The maximum amount of seats is 127 * 8 + 7 = 1023
        for (int current_seat = 0; current_seat < 1024; current_seat++) {

            // Find an empty seat where the previous and next seat are filled
            bool current_seat_is_filled = binary_search(seats.begin(), seats.end(), current_seat);
            if (!current_seat_is_filled) {
                bool previous_seat_is_filled = binary_search(seats.begin(), seats.end(), current_seat - 1);
                bool next_seat_is_filled = binary_search(seats.begin(), seats.end(), current_seat + 1);
                if (previous_seat_is_filled and
                    next_seat_is_filled) {
                    my_seat = current_seat;
                    break;
                }
            }
        }

        // Print result
        cout << "The id of my seat is: " << my_seat << "\n";
    }
    input_file.close();

    return 0;
}