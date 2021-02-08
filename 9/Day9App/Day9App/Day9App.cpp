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
		// TODO: May be able to use this information to also define Instruction Pointer Increment
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

			std::cerr << instruction.opcode << std::endl;
			if (instruction.parameter_1_mode == Mode::immediate) std::cerr << "Immediate Mode" << std::endl;
			//
			if (instruction.opcode == 1) {
				// add operation
				p1_index = (instruction.parameter_1_mode == Mode::relative) ? intcode_program[instruction_pointer + 1 + relative_base] : intcode_program[instruction_pointer + 1];
				p2_index = (instruction.parameter_2_mode == Mode::relative) ? intcode_program[instruction_pointer + 2 + relative_base] : intcode_program[instruction_pointer + 2];
				p3_index = (instruction.parameter_3_mode == Mode::relative) ? intcode_program[instruction_pointer + 3 + relative_base] : intcode_program[instruction_pointer + 3];
				p1 = (instruction.parameter_1_mode == Mode::immediate) ? p1_index : intcode_program[p1_index];
				p2 = (instruction.parameter_2_mode == Mode::immediate) ? p2_index : intcode_program[p2_index];
				p3 = p1 + p2;
				intcode_program[p3_index] = p3;
				
				//Increment instruction pointer 
				instruction_pointer += 4;
			}
			//
			std::cerr << "p3: " << p3 << std::endl;
			//
			break;
		}
	}

private:
	//Private Variable Declaration
	std::vector<long long int> intcode_program;
	int instruction_pointer{};
	int relative_base{};
	long long int p1{};
	long long int p2{};
	long long int p3{};
	int p1_index{};
	int p2_index{};
	int p3_index{};


	

	
};

int main()
{
	//std::vector<long long int> intcode_program = { 109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99 };
	std::vector<long long int> intcode_program = { 11101, 5, 15, 0, 99, 42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	std::cout << "Day 9 App Started..." << std::endl;

	IntcodeComputer intcodeComputer{ intcode_program };
	intcodeComputer.run();


    system("pause");
}
