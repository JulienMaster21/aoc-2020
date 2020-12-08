#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_6.txt", ios::in);

    if (input_file.is_open()) {
        bool questions[26] = { false, false, false, false, false, false, false, false, false, false,
                               false, false, false, false, false, false, false, false, false, false,
                               false, false, false, false, false, false };
        int total_amount_of_yes = 0;
        string line;

        while (getline(input_file, line)) {

            if (line.empty()) {

                // Get amount 'yes' to questions and reset to false
                int yes_sum = 0;
                for (int question_index = 0; question_index < (sizeof(questions) / sizeof(questions[0])); question_index++) {
                    if (questions[question_index]) {
                        yes_sum++;
                    }
                    questions[question_index] = false;
                }

                // Add amount to total sum
                total_amount_of_yes += yes_sum;
            }
            else {
                for (char character : line) {

                    switch (character) {
                        case 'a':
                            questions[0] = true;
                            break;
                        case 'b':
                            questions[1] = true;
                            break;
                        case 'c':
                            questions[2] = true;
                            break;
                        case 'd':
                            questions[3] = true;
                            break;
                        case 'e':
                            questions[4] = true;
                            break;
                        case 'f':
                            questions[5] = true;
                            break;
                        case 'g':
                            questions[6] = true;
                            break;
                        case 'h':
                            questions[7] = true;
                            break;
                        case 'i':
                            questions[8] = true;
                            break;
                        case 'j':
                            questions[9] = true;
                            break;
                        case 'k':
                            questions[10] = true;
                            break;
                        case 'l':
                            questions[11] = true;
                            break;
                        case 'm':
                            questions[12] = true;
                            break;
                        case 'n':
                            questions[13] = true;
                            break;
                        case 'o':
                            questions[14] = true;
                            break;
                        case 'p':
                            questions[15] = true;
                            break;
                        case 'q':
                            questions[16] = true;
                            break;
                        case 'r':
                            questions[17] = true;
                            break;
                        case 's':
                            questions[18] = true;
                            break;
                        case 't':
                            questions[19] = true;
                            break;
                        case 'u':
                            questions[20] = true;
                            break;
                        case 'v':
                            questions[21] = true;
                            break;
                        case 'w':
                            questions[22] = true;
                            break;
                        case 'x':
                            questions[23] = true;
                            break;
                        case 'y':
                            questions[24] = true;
                            break;
                        case 'z':
                            questions[25] = true;
                            break;
                        default:
                            cout << "Invalid character: " << character << "\n";
                            break;
                    }
                }
            }
        }

        // Check last group
        int yes_sum = 0;
        for (int question_index = 0; question_index < (sizeof(questions) / sizeof(questions[0])); question_index++) {
            if (questions[question_index]) {
                yes_sum++;
            }
            questions[question_index] = false;
        }

        // Add amount to total sum
        total_amount_of_yes += yes_sum;

        // Print result
        cout << "The sum of all yes to questions are: " << total_amount_of_yes << "\n";
    }
    input_file.close();

    return 0;
}