#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Instruction {
    public:
    unsigned int id;
    string operation;
    signed int argument;
    unsigned int times_executed;

    Instruction(unsigned int id,
                string operation,
                signed int argument) {

        this->id = id;
        this->operation = move(operation);
        this->argument = argument;
        this->times_executed = 0;
    }

    /**
     *
     * @param accumulator
     * @param instructions
     * @return id of next instruction or a negative exit code, -1 normal exit, -2 infinite loop, -3 other exception
     */
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
            else {
                return -1;
            }
        }
        else if (operation == "acc") {
            accumulator += argument;
            if (instructions.size() > id + 1) {
                return id + 1;
            }
            else {
                return -1;
            }
        }
        else if (operation == "jmp") {
            if (instructions.size() > id + argument and
                0 <= id + argument) {
                return id + argument;
            }
            else if (0 <= id + argument) {
                return -1;
            }
        }

        // Unknown exception
        return -3;
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
            Instruction instruction = Instruction(id, operation, argument);
            instructions.push_back(instruction);

            // Increment id
            id++;
        }

        // Try instructions until program terminates
        for (int instruction_id = 0; instruction_id < instructions.size(); instruction_id++) {

            // Make a modified copy of instructions
            vector<Instruction> modified_instructions;
            copy(instructions.begin(), instructions.end(), back_inserter(modified_instructions));
            if (instructions[instruction_id].operation == "nop") {
                modified_instructions[instruction_id].operation = "jmp";
            }
            else if (instructions[instruction_id].operation == "jmp") {
                modified_instructions[instruction_id].operation = "nop";
            }
            // Acc instructions aren't corrupted, so skip them
            else if (instructions[instruction_id].operation == "acc") {
                continue;
            }

            // Run program
            accumulator = 0;
            int execution_result = 0;
            while (execution_result > -1) {

                execution_result = modified_instructions[execution_result].execute(accumulator, modified_instructions);
            }

            // Check if program terminated
            if (execution_result == -1) {
                break;
            }
        }

        // Print result
        cout << "The value of the accumulator after program termination is: " << accumulator << "\n";
    }
    input_file.close();

    return 0;
}