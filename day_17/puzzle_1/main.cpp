#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Cube {

public:
    signed int x_pos;
    signed int y_pos;
    signed int z_pos;

    Cube(signed int x_pos,
         signed int y_pos,
         signed int z_pos) {

        this->x_pos = x_pos;
        this->y_pos = y_pos;
        this->z_pos = z_pos;
    }
};

int find_cube(  unsigned int x_pos,
                unsigned int y_pos,
                unsigned int z_pos,
                const vector<Cube>& cubes) {

    int cube_index = -1;

    for (int index = 0; index < cubes.size(); index++) {

        Cube cube = cubes.at(index);
        if (cube.x_pos == x_pos and
            cube.y_pos == y_pos and
            cube.z_pos == z_pos) {
            cube_index = index;
        }
    }

    return cube_index;
}

unsigned int find_active_neighbours(int x_pos, int y_pos, int z_pos, const vector<Cube>& cubes) {

    unsigned int amount_of_active_neighbours = 0;

    for (int current_z_pos = z_pos - 1; current_z_pos < z_pos + 2; current_z_pos++) {

        for (int current_y_pos = y_pos - 1; current_y_pos < y_pos + 2; current_y_pos++) {

            for (int current_x_pos = x_pos - 1; current_x_pos < x_pos + 2; current_x_pos++) {

                if (find_cube(current_x_pos,
                              current_y_pos,
                              current_z_pos,
                              cubes)
                              > -1)
                amount_of_active_neighbours++;
            }
        }
    }

    return amount_of_active_neighbours;
}

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_17.txt", ios::in);

    if (input_file.is_open()) {

        vector<Cube> active_cubes = {};
        unsigned int amount_of_active_cubes;
        int initial_y_pos = 0;
        int x_start_bound;
        int x_end_bound;
        int y_start_bound;
        int y_end_bound;
        int z_start_bound;
        int z_end_bound;
        string line;
        while (getline(input_file, line)) {

            for (int index = 0; index < line.size(); index++) {

                // Assume that starting cubes are on a 2D plane
                char character = line.at(index);
                if (character == '#') {
                    Cube cube = Cube(index, initial_y_pos, 0);
                    active_cubes.push_back(cube);
                }
            }

            // Increment y position
            initial_y_pos++;
        }

        // Simulate six cycles
        for (unsigned int cycle = 0; cycle < 6; cycle++) {

            // Update bounds
            for (Cube cube : active_cubes) {

                if (cube.x_pos - 1 < x_start_bound) {
                    x_start_bound = cube.x_pos - 1;
                }
                if (cube.x_pos + 1 > x_end_bound) {
                    x_end_bound = cube.x_pos + 1;
                }

                if (cube.y_pos - 1 < y_start_bound) {
                    y_start_bound = cube.y_pos - 1;
                }
                if (cube.y_pos + 1 > y_end_bound) {
                    y_end_bound = cube.y_pos + 1;
                }

                if (cube.z_pos - 1 < z_start_bound) {
                    z_start_bound = cube.z_pos - 1;
                }
                if (cube.z_pos + 1 > z_end_bound) {
                    z_end_bound = cube.z_pos + 1;
                }
            }

            // Iterate through all of the cubes within the bounds
            vector<Cube> new_active_cubes = {};
            for (int current_z_pos = z_start_bound; current_z_pos < z_end_bound + 1; current_z_pos++) {

                for (int current_y_pos = y_start_bound; current_y_pos < y_end_bound + 1; current_y_pos++) {

                    for (int current_x_pos = x_start_bound; current_x_pos < x_end_bound + 1; current_x_pos++) {

                        // Check conditions
                        bool is_active = find_cube(current_x_pos,
                                                   current_y_pos,
                                                   current_z_pos,
                                                   active_cubes
                                                   ) > -1;
                        unsigned int amount_of_active_neighbours = find_active_neighbours(current_x_pos,
                                                                                          current_y_pos,
                                                                                          current_z_pos,
                                                                                          active_cubes);
                        if (is_active and
                            (amount_of_active_neighbours == 2 or
                            amount_of_active_neighbours == 3)) {
                            new_active_cubes.emplace_back(current_x_pos, current_y_pos, current_z_pos);
                        }

                        if (!is_active and
                            amount_of_active_neighbours == 3) {
                            new_active_cubes.emplace_back(current_x_pos, current_y_pos, current_z_pos);
                        }
                    }
                }
            }

            // Update active cubes
            active_cubes = new_active_cubes;
        }

        // Get final amount of active cubes
        amount_of_active_cubes = active_cubes.size();

        // Print result
        cout << "The amount of active cubes after the sixth cycle is: " << amount_of_active_cubes << "\n";
    }
    input_file.close();

    return 0;
}