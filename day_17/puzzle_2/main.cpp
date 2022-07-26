#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_17.txt", ios::in);

    if (input_file.is_open()) {

        string line;
        while (getline(input_file, line)) {


        }

        // Print result
        cout << ": " <<  << "\n";
    }
    input_file.close();

    return 0;
}