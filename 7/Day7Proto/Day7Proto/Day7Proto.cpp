// Day7Proto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>

void printVector(std::vector<int> myVector) {
    for (auto x : myVector) {
        std::cout << x;
    }
    std::cout << std::endl;
}

void everyCombination(std::vector<int> orderedPhases, std::set<int> availablePhases) {

    std::vector<int> downstreamOrderedPhases;
    std::set<int> downstreamAvailablePhases;

    if (availablePhases.size() == 0) {       
        printVector(orderedPhases);
        return;
    } else{
        for (auto phase : availablePhases) { 
            //Next two lines: Resets for every loop iteration    
            downstreamOrderedPhases = orderedPhases;
            downstreamAvailablePhases = availablePhases;
            downstreamOrderedPhases.push_back(phase);
            downstreamAvailablePhases.erase(phase);
            everyCombination(downstreamOrderedPhases, downstreamAvailablePhases);
        }
        return;
    }  
}


int main()
{
    std::cout << "Running Proto...\n";

    std::set<int> puzzlePhases = { 0,1,2,3,4 };
    std::vector<int> orderedPhases;

    everyCombination(orderedPhases, puzzlePhases);

}


