// Day7App_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <concrt.h>
#include <functional>

int amp_a_output = 0;
int amp_b_output = 0;
int amp_c_output = 0;
int amp_d_output = 0;
int amp_e_output = 0;

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
	int input{0};
	int output{0};
	bool waitingForInput{true};
	std::function<void(int)> setDownstreamInput;


	IntcodeComputer(std::vector<int>& puzzleInput, int phaseAmp) {
		intcodeProgram = puzzleInput;
		setInput(phaseAmp);
	};

	// TODO: Figure out how to pass the setInput setter for downstream amp.
	IntcodeComputer(std::vector<int>& puzzleInput, int phaseAmp, std::function<void(int)> setDownstream) {
		intcodeProgram = puzzleInput;
		setInput(phaseAmp);
		setDownstreamInput = setDownstream;
	};

	void setInput(int i) {
		input = i;
		waitingForInput = false;
	}

	void compute(long long instruction_pointer) {

		InstructionDecoder* decoder_ptr = new InstructionDecoder(intcodeProgram[instruction_pointer]);

		int a{};
		int b{};
		int c{};
		int index_a{};
		int index_b{};
		int index_c{};
		int progIn{};
		int progOut{};
		

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
			std::cout << "Opt Code 3 Executed" << std::endl;
			index_a = intcodeProgram[instruction_pointer + 1];
			while (waitingForInput) {
				Concurrency::wait(10); // sleeps for 10 milliseconds
			}
			std::cout << "Input Set" << std::endl;
			intcodeProgram[index_a] = input;
			waitingForInput = true;
			compute(instruction_pointer + 2);

		}
		else if (decoder_ptr->opcode == 4) {
			// output operation
			index_a = intcodeProgram[instruction_pointer + 1];
			output = (decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a]);
			// TODO Get the line below working
			//setDownstreamInput(output);
			compute(instruction_pointer + 2);

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
			// Halt intcode computer 
			std::cout << "Opt Code 99 Executed" << std::endl;
			std::cout << "Amp Output: " << output << std::endl;
			return; 
		}
		else {
			// invalid opcode handling
			std::cout << "Intcode computer error, unexpected opcode: " << decoder_ptr->opcode << std::endl;
			std::terminate;
		}

	}

};

int testThruster(std::vector<int>& puzzleInput, std::vector<int>& orderedPhases) {
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

	//Initialize the Amps

	// TODO figure out how to pass the setInput method of amp_b as a constructor argument for amp_a
	//Amp A
	IntcodeComputer* amp_a = new IntcodeComputer(puzzleInput, phaseAmpA);
	amp_a->compute(0);
	std::cout << "Output of amp a: " << outputAmpA << std::endl;

	//Amp B
	IntcodeComputer* amp_b = new IntcodeComputer(puzzleInput, phaseAmpB);
	amp_b->compute(0);
	std::cout << "Output of amp B: " << outputAmpB << std::endl;

	//Amp C
	IntcodeComputer* amp_c = new IntcodeComputer(puzzleInput, phaseAmpC);
	amp_c->compute(0);
	std::cout << "Output of amp C: " << outputAmpC << std::endl;

	//AMP D
	IntcodeComputer* amp_d = new IntcodeComputer(puzzleInput, phaseAmpD);
	amp_d->compute(0);
	std::cout << "Output of amp D: " << outputAmpD << std::endl;

	//AMP E
	IntcodeComputer* amp_e = new IntcodeComputer(puzzleInput, phaseAmpE);
	amp_e->compute(0);
	std::cout << "Output of amp E: " << outputAmpE << std::endl;

	//Provide Amp A with initial input

	amp_a->setInput(0);

	return outputAmpE;
}

void everyCombination(std::vector<int>& puzzleInput, std::vector<int> orderedPhases, std::set<int> availablePhases, int& maxThrust) {

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
	std::vector<int> puzzleInput = { 3,8,1001,8,10,8,105,1,0,0,21,42,67,88,101,114,195,276,357,438,99999,3,9,101,3,9,9,1002,9,4,9,1001,9,5,9,102,4,9,9,4,9,99,3,9,1001,9,3,9,1002,9,2,9,101,2,9,9,102,2,9,9,1001,9,5,9,4,9,99,3,9,102,4,9,9,1001,9,3,9,102,4,9,9,101,4,9,9,4,9,99,3,9,101,2,9,9,1002,9,3,9,4,9,99,3,9,101,4,9,9,1002,9,5,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,99 };

	std::vector<int> orderedPhases;
	std::set<int> puzzlePhases = { 0,1,2,3,4 };
	int maxThrust{ 0 };
	
	//TODO trying to get this test to pass
	//TODO application compiles, but just sits as amp wait for input, that never comes.
	//text single configuration of phases
	std::vector<int> testPuzzleInput = { 3, 26, 1001, 26, -4, 26, 3, 27, 1002, 27, 2, 27, 1, 27, 26, 27, 4, 27, 1001, 28, -1, 28, 1005, 28, 6, 99, 0, 0, 5 };
	std::vector<int> testOrderedPhases = { 9,8,7,6,5 };
	testThruster(testPuzzleInput, testOrderedPhases);

	//Disable line below temporarily
	//everyCombination(puzzleInput, orderedPhases, puzzlePhases, maxThrust);

	std::cout << "Max Thrust: " << maxThrust << std::endl;
}
