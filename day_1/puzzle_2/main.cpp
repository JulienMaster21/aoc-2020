#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input.txt", ios::in);
    
    if (input_file.is_open()) {
        
        // Read the numbers from input and put them in an int vector
        string line;
        vector<int> numbers;
        while (getline(input_file, line)) {
            int number = stoi(line);
            numbers.push_back(number);
        }
        input_file.close();
        
        // Check which sum of three numbers is 2020
        int number_1;
        int number_2;
        int number_3;
        for (int first_number = 0; first_number < numbers.size(); ++first_number) {

            for (int second_number = 0; second_number < numbers.size(); ++second_number) {

                for (int third_number = 0; third_number < numbers.size(); ++third_number) {

                    // The numbers need to be different
                    if (first_number == second_number or
                        first_number == third_number or
                        second_number == third_number) {
                        continue;
                    } else {
                        // If the sum of numbers is 2020, then stop searching
                        if (numbers[first_number] + numbers[second_number] + numbers[third_number] == 2020) {
                            number_1 = numbers[first_number];
                            number_2 = numbers[second_number];
                            number_3 = numbers[third_number];
                            goto combination_found;
                        }
                    }
                }
            }
        }

        combination_found: int result = number_1 * number_2 * number_3;
        cout << "The result is " << number_1 << " * " << number_2 << " * " << number_3 << " = " << result << "\n";
    }
}
