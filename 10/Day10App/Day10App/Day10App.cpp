// Day10App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> 
using namespace std;

//  |-----------> x-dir
//  |
//  |
//  |
//  v
//  y-dir
//
// Traditionally grid[row #][column #]  = grid [y] [x]
// However for this puzzle, I'm looking for grid to display in (x,y) format aka grid[x][y] (Transposing x with y)


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
     //Creates grid[x][y]  grid[<row number>][<columns number>]
     vector<vector<char>> grid;
     vector<char> column;
     int x{};
     int y{};

     for (int i = 0; i < puzzle.length(); i++) {
         if (puzzle.at(i) == '\n') {
             //Increments x, y appropriately, new row begins after '\n'
             //This statement also handles puzzle input that starts with '\n' 
             if (x > 0) {               
                 x = 0;
                 y++;
             }
         }
         else if (y == 0) {
             // create new column, adding one elment to column
             column.push_back(puzzle.at(i));
             grid.push_back(column);
             column.clear();
             x++;
         }
         else {
             // add element to bottom of column
             grid[x].push_back(puzzle.at(i));
             x++;
         }
     }

     return grid;
 }


int main()
{
    std::cout << "Day 10 Proto: Starting ..." << std::endl;;

    std::string puzzle = LoadPuzzle();

    vector<vector<char>> asteroid_grid = LoadToGrid(puzzle);
    
    PrintGrid(asteroid_grid);

    int x = 2;
    int y = 0;

    std::cerr << asteroid_grid[x][y] << std::endl;

    system("pause");
}
