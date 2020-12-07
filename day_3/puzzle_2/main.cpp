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
        int line_index = 0;
        int x_positions[] = { 0, 0, 0, 0, 0 };
        int amounts_of_trees[] = { 0, 0, 0, 0, 0 };

        while (getline(input_file, line)) {

            // Check if a tree would be encountered for every slope
            for (int index = 0; index < (sizeof(x_positions) / sizeof(x_positions[0])); index++) {
                int position_in_repeated_sequence = x_positions[index] % line.size();
                char current_character = line.at(position_in_repeated_sequence);
                if (current_character == '#') {
                    // Check if line index is even for slope 5
                    if (line_index % 2 == 0 or
                        index != 4)
                    amounts_of_trees[index]++;
                }
            }

            // Increment line index
            line_index += 1;

            // increment x_position
            x_positions[0] += 1;
            x_positions[1] += 3;
            x_positions[2] += 5;
            x_positions[3] += 7;
            x_positions[4] += 1;
        }

        // Print result
        int product_of_amounts_of_trees = 1;
        for (int slope : amounts_of_trees) {
            product_of_amounts_of_trees *= slope;
        }
        cout << "The product of the amount of trees is " << amounts_of_trees[0] << " * " << amounts_of_trees[1]
        << " * " << amounts_of_trees[2] << " * " << amounts_of_trees[3] << " * " << amounts_of_trees[4] << " = "
        << product_of_amounts_of_trees << " trees encountered on the way.\n";
    }
    input_file.close();

    return 0;
}