// Day9App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>

//Instruction Modes
// 0 - postion mode - intProgram[parameter]
// 1 - immeditate mode - parameter
// 2 - relative mode - intProgram[parameter + relativeBase]
enum class Mode {position, immediate, relative};

class Instruction {
public:
	int opcode{};
	Mode parameter_1_mode;
	Mode parameter_2_mode;
	Mode parameter_3_mode;

	//Constructor
	Instruction(long long int instruction) :instruction{ instruction } {
		setOpcode();
		setNumberOfParameters();
		setParameterMode();
	};
private:
	long long int instruction{};
	int num_parameters{};
	

	int getDigit(int n, int position) {
		return (n % (int)pow(10, position) - (n % (int)pow(10, position - 1))) / (int)pow(10, position - 1);
	}

	void setOpcode() {
		int x = instruction; // Explicit Type Conversion from Long Long Int to Int (Narrowing Conversion)
		opcode = (getDigit(x, 2) * 10) + getDigit(x, 1);
	}

	void setNumberOfParameters() {
		     if (opcode == 1) num_parameters = 3;  // add
		else if (opcode == 2) num_parameters = 3;  // multiply
		else if (opcode == 3) num_parameters = 1;  // read
		else if (opcode == 4) num_parameters = 1;  // write
		else if (opcode == 5) num_parameters = 2;  // jump-if-true
		else if (opcode == 6) num_parameters = 2;  // jump-if-false
		else if (opcode == 7) num_parameters = 3;  // less-than
		else if (opcode == 8) num_parameters = 3;  // equals
		else if (opcode == 9) num_parameters = 1;  // adjust relative base
		else if (opcode == 99) num_parameters = 0; // halt
	}

	
	Mode EvaluateMode(int x) {
		switch (x) {
		case 0: return Mode::position;
		case 1: return Mode::immediate;
		case 2: return Mode::relative;
		}
	}
	
	void setParameterMode() {
		// TODO: Implicit conversion long long int to int in getDigit call. May need to address.
		if (num_parameters >= 1) {
			int x = getDigit(instruction, 3);
			parameter_1_mode = EvaluateMode(x);
		}
		if (num_parameters >= 2) {
			int y = getDigit(instruction, 4);
			parameter_2_mode = EvaluateMode(y);
		}
		if (num_parameters >= 3) {
			int z = getDigit(instruction, 5);
			parameter_3_mode = EvaluateMode(z);
		}
	}

};


class IntcodeComputer {

public:
//Public Variable Declarations


// Constructor
	IntcodeComputer(std::vector<long long int> intcodeProgram) : intcode_program{ intcodeProgram } {};

	void run() {
		while (true) {
			Instruction instruction{ intcode_program[instruction_pointer] };

			//Writes opcode to console
			//std::cerr << "opcode: " <<instruction.opcode << std::endl;
			
			if (instruction.opcode == 1) {
				// add operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p3_index = (instruction.parameter_3_mode == Mode::relative) ? intcode_program[instruction_pointer + 3] + relative_base : intcode_program[instruction_pointer + 3];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				p3 = p1 + p2;
				if (instruction.parameter_3_mode == Mode::immediate) intcode_program[instruction_pointer + 3] = p3;
				else intcode_program[p3_index] = p3;
				
				//Increment instruction pointer 
				instruction_pointer += 4;
			}
			else if (instruction.opcode == 2) {
				// multiply operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p3_index = (instruction.parameter_3_mode == Mode::relative) ? intcode_program[instruction_pointer + 3] + relative_base : intcode_program[instruction_pointer + 3];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				p3 = p1 * p2;
				if (instruction.parameter_3_mode == Mode::immediate) intcode_program[instruction_pointer + 3] = p3;
				else intcode_program[p3_index] = p3;

				//Increment instruction pointer 
				instruction_pointer += 4;
			}
			else if (instruction.opcode == 3) {
				// input operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];

				// Todo: Currently only implemented to accept input from command line.				
				p1 = getInt();

				if (instruction.parameter_1_mode == Mode::immediate) intcode_program[instruction_pointer + 1] = p1;
				else intcode_program[p1_index] = p1;

				//Increment instruction pointer 
				instruction_pointer += 2;
			}
			else if (instruction.opcode == 4) {
				// output operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				std::cout << p1 << std::endl;

				//Increment instruction pointer 
				instruction_pointer += 2;
			}
			else if (instruction.opcode == 5) {
				// jump-if-true operation operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				
				//Jump or Increment instruction pointer 
				if (p1 != 0) instruction_pointer = p2;
				else instruction_pointer += 3;
			}
			else if (instruction.opcode == 6) {
				// jump-if-false operation operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];

				//Jump or Increment instruction pointer 
				if (p1 == 0) instruction_pointer = p2;
				else instruction_pointer += 3;
			}
			else if (instruction.opcode == 7) {
				// less than operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p3_index = (instruction.parameter_3_mode == Mode::relative) ? intcode_program[instruction_pointer + 3] + relative_base : intcode_program[instruction_pointer + 3];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				p3 = (p1 < p2) ? 1 : 0;
				
				if (instruction.parameter_3_mode == Mode::immediate) intcode_program[instruction_pointer + 3] = p3;
				else intcode_program[p3_index] = p3;

				//Increment instruction pointer 
				instruction_pointer += 4;
			}
			else if (instruction.opcode == 8) {
				// equal (boolean) operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2] + relative_base : intcode_program[instruction_pointer + 2];
				p3_index = (instruction.parameter_3_mode == Mode::relative) ? intcode_program[instruction_pointer + 3] + relative_base : intcode_program[instruction_pointer + 3];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				p3 = (p1 == p2) ? 1 : 0;
				
				if (instruction.parameter_3_mode == Mode::immediate) intcode_program[instruction_pointer + 3] = p3;
				else intcode_program[p3_index] = p3;

				//Increment instruction pointer 
				instruction_pointer += 4;
			}
			else if (instruction.opcode == 9) {
				// adjusts the relative base operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1] + relative_base : intcode_program[instruction_pointer + 1];

				if (instruction.parameter_1_mode == Mode::immediate) relative_base += intcode_program[instruction_pointer + 1];
				else relative_base += intcode_program[p1_index];

				//Increment instruction pointer 
				instruction_pointer += 2;
			}
			else if (instruction.opcode == 99) {
				// Halt intcode computer 
				break;
			}
			else {
				// invalid opcode. Error handling
				std::terminate;
			}
		}
	}

private:
	//Private Variable Declaration
	std::vector<long long int> intcode_program;
	long long int instruction_pointer{};
	int relative_base{};
	long long int p1{};
	long long int p2{};
	long long int p3{};
	long long int p1_index{};
	long long int p2_index{};
	long long int p3_index{};

