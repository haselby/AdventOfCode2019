// Day10App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> 
using namespace std;

std::string LoadPuzzle() {

    //Input Puzzle as C++ Raw string literal
    //usage: prefix(optional) R"delimiter(raw_characters)delimiter"
    std::string _puzzle = R"(
.#..#
.....
#####
....#
...##
)";

    return _puzzle;
}

void PrintGrid(vector<vector<char>> grid) {
    
    for (int j = 0; j < grid.size(); j++)
    {
        for (int i = 0; i < grid[j].size(); i++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

vector<vector<char>> LoadToGrid(string puzzle) {
    
    // TODO: Fix initialization so puzzle can be of any size.
    vector<vector<char>> grid
    {
        { '1', '2', '3', '4', '5' },
        { '1', '2', '3', '4', '5' },
        { '1', '2', '3', '4', '5' },
        { '1', '2', '3', '4', '5' },
        { '1', '2', '3', '4', '5' }
    };

    int x{};
    int y{};

    for (int i = 0; i < puzzle.length(); i++) {
        if ((puzzle.at(i)) == '\n') {
            if (x > 0) {
                y++;
                x = 0;
            }
        }
        else {
            grid[x++][y] = puzzle.at(i);
        }
    }

    return grid;
}

int main()
{
    std::cout << "Day 10 Proto: Starting ..." << std::endl;;

    std::string puzzle = LoadPuzzle();
    //std::cerr << puzzle << std::endl;

    vector<vector<char>> asteroid_grid = LoadToGrid(puzzle);
    
    PrintGrid(asteroid_grid);

    std::cerr << asteroid_grid[1][0] << std::endl;
    system("pause");
}
