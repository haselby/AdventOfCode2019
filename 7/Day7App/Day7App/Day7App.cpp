// Day7App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct InstructionDecoder {
	InstructionDecoder(int myInstruction) {
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

struct IntcodeComputer {

	// TODO - Temporary constructor
	IntcodeComputer() {};

	void setup_trial(int* puzzle, const int* input, const int n_input, int noun, int verb) {
		for (size_t i = 0; i < n_input; i++) {
			puzzle[i] = input[i];
		}
		puzzle[1] = noun;
		puzzle[2] = verb;
	}

	int compute(int* array_ptr, size_t array_length, int instruction_pointer, int input) {

		InstructionDecoder* decoder_ptr = new InstructionDecoder(array_ptr[instruction_pointer]);

		int a{};
		int b{};
		int c{};
		int index_a{};
		int index_b{};
		int index_c{};
		int progIn{};
		int progOut{};
		int outputCode{};

		if (decoder_ptr->opcode == 1) {
			// add operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			index_c = array_ptr[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			c = a + b;
			array_ptr[index_c] = c;
			compute(array_ptr, array_length, instruction_pointer + 4, input);
		}
		else if (decoder_ptr->opcode == 2) {
			// multiple operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			index_c = array_ptr[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			c = a * b;
			array_ptr[index_c] = c;
			compute(array_ptr, array_length, instruction_pointer + 4, input);

		}
		else if (decoder_ptr->opcode == 3) {
			// request for input operation
			index_a = array_ptr[instruction_pointer + 1];
			//std::cout << "Request for Input" << std::endl;
			//std::cin >> progIn;
			progIn = input;
			array_ptr[index_a] = progIn;
			compute(array_ptr, array_length, instruction_pointer + 2, input);

		}
		else if (decoder_ptr->opcode == 4) {
			// output operation
			index_a = array_ptr[instruction_pointer + 1];
			return (decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a]);
			//No need to continue, since return above
			//compute(array_ptr, array_length, instruction_pointer + 2, input);

		}
		else if (decoder_ptr->opcode == 5) {
			// jump-if-true operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			if (!(a == 0)) {
				compute(array_ptr, array_length, b, input);
			}
			else {
				compute(array_ptr, array_length, instruction_pointer + 3, input); // Assuming 2 parameters
			}

		}
		else if (decoder_ptr->opcode == 6) {
			// jump-if-false operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			if (a == 0) {
				compute(array_ptr, array_length, b, input);
			}
			else {
				compute(array_ptr, array_length, instruction_pointer + 3, input); // Assuming 2 parameters
			}
		}
		else if (decoder_ptr->opcode == 7) {
			// less than operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			index_c = array_ptr[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			c = (a < b) ? 1 : 0;
			array_ptr[index_c] = c;
			compute(array_ptr, array_length, instruction_pointer + 4, input);
		}
		else if (decoder_ptr->opcode == 8) {
			// equals operation
			index_a = array_ptr[instruction_pointer + 1];
			index_b = array_ptr[instruction_pointer + 2];
			index_c = array_ptr[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : array_ptr[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : array_ptr[index_b];
			c = (a == b) ? 1 : 0;
			array_ptr[index_c] = c;
			compute(array_ptr, array_length, instruction_pointer + 4, input);

		}
		else if (decoder_ptr->opcode == 99) {
			// exit operation - SHOULD NEVER GET HERE in Day7App - 
			std::cout << "Opt Code 99 Executed" << std::endl;
			std::cout << array_ptr[0] << std::endl;
			std::cout << "TEST2: " << outputCode << std::endl;
			return 42; // Should we ever get here?
		}
		else {
			// invalid opcode handling
			std::cout << "Intcode computer error, unexpected opcode: " << decoder_ptr->opcode << std::endl;
			std::terminate;
		}

	}

};

int main()
{
	
	IntcodeComputer* amp_a = new IntcodeComputer();

	int puzzleInput[] = { 3,225,1,225,6,6,1100,1,238,225,104,0,1102,83,20,225,1102,55,83,224,1001,224,-4565,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,1101,52,15,225,1102,42,92,225,1101,24,65,225,101,33,44,224,101,-125,224,224,4,224,102,8,223,223,1001,224,7,224,1,223,224,223,1001,39,75,224,101,-127,224,224,4,224,1002,223,8,223,1001,224,3,224,1,223,224,223,2,14,48,224,101,-1300,224,224,4,224,1002,223,8,223,1001,224,2,224,1,223,224,223,1002,139,79,224,101,-1896,224,224,4,224,102,8,223,223,1001,224,2,224,1,223,224,223,1102,24,92,225,1101,20,53,224,101,-73,224,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,1101,70,33,225,1101,56,33,225,1,196,170,224,1001,224,-38,224,4,224,102,8,223,223,101,4,224,224,1,224,223,223,1101,50,5,225,102,91,166,224,1001,224,-3003,224,4,224,102,8,223,223,101,2,224,224,1,224,223,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1107,677,677,224,1002,223,2,223,1006,224,329,1001,223,1,223,1107,226,677,224,102,2,223,223,1005,224,344,101,1,223,223,108,677,677,224,1002,223,2,223,1006,224,359,101,1,223,223,107,677,677,224,1002,223,2,223,1006,224,374,1001,223,1,223,1007,677,677,224,102,2,223,223,1006,224,389,101,1,223,223,108,677,226,224,102,2,223,223,1006,224,404,101,1,223,223,1108,226,677,224,102,2,223,223,1005,224,419,1001,223,1,223,7,677,226,224,102,2,223,223,1005,224,434,101,1,223,223,1008,677,677,224,102,2,223,223,1006,224,449,1001,223,1,223,1007,677,226,224,1002,223,2,223,1006,224,464,101,1,223,223,1108,677,677,224,1002,223,2,223,1005,224,479,1001,223,1,223,107,226,226,224,1002,223,2,223,1005,224,494,101,1,223,223,8,226,677,224,102,2,223,223,1006,224,509,101,1,223,223,8,677,677,224,102,2,223,223,1006,224,524,101,1,223,223,1007,226,226,224,1002,223,2,223,1006,224,539,1001,223,1,223,107,677,226,224,102,2,223,223,1006,224,554,101,1,223,223,1107,677,226,224,1002,223,2,223,1006,224,569,1001,223,1,223,1008,226,677,224,102,2,223,223,1006,224,584,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,599,1001,223,1,223,7,677,677,224,1002,223,2,223,1005,224,614,1001,223,1,223,1108,677,226,224,1002,223,2,223,1005,224,629,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,644,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,659,101,1,223,223,108,226,226,224,102,2,223,223,1005,224,674,101,1,223,223,4,223,99,226 };

	const int n_input = (sizeof(puzzleInput) / sizeof(puzzleInput[0]));

	int input_amp_a = 5;

	std::cout << "Input of amp a: " << input_amp_a << std::endl;
	
	int output_amp_a = amp_a->compute(puzzleInput, n_input, 0, input_amp_a);

	std::cout << "Output of amp a: " << output_amp_a << std::endl;
}