	int getInt() {
		// TODO: This is not guarded. User can enter any input.
		int progIn{};
		std::cout << "Request for Input: " << std::endl;
		std::cin >> progIn;
		return progIn;
	}
};

std::vector<long long int> loadTest(){
	//Usage: Comment out one of the test incode_programs below:
	
	//std::vector<long long int> intcode_program = { }; // intcode program -
	//std::vector<long long int> intcode_program = { 3,9,8,9,10,9,4,9,99,-1,8 }; // intcode program - Using position mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
	//std::vector<long long int> intcode_program = { 3,9,7,9,10,9,4,9,99,-1,8 }; // intcode program - Using position mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
	//std::vector<long long int> intcode_program = { 3,3,1108,-1,8,3,4,3,99 }; // intcode program - Using immediate mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
	//std::vector<long long int> intcode_program = { 3,3,1107,-1,8,3,4,3,99 }; // intcode program - Using immediate mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
	//std::vector<long long int> intcode_program = { 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99 }; // intcode program - input instruction to ask for a single number. The program will then output 999 if the input value is below 8, output 1000 if the input value is equal to 8, or output 1001 if the input value is greater than 8.
	//std::vector<long long int> intcode_program = { 109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99 }; // intcode program - takes no input and produces a copy of itself as output
	//std::vector<long long int> intcode_program = { 1102,34915192,34915192,7,4,7,99,0 }; // intcode program - should output a 16-digit number.
	//std::vector<long long int> intcode_program = { 104,1125899906842624,99 }; // intcode program - should output the large number in the middle

	//Puzzle Input below: (Note: When prompted for input, enter 1 - Part 1 or enter 2 - Part 2)
	std::vector<long long int> intcode_program = { 1102,34463338,34463338,63,1007,63,34463338,63,1005,63,53,1101,3,0,1000,109,988,209,12,9,1000,209,6,209,3,203,0,1008,1000,1,63,1005,63,65,1008,1000,2,63,1005,63,904,1008,1000,0,63,1005,63,58,4,25,104,0,99,4,0,104,0,99,4,17,104,0,99,0,0,1102,1,31,1018,1102,352,1,1023,1101,0,1,1021,1101,0,33,1003,1102,1,36,1007,1102,21,1,1005,1101,359,0,1022,1101,0,787,1024,1102,1,24,1011,1101,30,0,1014,1101,22,0,1016,1101,0,0,1020,1102,1,29,1000,1101,778,0,1025,1102,23,1,1017,1102,1,28,1002,1101,38,0,1019,1102,1,27,1013,1102,1,32,1012,1101,0,37,1006,1101,444,0,1027,1102,1,20,1009,1101,0,447,1026,1101,0,39,1008,1101,35,0,1010,1102,559,1,1028,1102,26,1,1004,1102,1,25,1015,1102,1,34,1001,1101,0,554,1029,109,-3,2101,0,9,63,1008,63,34,63,1005,63,205,1001,64,1,64,1105,1,207,4,187,1002,64,2,64,109,23,21107,40,39,-7,1005,1013,227,1001,64,1,64,1106,0,229,4,213,1002,64,2,64,109,-17,1202,-2,1,63,1008,63,36,63,1005,63,249,1106,0,255,4,235,1001,64,1,64,1002,64,2,64,109,-6,1202,10,1,63,1008,63,36,63,1005,63,277,4,261,1106,0,281,1001,64,1,64,1002,64,2,64,109,-2,1208,9,26,63,1005,63,303,4,287,1001,64,1,64,1106,0,303,1002,64,2,64,109,32,1206,-7,321,4,309,1001,64,1,64,1106,0,321,1002,64,2,64,109,-29,1207,7,20,63,1005,63,337,1105,1,343,4,327,1001,64,1,64,1002,64,2,64,109,27,2105,1,-2,1001,64,1,64,1106,0,361,4,349,1002,64,2,64,109,-25,2108,39,7,63,1005,63,377,1106,0,383,4,367,1001,64,1,64,1002,64,2,64,109,1,1201,6,0,63,1008,63,36,63,1005,63,409,4,389,1001,64,1,64,1105,1,409,1002,64,2,64,109,1,2102,1,1,63,1008,63,33,63,1005,63,435,4,415,1001,64,1,64,1105,1,435,1002,64,2,64,109,28,2106,0,-3,1106,0,453,4,441,1001,64,1,64,1002,64,2,64,109,-13,21101,41,0,1,1008,1018,44,63,1005,63,477,1001,64,1,64,1106,0,479,4,459,1002,64,2,64,109,4,21108,42,42,-2,1005,1019,501,4,485,1001,64,1,64,1106,0,501,1002,64,2,64,109,-21,2101,0,2,63,1008,63,28,63,1005,63,523,4,507,1105,1,527,1001,64,1,64,1002,64,2,64,109,26,1205,-5,545,4,533,1001,64,1,64,1105,1,545,1002,64,2,64,109,3,2106,0,-1,4,551,1106,0,563,1001,64,1,64,1002,64,2,64,109,-33,1201,4,0,63,1008,63,28,63,1005,63,583,1105,1,589,4,569,1001,64,1,64,1002,64,2,64,109,11,2107,27,-3,63,1005,63,609,1001,64,1,64,1106,0,611,4,595,1002,64,2,64,109,8,21102,43,1,3,1008,1018,43,63,1005,63,637,4,617,1001,64,1,64,1105,1,637,1002,64,2,64,109,-5,21108,44,41,0,1005,1010,653,1105,1,659,4,643,1001,64,1,64,1002,64,2,64,109,-13,2108,21,8,63,1005,63,681,4,665,1001,64,1,64,1106,0,681,1002,64,2,64,109,6,1207,0,34,63,1005,63,703,4,687,1001,64,1,64,1105,1,703,1002,64,2,64,109,7,1208,-7,35,63,1005,63,723,1001,64,1,64,1106,0,725,4,709,1002,64,2,64,109,-13,2102,1,7,63,1008,63,23,63,1005,63,745,1105,1,751,4,731,1001,64,1,64,1002,64,2,64,109,13,1205,10,767,1001,64,1,64,1105,1,769,4,757,1002,64,2,64,109,14,2105,1,0,4,775,1001,64,1,64,1106,0,787,1002,64,2,64,109,-20,21107,45,46,7,1005,1011,809,4,793,1001,64,1,64,1105,1,809,1002,64,2,64,109,-3,2107,25,3,63,1005,63,827,4,815,1106,0,831,1001,64,1,64,1002,64,2,64,109,13,1206,7,847,1001,64,1,64,1106,0,849,4,837,1002,64,2,64,109,-11,21101,46,0,7,1008,1010,46,63,1005,63,871,4,855,1106,0,875,1001,64,1,64,1002,64,2,64,109,15,21102,47,1,-4,1008,1014,48,63,1005,63,895,1106,0,901,4,881,1001,64,1,64,4,64,99,21102,27,1,1,21101,0,915,0,1106,0,922,21201,1,63208,1,204,1,99,109,3,1207,-2,3,63,1005,63,964,21201,-2,-1,1,21102,1,942,0,1106,0,922,21202,1,1,-1,21201,-2,-3,1,21101,957,0,0,1105,1,922,22201,1,-1,-2,1106,0,968,21201,-2,0,-2,109,-3,2106,0,0 }; // intcode program - Day9App

	//Add zeroed memory to the tail of intcode_program
	for (int i = 0; i < 1000; i++) {
		intcode_program.push_back(0);
	}
	
	return intcode_program;
}

int main()
{
	std::cout << "Day 9 App Started..." << std::endl;

	std::vector<long long int> intcode_program = loadTest();

	IntcodeComputer intcodeComputer{ intcode_program };
	intcodeComputer.run();

    system("pause");
}
