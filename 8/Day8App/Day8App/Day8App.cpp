/* Day8App.cpp : This file contains the 'main' function. Program execution begins and ends there.
*
* Top Left Corner (Origin)
* (0,0,0) - (x, y, z) 
* 
* -----------> y
* |
* |
* |
* V
* x
* 
* z-axis is the frame number, starting with frame 0
*
* Each Frame in my puzzle is 25 wide (x-axis) by 6 tall (y-axis)
* 
* Requires installation of Boost C++ Library: https://www.boost.org/
* Requires configuration of Boost Library by adding Property Sheet to Visual Studio Project 
* in Property Manager Window under (Debug | x64) and/or (Release |x64)
* C/C++ - Additional Include Directories: C:\devtools\boost_1_75_0
* Linker - Additional Library Directories: C:\devtools\boost_1_75_0\stage\lib
* 
* Turn Property Manager Window on View (Menu) --> Other Windows --> Property Manager
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include <boost/multi_array.hpp> 
#include <cassert>


void ReadInPuzzle() {
    std::ifstream puzzle_file;
    puzzle_file.open("puzzle_input.txt");

    int x_size = 25;
    int y_size = 6;
    int z_size = 100; //Number of frames 100; Based on number fo character = 15000

    // Create a 3D array that is 3 x 4 x 2
    typedef boost::multi_array<int, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[x_size][y_size][z_size]);

    // Assign values to the elements
    char c;
    
    for (index z = 0; z != z_size; ++z) {
        for (index y = 0; y != y_size; ++y) {
            for (index x = 0; x != x_size; ++x){
                if (puzzle_file.get(c)) {
                    A[x][y][z] = (int)c - (int)48;  //Convert char to int using ASCII Math
                }
            }
        }
    }

    puzzle_file.close();

    // Print Frames of interest

    std::cout << "Frames of interest: " << std::endl;
    
    int answer{ 0 };
    int zero_count_min{ 150 };

    for (index z = 0; z != z_size; ++z) {
        int num_zero{ 0 };
        int num_one{ 0 };
        int num_two{ 0 };
        for (index y = 0; y != y_size; ++y) {
            for (index x = 0; x != x_size; ++x) {
                switch (A[x][y][z]) {
                case 0 : 
                    ++num_zero;
                    break;
                case 1 :
                    ++num_one;
                    break;
                case 2 : 
                    ++num_two;
                    break;
                }
            }
        }
        
        if (num_zero <= zero_count_min) {
            zero_count_min = num_zero;
            answer = (num_one * num_two);
            std::cout << "Frame ID: " << z << " Zero count: " << num_zero << ", One count: " << num_one << ", Two count: " << num_two << ", One times two count : " << answer  << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Final Answer: " << answer << std::endl;



}


int main()
{
    std::cout << "Day 8 App" << std::endl;
    ReadInPuzzle();

}

