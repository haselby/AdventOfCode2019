// Day7Proto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>

void everyCombination(std::vector<int> orderedPhases, std::set<int> availablePhases, int depth) {

    std::set<int> downstreamAvailablePhases;
    for (auto myPhase : availablePhases) {
        downstreamAvailablePhases.insert(myPhase);
    };

    if (availablePhases.size() == 0) {       
        for (auto orderedPhase : orderedPhases) {
            std::cout << orderedPhase;
        }
        std::cout << std::endl;
    } else{
        for (auto phase : availablePhases) {   
                orderedPhases.push_back(phase);
                downstreamAvailablePhases.erase(phase);
                everyCombination(orderedPhases, downstreamAvailablePhases, depth + 1);
                //Next two lines help unwrap the recursive algorithm
                orderedPhases.pop_back();  
                downstreamAvailablePhases = availablePhases;
        }
    }
    return;
}


int main()
{
    int depth{ 1 };
    std::cout << "Running Proto...\n";

    std::set<int> puzzlePhases = { 0,1,2,3,4 };
    std::vector<int> orderedPhases;

    everyCombination(orderedPhases, puzzlePhases, depth);

}


