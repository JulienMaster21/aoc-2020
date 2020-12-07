#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Define amount of valid password
    int amount_of_valid_passwords = 0;

    // Open the input file
    fstream input_file;
    input_file.open("input_2.txt", ios::in);

    if (input_file.is_open()) {
        string line;
        string limit;
        int first;
        int second;
        char filter;
        string password;

        while (getline(input_file, line)) {

            // The needed values are delimited by spaces
            // Line is in the format of: limit filter password
            size_t first_space = line.find(' ');
            size_t second_space = line.find(' ', first_space + 1);
            limit = line.substr(0, first_space);
            filter = line.at(first_space + 1);
            password = line.substr(second_space + 1);

            // Limit consists of first and second delimited by a dash
            size_t first_dash = limit.find('-');
            first = stoi(limit.substr(0, first_dash));
            second = stoi(limit.substr(first_dash + 1));

            // Check if password is valid
            if (password.at(first - 1) == filter xor
                password.at(second - 1) == filter) {
                amount_of_valid_passwords++;
            }
        }
        input_file.close();

        // Print result
        cout << "There are a total of " << amount_of_valid_passwords << " valid passwords.\n";
    }

    return 0;
}