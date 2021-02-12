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
// However for this puzzle, I'm looking for grid to display in (x,y) format aka grid[x][y] (Transposing X with Y)


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
    int x{};
    int y{};
    int x_max{};
    int y_max{};

    for (int i = 0; i < puzzle.length(); i++) {
        if ((puzzle.at(i)) == '\n') {
            if (x > 0) {
                y++;
                if (y_max < y) y_max = y;
                x = 0;
            }
        }
        else {
            x++;
            if (x_max < x) x_max = x;
        }
    }
    
    vector<vector<char>> grid(y_max, vector<char>(x_max, 'a'));

    x=0;
    y=0;

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

 vector<vector<char>> LoadToGrid2(string puzzle) {
     //Creates grid[y][x]  grid[<row number>][<columns number>]
     // Note: Not what I want for this application
    vector<vector<char>> grid;
    vector<char> row;
    int x{};

    for (int i = 0; i < puzzle.length(); i++) {
        if (puzzle.at(i) == '\n') {
            if (x > 0) {
                grid.push_back(row);
                row.clear();
                x = 0;
            }
        }
        else {
            row.push_back(puzzle.at(i));
            x++;
        }
    }

    return grid;
}

 vector<vector<char>> LoadToGrid3(string puzzle) {
     //Creates grid[x][y]  grid[<row number>][<columns number>]
     vector<vector<char>> grid;
     vector<char> column;
     int x{};
     int y{};

     for (int i = 0; i < puzzle.length(); i++) {
         if (puzzle.at(i) == '\n') {
             if (x > 0) {               
                 x = 0;
                 y++;
             }
         }
         else if (y == 0) {
             // creates columns
             column.push_back(puzzle.at(i));
             grid.push_back(column);
             column.clear();
             x++;
         }
         else {
             // grow column by one, then add new point;
             grid[x].resize(y+1);
             grid[x][y] = puzzle.at(i);
             x++;
         }
     }

     return grid;
 }

 vector<vector<char>> LoadToGrid4(string puzzle) {
     //Creates grid[x][y]  grid[<row number>][<columns number>]

     vector<vector<char>> input_grid;
     vector<char> input_row;
     int x{};

     for (int i = 0; i < puzzle.length(); i++) {
         if (puzzle.at(i) == '\n') {
             if (x > 0) {
                 input_grid.push_back(input_row);
                 input_row.clear();
                 x = 0;
             }
         }
         else {
             input_row.push_back(puzzle.at(i));
             x++;
         }
     }

     //Transpose input_grid 
     int x_max = input_grid[0].size();
     int y_max = input_grid.size();
     vector<vector<char>> grid(y_max, vector<char>(x_max, 'a'));
     
     for (int i = 0; i < x_max; ++i)
         for (int j = 0; j < y_max; ++j)
             grid[i][j] = input_grid[j][i];
     
     return grid;
 }

int main()
{
    std::cout << "Day 10 Proto: Starting ..." << std::endl;;

    std::string puzzle = LoadPuzzle();
    //std::cerr << puzzle << std::endl;

    vector<vector<char>> asteroid_grid = LoadToGrid4(puzzle);
    
    PrintGrid(asteroid_grid);

    int x = 2;
    int y = 0;

    std::cerr << asteroid_grid[x][y] << std::endl;

    system("pause");
}
