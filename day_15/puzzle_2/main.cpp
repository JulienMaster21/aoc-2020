#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {

    // Define variables
    vector<unsigned int> input = { 0, 1, 5, 10, 3, 12, 19 };
    unsigned int turn_number = 1;
    unsigned int second_to_last_number_spoken = 0;
    unsigned int last_number_spoken = 0;
    map<unsigned int, unsigned int> last_occurrence_of_number = {};

    // Read starting numbers
    for (unsigned int starting_number : input) {

        if (turn_number != 1) {
            second_to_last_number_spoken = last_number_spoken;
            try {
                last_occurrence_of_number.at(second_to_last_number_spoken) = turn_number - 1;
            }
            catch (out_of_range& e) {
                last_occurrence_of_number.insert(pair<unsigned int, unsigned int>(second_to_last_number_spoken,
                                                                                  turn_number - 1));
            }
        }

        // Save occurrence of number
        last_number_spoken = starting_number;

        // Increment turn
        turn_number++;
    }

    // Play until turn 2021, so we can print the 2020th word
    while (turn_number < 30000001) {

        // Save second to last number
        second_to_last_number_spoken = last_number_spoken;

        try {
            int previous_turn = turn_number - 1;
            int difference = previous_turn - last_occurrence_of_number.at(last_number_spoken);
            last_number_spoken = difference;
        }
        catch (out_of_range& e) {
            last_number_spoken = 0;
            last_occurrence_of_number.insert(pair<unsigned int, unsigned int>(0, turn_number));
        }

        // Add second to last number to last occurrence of number
        try {
            last_occurrence_of_number.at(second_to_last_number_spoken) = turn_number - 1;
        }
        catch (out_of_range& e) {
            last_occurrence_of_number.insert(pair<unsigned int, unsigned int>(second_to_last_number_spoken,
                                                                              turn_number - 1));
        }

        // Increment turn
        turn_number++;
    }

    // Print result
    cout << "The 30000000th number spoken is: " << last_number_spoken << "\n";

    return 0;
}