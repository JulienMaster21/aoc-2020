#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_4.txt", ios::in);

    if (input_file.is_open()) {
        int amount_of_valid_passports = 0;
        string byr;
        string iyr;
        string eyr;
        string hgt;
        string hcl;
        string ecl;
        string pid;
        string cid;
        string line;

        while (getline(input_file, line)) {

            // A blank line indicates a new passport
            if (line.empty()) {
                // If all necessary fields are present, then it is valid
                if (!byr.empty() and
                    !iyr.empty() and
                    !eyr.empty() and
                    !hgt.empty() and
                    !hcl.empty() and
                    !ecl.empty() and
                    !pid.empty()) {
                    amount_of_valid_passports++;
                }

                // Clear passport fields
                byr = "";
                iyr = "";
                eyr = "";
                hgt = "";
                hcl = "";
                ecl = "";
                pid = "";
                cid = "";
            }
            else {
                // Pairs are separated by spaces
                int substring_beginning = 0;
                vector<string> pairs = {};
                for (int char_index = 0; char_index < line.size(); char_index++) {

                    if (line.at(char_index) == ' ') {
                        pairs.push_back(line.substr(substring_beginning, char_index - substring_beginning));
                        substring_beginning = char_index + 1;
                    }
                }
                // Get the last pair
                pairs.push_back(line.substr(substring_beginning));

                // Process pairs
                for (const string& pair : pairs) {

                    int colon = pair.find(':');
                    string key = pair.substr(0, colon);
                    string value = pair.substr(colon + 1);

                    if (key == "byr") {
                        byr = value;
                    }
                    else if (key == "iyr") {
                        iyr = value;
                    }
                    else if (key == "eyr") {
                        eyr = value;
                    }
                    else if (key == "hgt") {
                        hgt = value;
                    }
                    else if (key == "hcl") {
                        hcl = value;
                    }
                    else if (key == "ecl") {
                        ecl = value;
                    }
                    else if (key == "pid") {
                        pid = value;
                    }
                    else if (key == "cid") {
                        cid = value;
                    }
                }
            }
        }
        // Check last passport
        if (!byr.empty() and
            !iyr.empty() and
            !eyr.empty() and
            !hgt.empty() and
            !hcl.empty() and
            !ecl.empty() and
            !pid.empty()) {
            amount_of_valid_passports++;
        }

        // Print result
        cout << "There are " << amount_of_valid_passports << " valid passports.\n";
    }
    input_file.close();

    return 0;
}