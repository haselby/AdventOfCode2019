// Day7App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>

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
	
	std::vector<int> intcodeProgram;
	int phase;
	int input;
	int input_no = 1;
	
	IntcodeComputer(std::vector<int> &puzzleInput, int phaseAmp, int inputAmp) {
		intcodeProgram = puzzleInput;
		phase = phaseAmp;
		input = inputAmp;
	};

	int compute(long long instruction_pointer) {

		InstructionDecoder* decoder_ptr = new InstructionDecoder(intcodeProgram[instruction_pointer]);

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
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			index_c = intcodeProgram[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			c = a + b;
			intcodeProgram[index_c] = c;
			compute(instruction_pointer + 4);
		}
		else if (decoder_ptr->opcode == 2) {
			// multiple operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			index_c = intcodeProgram[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			c = a * b;
			intcodeProgram[index_c] = c;
			compute(instruction_pointer + 4);

		}
		else if (decoder_ptr->opcode == 3) {
			// request for input operation
			index_a = intcodeProgram[instruction_pointer + 1];
			//std::cout << "Request for Input" << std::endl;
			//std::cin >> progIn;
			progIn = (input_no == 1) ? phase : input;
			++input_no;
			intcodeProgram[index_a] = progIn;
			compute(instruction_pointer + 2);

		}
		else if (decoder_ptr->opcode == 4) {
			// output operation
			index_a = intcodeProgram[instruction_pointer + 1];
			return (decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a]);
			//No need to continue, since return above
			//compute(instruction_pointer + 2);

		}
		else if (decoder_ptr->opcode == 5) {
			// jump-if-true operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			if (!(a == 0)) {
				compute(b);
			}
			else {
				compute(instruction_pointer + 3); 
			}

		}
		else if (decoder_ptr->opcode == 6) {
			// jump-if-false operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			if (a == 0) {
				compute(b);
			}
			else {
				compute(instruction_pointer + 3); 
			}
		}
		else if (decoder_ptr->opcode == 7) {
			// less than operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			index_c = intcodeProgram[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			c = (a < b) ? 1 : 0;
			intcodeProgram[index_c] = c;
			compute(instruction_pointer + 4);
		}
		else if (decoder_ptr->opcode == 8) {
			// equals operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			index_c = intcodeProgram[instruction_pointer + 3];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			c = (a == b) ? 1 : 0;
			intcodeProgram[index_c] = c;
			compute(instruction_pointer + 4);

		}
		else if (decoder_ptr->opcode == 99) {
			// exit operation - SHOULD NEVER GET HERE in Day7App - 
			std::cout << "Opt Code 99 Executed" << std::endl;
			std::cout << intcodeProgram[0] << std::endl;
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

int testThruster(std::vector<int> &puzzleInput, std::vector<int> &orderedPhases) {
	int phaseAmpA = orderedPhases[0];
	int phaseAmpB = orderedPhases[1];
	int phaseAmpC = orderedPhases[2];
	int phaseAmpD = orderedPhases[3];
	int phaseAmpE = orderedPhases[4];

	int inputAmpA{ 0 };

	int outputAmpA{};
	int outputAmpB{};
	int outputAmpC{};
	int outputAmpD{};
	int outputAmpE{};

	std::cout << "Phase of amp a: " << phaseAmpA << std::endl;
	std::cout << "Phase of amp b: " << phaseAmpB << std::endl;
	std::cout << "Phase of amp c: " << phaseAmpC << std::endl;
	std::cout << "Phase of amp d: " << phaseAmpD << std::endl;
	std::cout << "Phase of amp e: " << phaseAmpE << std::endl;


	std::cout << "Input of amp a: " << inputAmpA << std::endl;

	//Amp A
	IntcodeComputer* amp_a = new IntcodeComputer(puzzleInput, phaseAmpA, inputAmpA);
	outputAmpA = amp_a->compute(0);
	std::cout << "Output of amp a: " << outputAmpA << std::endl;

	//Amp B
	IntcodeComputer* amp_b = new IntcodeComputer(puzzleInput, phaseAmpB, outputAmpA);
	outputAmpB = amp_b->compute(0);
	std::cout << "Output of amp B: " << outputAmpB << std::endl;

	//Amp C
	IntcodeComputer* amp_c = new IntcodeComputer(puzzleInput, phaseAmpC, outputAmpB);
	outputAmpC = amp_c->compute(0);
	std::cout << "Output of amp C: " << outputAmpC << std::endl;

	//AMP D
	IntcodeComputer* amp_d = new IntcodeComputer(puzzleInput, phaseAmpD, outputAmpC);
	outputAmpD = amp_d->compute(0);
	std::cout << "Output of amp D: " << outputAmpD << std::endl;

	//AMP E
	IntcodeComputer* amp_e = new IntcodeComputer(puzzleInput, phaseAmpE, outputAmpD);
	outputAmpE = amp_e->compute(0);
	std::cout << "Output of amp E: " << outputAmpE << std::endl;

	return outputAmpE;
}

void everyCombination(std::vector<int>& puzzleInput, std::vector<int> orderedPhases, std::set<int> availablePhases, int &maxThrust) {

	std::vector<int> downstreamOrderedPhases;
	std::set<int> downstreamAvailablePhases;
	int currentThrust{};

	if (availablePhases.size() == 0) {
		currentThrust = testThruster(puzzleInput, orderedPhases);
		if (currentThrust > maxThrust) maxThrust = currentThrust;
		return;
	}
	else {
		for (auto phase : availablePhases) {
			//Next two lines: Resets for every loop iteration    
			downstreamOrderedPhases = orderedPhases;
			downstreamAvailablePhases = availablePhases;
			downstreamOrderedPhases.push_back(phase);
			downstreamAvailablePhases.erase(phase);
			everyCombination(puzzleInput, downstreamOrderedPhases, downstreamAvailablePhases, maxThrust);
		}
		return;
	}
}

int main()
{
	//std::vector<int> puzzleInput = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0}; // Passing
	//std::vector<int> puzzleInput = { 3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0 }; // Passing
	//std::vector<int> puzzleInput = { 3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0 }; //Passing
	std::vector<int> puzzleInput = { 3,8,1001,8,10,8,105,1,0,0,21,42,67,88,101,114,195,276,357,438,99999,3,9,101,3,9,9,1002,9,4,9,1001,9,5,9,102,4,9,9,4,9,99,3,9,1001,9,3,9,1002,9,2,9,101,2,9,9,102,2,9,9,1001,9,5,9,4,9,99,3,9,102,4,9,9,1001,9,3,9,102,4,9,9,101,4,9,9,4,9,99,3,9,101,2,9,9,1002,9,3,9,4,9,99,3,9,101,4,9,9,1002,9,5,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,99};

	std::vector<int> orderedPhases;
	std::set<int> puzzlePhases = { 0,1,2,3,4 };
	int maxThrust{ 0 };
    everyCombination(puzzleInput,orderedPhases, puzzlePhases, maxThrust);

	std::cout << "Max Thrust: " << maxThrust << std::endl;
}