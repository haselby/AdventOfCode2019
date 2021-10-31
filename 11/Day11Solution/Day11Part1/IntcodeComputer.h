#pragma once
#include <iostream>
#include <vector>
#include "Mode.h"
#include "Instruction.h"
#include "PanelGrid.h"

using namespace std;


class IntcodeComputer {
private:
	PanelGrid shipPanelGrid{ 100,100,0 };

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
				
				//Output operation
				//std::cout << p1 << std::endl;
				shipPanelGrid.readCommand(p1);


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
				cout << "Painted Panels Count: " << shipPanelGrid.countPaintedPanels() << endl;
				cout << endl;
				shipPanelGrid.printPanels();
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
		//int progIn{};
		//std::cout << "Request for Input: " << std::endl;
		//std::cin >> progIn;
		//return progIn;
		return shipPanelGrid.getColor();
	}
};

