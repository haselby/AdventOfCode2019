// Day5App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <cstdio>
#include <iostream>
using namespace std;


struct Instruction_decoder {
    Instruction_decoder(int myInstruction) {
        instruction = myInstruction;
        set_opcode();
        set_num_parameters();
        set_parameter_mode();
    };
    int instruction;
    int opcode;
    int num_parameters;
    bool parameter1_isImmediate;
    bool parameter2_isImmediate;
    bool parameter3_isImmediate;

    int getDigit(int n, int position) {
        return (n % (int)pow(10, position) - (n % (int)pow(10, position - 1))) / (int)pow(10, position - 1);
    }

    void set_opcode() {
        opcode = (getDigit(instruction, 2) * 10) + getDigit(instruction, 1);
    }
    void set_num_parameters() {
        if (opcode == 1) num_parameters = 3;
        else if (opcode == 2) num_parameters = 3;
        else if (opcode == 3) num_parameters = 1;
        else if (opcode == 4) num_parameters = 1;
    }

    void set_parameter_mode() {
        parameter1_isImmediate = (getDigit(instruction, 3) == 1);
        parameter2_isImmediate = (getDigit(instruction, 4) == 1);
        parameter3_isImmediate = (getDigit(instruction, 5) == 1);       
    }
};

void setup_trial(int* puzzle, const int* input, const int n_input, int noun, int verb) {
    for (size_t i = 0; i < n_input; i++) {
        puzzle[i] = input[i];
    }
    puzzle[1] = noun;
    puzzle[2] = verb;
}

void compute(int* array_ptr, size_t array_length, int instruction_pointer) {
    int a{};
    int b{};
    int c{};
    int index_a{};
    int index_b{};
    int index_c{};
    int progIn{};
    int progOut{};
    
    if (array_ptr[instruction_pointer] == 1) {
        index_a = array_ptr[instruction_pointer + 1];
        index_b = array_ptr[instruction_pointer + 2];
        index_c = array_ptr[instruction_pointer + 3];
        a = array_ptr[index_a];
        b = array_ptr[index_b];
        c = a + b;
        array_ptr[index_c] = c;
        compute(array_ptr, array_length, instruction_pointer + 4);
    }
    else if (array_ptr[instruction_pointer] == 2) {
        index_a = array_ptr[instruction_pointer + 1];
        index_b = array_ptr[instruction_pointer + 2];
        index_c = array_ptr[instruction_pointer + 3];
        a = array_ptr[index_a];
        b = array_ptr[index_b];
        c = a * b;
        array_ptr[index_c] = c;
        compute(array_ptr, array_length, instruction_pointer + 4);

    }
    else if (array_ptr[instruction_pointer] == 3) {
        index_a = array_ptr[instruction_pointer + 1];
        cout << "Request for Input" << endl;
        cin >> progIn;
        array_ptr[index_a] = progIn;
        compute(array_ptr, array_length, instruction_pointer + 2);

    }
    else if (array_ptr[instruction_pointer] == 4) {
        index_a = array_ptr[instruction_pointer + 1];
        cout << "Ouput: " << std::endl;
        cout << array_ptr[index_a] << std::endl;
        compute(array_ptr, array_length, instruction_pointer + 2);

    }
    else if (array_ptr[instruction_pointer] == 99) {
        printf("Opt Code 99 Executed\n");
        printf("Result: %d\n", array_ptr[0]);
        return;
    }
    else {
        printf("Danger Will Robinson. Abort. Abort\n");
        return;
    }

}

int main()
{
    //TODO: Add support for immediate mode

    //Next three lines input from Day2App Part 1
    int puzzleInput[] = { 1, 0, 0, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 9, 1, 19, 1, 19, 5, 23, 1, 23, 5, 27, 2, 27, 10, 31, 1, 31, 9, 35, 1, 35, 5, 39, 1, 6, 39, 43, 2, 9, 43, 47, 1, 5, 47, 51, 2, 6, 51, 55, 1, 5, 55, 59, 2, 10, 59, 63, 1, 63, 6, 67, 2, 67, 6, 71, 2, 10, 71, 75, 1, 6, 75, 79, 2, 79, 9, 83, 1, 83, 5, 87, 1, 87, 9, 91, 1, 91, 9, 95, 1, 10, 95, 99, 1, 99, 13, 103, 2, 6, 103, 107, 1, 107, 5, 111, 1, 6, 111, 115, 1, 9, 115, 119, 1, 119, 9, 123, 2, 123, 10, 127, 1, 6, 127, 131, 2, 131, 13, 135, 1, 13, 135, 139, 1, 9, 139, 143, 1, 9, 143, 147, 1, 147, 13, 151, 1, 151, 9, 155, 1, 155, 13, 159, 1, 6, 159, 163, 1, 13, 163, 167, 1, 2, 167, 171, 1, 171, 13, 0, 99, 2, 0, 14, 0 };
    puzzleInput[1] = 12;
    puzzleInput[2] = 2;
    //int puzzleInput[] = {3,0,4,0,99};
    
    const int n_input = (sizeof(puzzleInput) / sizeof(puzzleInput[0]));
  
    compute(puzzleInput, n_input, 0);

    //Test area
    int myInstr = 10102;
    Instruction_decoder myTestInstruction(myInstr);
    cout << "My instruction is: " << myInstr << endl;
    cout << "My opcode is: " << myTestInstruction.opcode << endl;
    cout << "My number of parameters is: " << myTestInstruction.num_parameters << endl;
    cout << "parameters 1 is intermediate: " << myTestInstruction.parameter1_isImmediate << endl;
    cout << "parameters 2 is intermediate: " << myTestInstruction.parameter2_isImmediate << endl;
    cout << "parameters 3 is intermediate: " << myTestInstruction.parameter3_isImmediate << endl;
}
