// Day7Proto_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.



class Amp {

    int ampOutput[5];
    std::mutex mutex_ampOutput[5];
    bool freshOutput[5];
    
public:
        Amp() {
            ampOutput[0] = 0; // ampA output
            ampOutput[1] = 0; // ampB output
            ampOutput[2] = 0; // ampC output
            ampOutput[3] = 0; // ampD output
            ampOutput[4] = 0; // ampE output

            freshOutput[0] = false; // ampA output
            freshOutput[1] = false; // ampB output
            freshOutput[2] = false; // ampC output
            freshOutput[3] = false; // ampD output
            freshOutput[4] = true; // ampE output

        }

        void powerOn(int inputIndex, int outputIndex) {
            
            while (!freshOutput[inputIndex]) sleep_for(1000ns);
            
            mutex_ampOutput[inputIndex].lock();
            mutex_ampOutput[outputIndex].lock();
           
            // Start Critical Region 
            ampOutput[outputIndex] = ampOutput[inputIndex] + 42;
            freshOutput[inputIndex] = false;
            freshOutput[outputIndex] = true;
            // End Critical Region
            
            mutex_ampOutput[inputIndex].unlock();
            mutex_ampOutput[outputIndex].unlock();


    }
        int getOutput(int outputIndex) {
            return ampOutput[outputIndex];
        }
};


int main()
{
    std::cout << "Starting Proto ..." << std::endl;

    Amp ampObject;

    auto ampA = std::thread(&Amp::powerOn, &ampObject, 4, 0);
    auto ampB = std::thread(&Amp::powerOn, &ampObject, 0, 1);
    auto ampC = std::thread(&Amp::powerOn, &ampObject, 1, 2);
    auto ampD = std::thread(&Amp::powerOn, &ampObject, 2, 3);
    auto ampE = std::thread(&Amp::powerOn, &ampObject, 3, 4);

    ampA.join();
    ampB.join();
    ampC.join();
    ampD.join();
    ampE.join();

    std::cout << ampObject.getOutput(0) << " " << ampObject.getOutput(1) << " " << ampObject.getOutput(2) << " " << ampObject.getOutput(3) << " " << ampObject.getOutput(4) << std::endl;
}


