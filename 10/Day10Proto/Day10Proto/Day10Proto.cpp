// Day10Proto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> 
using namespace std;


void PrintGrid(vector<vector<int>> grid) {
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << endl;
    }
}

int main()
{
    std::cout << "Day 10 Proto: Starting ..." << std::endl;;

    // Usage asteroid_grid[row][column]
    vector<vector<int>> asteroid_grid
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << std::endl;

    PrintGrid(asteroid_grid);

    std::cout << std::endl;

    std::cout << asteroid_grid[0][0] << std::endl;

    std::cout << std::endl;
    
    asteroid_grid[0][0] = 42;

    std::cout << asteroid_grid[0][0] << std::endl;

    std::cout << std::endl;

    std::cout << asteroid_grid[2][1] << std::endl;

    asteroid_grid[2][1] *= asteroid_grid[2][1];

    std::cout << std::endl;

    std::cout << asteroid_grid[2][1] << std::endl;

    std::cout << std::endl;

    PrintGrid(asteroid_grid);

    std::cout << std::endl;

    system("pause");
}
