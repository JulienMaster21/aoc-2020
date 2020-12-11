#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Instruction {
    public:
    unsigned int id;
    string operation;
    signed int argument;
    unsigned int times_executed;

    Instruction() {

        this->id = id;
        this->operation = move(operation);
        this->argument = argument;
        this->times_executed = 0;
    }

    int execute(unsigned int &accumulator, const vector<Instruction>& instructions) {

        // Increment times executed
        times_executed++;

        // If times executed is 2 or more, stop execution
        if (times_executed >= 2) {
            return -2;
        }

        // Execute dependant on operation
        if (operation == "nop") {
            if (instructions.size() > id + 1) {
                return id + 1;
            }
        }
        else if (operation == "acc") {
            accumulator += argument;
            if (instructions.size() > id + 1) {
                return id + 1;
            }
        }
        else if (operation == "jmp") {
            if (instructions.size() > id + argument) {
                return id + argument;
            }
            else if (0 > id + argument) {
                cout << "A jump instruction tried to jump before the first instruction.\n";
                return -1;
            }
        }

        return -1;
    }
};

int main() {

    // Open the input file
    fstream input_file;
    input_file.open("input_8.txt", ios::in);

    if (input_file.is_open()) {
        vector<Instruction> instructions = {};
        unsigned int id = 0;
        unsigned int accumulator = 0;
        string line;

        while (getline(input_file, line)) {

            // Get program instructions from file
            string operation = line.substr(0, 3);
            signed int argument = stoi(line.substr(4));

            // Add instruction to instructions vector
            Instruction instruction = Instruction();
            instructions.push_back(instruction);

            // Increment id
            id++;
        }

        // Run program
        int next_instruction = 0;
        while (next_instruction > -1) {
            next_instruction = instructions[next_instruction].execute(accumulator, instructions);
        }

        // Print result
        cout << "The value of the accumulator before the infinite loop is: " << accumulator << "\n";
    }
    input_file.close();

    return 0;
}