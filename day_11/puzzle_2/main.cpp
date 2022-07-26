#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

unsigned int find_amount_of_adjacent_occupied_seats(int row_id, int column_id, vector<string> grid) {

    unsigned int amount_of_occupied_seats = 0;

    // Above middle
    while (row_id - 1 > -1) {

        // Check if current space contains an occupied seat
        if (grid[row_id - 1][column_id] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id - 1][column_id] == 'L') {
            break;
        }

        // Decrement row
        row_id--;
    }

    // Below middle
    while (row_id + 1 < grid.size()) {

        // Check if current space contains an occupied seat
        if (grid[row_id + 1][column_id] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id + 1][column_id] == 'L') {
            break;
        }

        // Increment row
        row_id++;
    }

    // Left
    while (column_id - 1 > -1) {

        // Check if current space contains an occupied seat
        if (grid[row_id][column_id - 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id][column_id - 1] == 'L') {
            break;
        }

        // Decrement column
        column_id--;
    }

    // Above left
    while ( row_id - 1 > -1 and
            column_id - 1 > -1) {

        // Check if current space contains an occupied seat
        if (grid[row_id - 1][column_id - 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id - 1][column_id - 1] == 'L') {
            break;
        }

        // Decrement row and column
        row_id--;
        column_id--;
    }

    // Below left
    while ( row_id + 1 < grid.size() and
            column_id - 1 > -1) {

        // Check if current space contains an occupied seat
        if (grid[row_id + 1][column_id - 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id + 1][column_id - 1] == 'L') {
            break;
        }

        // Increment row and decrement column
        row_id++;
        column_id--;
    }

    // Right
    while (column_id + 1 < grid[row_id].size()) {

        // Check if current space contains an occupied seat
        if (grid[row_id][column_id + 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id][column_id + 1] == 'L') {
            break;
        }

        // Increment column
        column_id++;
    }

    // Above right
    while ( row_id - 1 > -1 and
            column_id + 1 < grid[row_id].size()) {

        // Check if current space contains an occupied seat
        if (grid[row_id - 1][column_id + 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id - 1][column_id + 1] == 'L') {
            break;
        }

        // Decrement row and increment column
        row_id--;
        column_id++;
    }

    // Below right
    while ( row_id + 1 < grid.size() and
            column_id + 1 < grid[row_id].size()) {

        // Check if current space contains an occupied seat
        if (grid[row_id + 1][column_id + 1] == '#') {
            amount_of_occupied_seats++;
            break;
        }
        // Check if current space contains an empty seat
        else if (grid[row_id + 1][column_id + 1] == 'L') {
            break;
        }

        // Increment row and column
        row_id++;
        column_id++;
    }

    return amount_of_occupied_seats;
}

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_11.txt", ios::in);

    if (input_file.is_open()) {
        vector<string> grid = {};
        unsigned int amount_of_occupied_seats = 0;
        string line;

        while (getline(input_file, line)) {

            grid.push_back(line);
        }

        // Apply rules
        bool seats_changed = true;
        while (seats_changed) {

            // Set seats changed to false, so loops exits when nothing new happens
            seats_changed = false;

            // Save changes to new grid, so that all spaces are evaluated at the 'same' time
            vector<string> new_grid = grid;

            for (int row = 0; row < grid.size(); row++) {

                for (int column = 0; column < grid[row].size(); column++) {

                    // Get current space
                    char& space = new_grid[row][column];

                    // Check seat status
                    // Floor, thus skip
                    if (space == '.') {
                        continue;
                    }
                    // Empty
                    else if (space == 'L') {
                        // Check if seat becomes occupied
                        if (find_amount_of_adjacent_occupied_seats(row, column, grid) == 0) {
                            seats_changed = true;
                            space = '#';
                        }
                    }
                    // Occupied
                    else if (space == '#') {
                        // Check if seat becomes empty
                        if (find_amount_of_adjacent_occupied_seats(row, column, grid) > 4) {
                            seats_changed = true;
                            space = 'L';
                        }
                    }
                }
            }

            // Update old grid
            grid = new_grid;
        }

        // Count occupied seats
        for (const string& row : grid) {

            for (char space : row) {

                if (space == '#') {
                    amount_of_occupied_seats++;
                }
            }
        }

        // Print result
        cout << "After application of the rules there are: " << amount_of_occupied_seats << " occupied seats.\n";
    }
    input_file.close();

    return 0;
}