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
    
    Instruction_decoder* decoder_ptr = new Instruction_decoder(array_ptr[instruction_pointer]);
    
    int a{};
    int b{};
    int c{};
    int index_a{};
    int index_b{};
    int index_c{};
    int progIn{};
    int progOut{};
    
    if (decoder_ptr->opcode == 1) {
        index_a = array_ptr[instruction_pointer + 1];
        index_b = array_ptr[instruction_pointer + 2];
        index_c = array_ptr[instruction_pointer + 3];
        a = decoder_ptr->parameter1_isImmediate ? index_a :array_ptr[index_a];
        b = decoder_ptr->parameter2_isImmediate ? index_b :array_ptr[index_b];
        c = a + b;
        array_ptr[index_c] = c;
        compute(array_ptr, array_length, instruction_pointer + 4);
    }
    else if (decoder_ptr->opcode == 2) {
        index_a = array_ptr[instruction_pointer + 1];
        index_b = array_ptr[instruction_pointer + 2];
        index_c = array_ptr[instruction_pointer + 3];
        a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
        b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
        c = a * b;
        array_ptr[index_c] = c;
        compute(array_ptr, array_length, instruction_pointer + 4);

    }
    else if (decoder_ptr->opcode == 3) {
        index_a = array_ptr[instruction_pointer + 1];
        cout << "Request for Input" << endl;
        cin >> progIn;
        array_ptr[index_a] = progIn;
        compute(array_ptr, array_length, instruction_pointer + 2);

    }
    else if (decoder_ptr->opcode == 4) {
        index_a = array_ptr[instruction_pointer + 1];
        cout << "Ouput: " << endl;
        cout << (decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a]) << std::endl;
        compute(array_ptr, array_length, instruction_pointer + 2);

    }
    else if (decoder_ptr->opcode == 99) {
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
    //Test Input
    //int puzzleInput[] = { 1, 12, 2, 3, 1, 1, 2, 3, 1, 3, 4, 3, 1, 5, 0, 3, 2, 9, 1, 19, 1, 19, 5, 23, 1, 23, 5, 27, 2, 27, 10, 31, 1, 31, 9, 35, 1, 35, 5, 39, 1, 6, 39, 43, 2, 9, 43, 47, 1, 5, 47, 51, 2, 6, 51, 55, 1, 5, 55, 59, 2, 10, 59, 63, 1, 63, 6, 67, 2, 67, 6, 71, 2, 10, 71, 75, 1, 6, 75, 79, 2, 79, 9, 83, 1, 83, 5, 87, 1, 87, 9, 91, 1, 91, 9, 95, 1, 10, 95, 99, 1, 99, 13, 103, 2, 6, 103, 107, 1, 107, 5, 111, 1, 6, 111, 115, 1, 9, 115, 119, 1, 119, 9, 123, 2, 123, 10, 127, 1, 6, 127, 131, 2, 131, 13, 135, 1, 13, 135, 139, 1, 9, 139, 143, 1, 9, 143, 147, 1, 147, 13, 151, 1, 151, 9, 155, 1, 155, 13, 159, 1, 6, 159, 163, 1, 13, 163, 167, 1, 2, 167, 171, 1, 171, 13, 0, 99, 2, 0, 14, 0 };
    
    int puzzleInput[] = {3,225,1,225,6,6,1100,1,238,225,104,0,1102,83,20,225,1102,55,83,224,1001,224,-4565,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,1101,52,15,225,1102,42,92,225,1101,24,65,225,101,33,44,224,101,-125,224,224,4,224,102,8,223,223,1001,224,7,224,1,223,224,223,1001,39,75,224,101,-127,224,224,4,224,1002,223,8,223,1001,224,3,224,1,223,224,223,2,14,48,224,101,-1300,224,224,4,224,1002,223,8,223,1001,224,2,224,1,223,224,223,1002,139,79,224,101,-1896,224,224,4,224,102,8,223,223,1001,224,2,224,1,223,224,223,1102,24,92,225,1101,20,53,224,101,-73,224,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,1101,70,33,225,1101,56,33,225,1,196,170,224,1001,224,-38,224,4,224,102,8,223,223,101,4,224,224,1,224,223,223,1101,50,5,225,102,91,166,224,1001,224,-3003,224,4,224,102,8,223,223,101,2,224,224,1,224,223,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1107,677,677,224,1002,223,2,223,1006,224,329,1001,223,1,223,1107,226,677,224,102,2,223,223,1005,224,344,101,1,223,223,108,677,677,224,1002,223,2,223,1006,224,359,101,1,223,223,107,677,677,224,1002,223,2,223,1006,224,374,1001,223,1,223,1007,677,677,224,102,2,223,223,1006,224,389,101,1,223,223,108,677,226,224,102,2,223,223,1006,224,404,101,1,223,223,1108,226,677,224,102,2,223,223,1005,224,419,1001,223,1,223,7,677,226,224,102,2,223,223,1005,224,434,101,1,223,223,1008,677,677,224,102,2,223,223,1006,224,449,1001,223,1,223,1007,677,226,224,1002,223,2,223,1006,224,464,101,1,223,223,1108,677,677,224,1002,223,2,223,1005,224,479,1001,223,1,223,107,226,226,224,1002,223,2,223,1005,224,494,101,1,223,223,8,226,677,224,102,2,223,223,1006,224,509,101,1,223,223,8,677,677,224,102,2,223,223,1006,224,524,101,1,223,223,1007,226,226,224,1002,223,2,223,1006,224,539,1001,223,1,223,107,677,226,224,102,2,223,223,1006,224,554,101,1,223,223,1107,677,226,224,1002,223,2,223,1006,224,569,1001,223,1,223,1008,226,677,224,102,2,223,223,1006,224,584,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,599,1001,223,1,223,7,677,677,224,1002,223,2,223,1005,224,614,1001,223,1,223,1108,677,226,224,1002,223,2,223,1005,224,629,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,644,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,659,101,1,223,223,108,226,226,224,102,2,223,223,1005,224,674,101,1,223,223,4,223,99,226};

    const int n_input = (sizeof(puzzleInput) / sizeof(puzzleInput[0]));
  
    compute(puzzleInput, n_input, 0);
}
