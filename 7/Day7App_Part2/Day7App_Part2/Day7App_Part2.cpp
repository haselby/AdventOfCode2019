// Day7App_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <concrt.h> //Windows Only
#include<vector>
#include<mutex>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

//static bool upstreamDataAvailable[5] = { false, false, false, false, false };
//static int outputAmp[5] = { 0,0,0,0,0 };

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

class Amp {

	//NEW
	int ampOutput[5];
	std::mutex mutex_ampOutput[5];
	bool freshOutput[5];
	std::vector<int> ampPhase = {0,0,0,0,0};
	std::mutex mutex_ampPhase;
	bool phaseLoaded[5];

public:
	Amp(std::vector<int>& orderedPhases) {
		//TODO: (Before leaving: Read in phase setting for all 5 amps in constructor)

		ampOutput[0] = 0; // ampA output
		ampOutput[1] = 0; // ampB output
		ampOutput[2] = 0; // ampC output
		ampOutput[3] = 0; // ampD output
		ampOutput[4] = 0; // ampE output

		freshOutput[0] = false; // ampA output
		freshOutput[1] = false; // ampB output
		freshOutput[2] = false; // ampC output
		freshOutput[3] = false; // ampD output
		freshOutput[4] = true;  // ampE output

		ampPhase[0] = orderedPhases[0]; //ampA phase
		ampPhase[1] = orderedPhases[1]; //ampA phase
		ampPhase[2] = orderedPhases[2]; //ampA phase
		ampPhase[3] = orderedPhases[3]; //ampA phase
		ampPhase[4] = orderedPhases[4]; //ampA phase


		phaseLoaded[0] = false; // ampA phase read in
		phaseLoaded[1] = false; // ampB phase read in
		phaseLoaded[2] = false; // ampC phase read in
		phaseLoaded[3] = false; // ampD phase read in
		phaseLoaded[4] = false; // ampE phase read in

	};

	int getOutput(int outputIndex) {
		return ampOutput[outputIndex];
	}


	void compute(std::vector<int> intcodeProgram, long long instruction_pointer, int inputIndex, int outputIndex) {

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
			compute(intcodeProgram, instruction_pointer + 4, inputIndex, outputIndex);
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
			compute(intcodeProgram, instruction_pointer + 4, inputIndex, outputIndex);

		}
		else if (decoder_ptr->opcode == 3) {
			// request for input operation
			//std::cout << "Opt Code 3 Executed" << std::endl;
			index_a = intcodeProgram[instruction_pointer + 1];

			if (phaseLoaded[outputIndex]) {
				// Read input from output of upstream amp
				// Wait for fresh input
				while (!freshOutput[inputIndex]) sleep_for(1ms);				
				mutex_ampOutput[inputIndex].lock();
				// Start Critical Region
				std::cout << "Amp " << outputIndex << " - Reading Input..." << std::endl;
				intcodeProgram[index_a] = ampOutput[inputIndex];
				freshOutput[inputIndex] = false;
				// End Critical Region
				mutex_ampOutput[inputIndex].unlock();

			}else {
				//Setting Amp phase
				std::cout << "Setting Amp "<< outputIndex << " to phase: " << ampPhase[outputIndex] << std::endl;
				mutex_ampPhase.lock();
				intcodeProgram[index_a] = ampPhase[outputIndex];
				phaseLoaded[outputIndex] = true;
				mutex_ampPhase.unlock();
			}
			
			compute(intcodeProgram, instruction_pointer + 2, inputIndex, outputIndex);

		}
		else if (decoder_ptr->opcode == 4) {
			// output operation
			index_a = intcodeProgram[instruction_pointer + 1];
			
			mutex_ampOutput[outputIndex].lock();
			// Start Critical Region 
			std::cout << "Amp " << outputIndex << " - Writing Output ..." << std::endl;
			ampOutput[outputIndex] = (decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a]);
			freshOutput[outputIndex] = true;
			// End Critical Region
			mutex_ampOutput[outputIndex].unlock();

