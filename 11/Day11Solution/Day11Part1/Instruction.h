#pragma once

#include "Mode.h"
#include <math.h>

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

