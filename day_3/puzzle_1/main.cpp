#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_3.txt", ios::in);

    if (input_file.is_open()) {
        string line;
        int x_position = 0;
        int amount_of_trees = 0;

        while (getline(input_file, line)) {

            // Check if the current position has a tree
            int position_in_repeated_sequence = x_position % line.size();
            char current_character = line.at(position_in_repeated_sequence);
            if (current_character == '#') {
                amount_of_trees++;
            }

            // increment x_position
            x_position += 3;
        }

        // Print result
        cout << "There are " << amount_of_trees << " trees encountered on the way.\n";
    }
    input_file.close();

    return 0;
}