#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

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
                // Check if all fields are present and valid
                if (!byr.empty() and
                    // byr needs to be a 4 digit number between 1920 and 2002
                    regex_match(byr, regex("^19[2-9]\\d|^200[0-2]$")) and
                    !iyr.empty() and
                    // iyr needs to be a 4 digit number between 2010 and 2020
                    regex_match(iyr, regex("^201\\d|2020$")) and
                    !eyr.empty() and
                    // eyr needs to be a 4 digit number between 2020 and 2030
                    regex_match(eyr, regex("^202\\d|2030$")) and
                    !hgt.empty() and
                    // hgt needs to be a number followed by either cm or in
                    // if cm, then between 150 and 193
                    // if in, then between 59 and 76
                    regex_match(hgt, regex("^1[5-8]\\dcm|19[0-3]cm|59in|6\\din|7[0-6]in$")) and
                    !hcl.empty() and
                    // hcl is a hex code, so a # and six characters which can be 1-9 or a-f
                    regex_match(hcl, regex("^#[\\da-f]{6}$")) and
                    !ecl.empty() and
                    // ecl is a 3 character code, these are the valid codes: amb, blu, brn, gry, grn, hzl, or oth
                    regex_match(ecl, regex("^amb|blu|brn|gry|grn|hzl|oth$")) and
                    !pid.empty() and
                    // pid is a 9 digit number with leading zeros
                    regex_match(pid, regex("^\\d{9}$"))) {
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
        // Check if all fields are present and valid
        if (!byr.empty() and
            // byr needs to be a 4 digit number between 1920 and 2002
            regex_match(byr, regex("^19[2-9]\\d|^200[0-2]$")) and
            !iyr.empty() and
            // iyr needs to be a 4 digit number between 2010 and 2020
            regex_match(iyr, regex("^201\\d|2020$")) and
            !eyr.empty() and
            // eyr needs to be a 4 digit number between 2020 and 2030
            regex_match(eyr, regex("^202\\d|2030$")) and
            !hgt.empty() and
            // hgt needs to be a number followed by either cm or in
            // if cm, then between 150 and 193
            // if in, then between 59 and 76
            regex_match(hgt, regex("^1[5-8]\\dcm|19[0-3]cm|59in|6\\din|7[0-6]in$")) and
            !hcl.empty() and
            // hcl is a hex code, so a # and six characters which can be 1-9 or a-f
            regex_match(hcl, regex("^#[\\da-f]{6}$")) and
            !ecl.empty() and
            // ecl is a 3 character code, these are the valid codes: amb, blu, brn, gry, grn, hzl, or oth
            regex_match(ecl, regex("^amb|blu|brn|gry|grn|hzl|oth$")) and
            !pid.empty() and
            // pid is a 9 digit number with leading zeros
            regex_match(pid, regex("^\\d{9}$"))) {
            amount_of_valid_passports++;
        }

        // Print result
        cout << "There are " << amount_of_valid_passports << " valid passports.\n";
    }
    input_file.close();

    return 0;
}