			compute(intcodeProgram, instruction_pointer + 2, inputIndex, outputIndex);

		}
		else if (decoder_ptr->opcode == 5) {
			// jump-if-true operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			if (!(a == 0)) {
				compute(intcodeProgram, b, inputIndex, outputIndex);
			}
			else {
				compute(intcodeProgram, instruction_pointer + 3, inputIndex, outputIndex);
			}

		}
		else if (decoder_ptr->opcode == 6) {
			// jump-if-false operation
			index_a = intcodeProgram[instruction_pointer + 1];
			index_b = intcodeProgram[instruction_pointer + 2];
			a = decoder_ptr->parameter1_isImmediate ? index_a : intcodeProgram[index_a];
			b = decoder_ptr->parameter2_isImmediate ? index_b : intcodeProgram[index_b];
			if (a == 0) {
				compute(intcodeProgram, b, inputIndex, outputIndex);
			}
			else {
				compute(intcodeProgram, instruction_pointer + 3, inputIndex, outputIndex);
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
			compute(intcodeProgram, instruction_pointer + 4, inputIndex, outputIndex);
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
			compute(intcodeProgram, instruction_pointer + 4, inputIndex, outputIndex);

		}
		else if (decoder_ptr->opcode == 99) {
			// Halt intcode computer 
			std::cout << "Opt Code 99 Executed" << std::endl;
			
			std::cout << "Amp " << outputIndex << " - Thrust: " << ampOutput[outputIndex] << std::endl;
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

	int testThrust{};
	
	std::cout << "Phase of amp a: " << orderedPhases[0] << std::endl;
	std::cout << "Phase of amp b: " << orderedPhases[1] << std::endl;
	std::cout << "Phase of amp c: " << orderedPhases[2] << std::endl;
	std::cout << "Phase of amp d: " << orderedPhases[3] << std::endl;
	std::cout << "Phase of amp e: " << orderedPhases[4] << std::endl;

	//NEW CODE

	Amp ampObject(orderedPhases);

	auto ampA = std::thread(&Amp::compute, &ampObject, puzzleInput, 0, 4, 0);
	sleep_for(100ms);
	auto ampB = std::thread(&Amp::compute, &ampObject, puzzleInput, 0, 0, 1);
	sleep_for(100ms);
	auto ampC = std::thread(&Amp::compute, &ampObject, puzzleInput, 0, 1, 2);
	sleep_for(100ms);
	auto ampD = std::thread(&Amp::compute, &ampObject, puzzleInput, 0, 2, 3);
	sleep_for(100ms);
	auto ampE = std::thread(&Amp::compute, &ampObject, puzzleInput, 0, 3, 4);

	sleep_for(1s);
	ampA.join();
	ampB.join();
	ampC.join();
	ampD.join();
	ampE.join();


	return ampObject.getOutput(4);
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
	std::set<int> puzzlePhases = { 5,6,7,8,9 };
	int maxThrust{ 0 };
	
	
	//text single configuration of phases
	//std::vector<int> testPuzzleInput = { 3, 26, 1001, 26, -4, 26, 3, 27, 1002, 27, 2, 27, 1, 27, 26, 27, 4, 27, 1001, 28, -1, 28, 1005, 28, 6, 99, 0, 0, 5 }; //Passes
	//std::vector<int> testPuzzleInput = { 3, 52, 1001, 52, -5, 52, 3, 53, 1, 52, 56, 54, 1007, 54, 5, 55, 1005, 55, 26, 1001, 54, -5, 54, 1105, 1, 12, 1, 53, 54, 53, 1008, 54, 0, 55, 1001, 55, 1, 55, 2, 53, 55, 53, 4, 53, 1001, 56, -1, 56, 1005, 56, 6, 99, 0, 0, 0, 0, 10 }; //Passes
	//std::vector<int> testOrderedPhases = { 9, 7, 8, 5, 6 };
	//maxThrust = testThruster(testPuzzleInput, testOrderedPhases);

	//Disable line below temporarily
	
	everyCombination(puzzleInput, orderedPhases, puzzlePhases, maxThrust);

	std::cout << "Max Thrust: " << maxThrust << std::endl;
}
