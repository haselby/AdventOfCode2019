// Day10Proto2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

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


int main()
{
    std::cout << "Day10Proto2: Starting..." << std::endl;

    std::string puzzle = LoadPuzzle();

    std::cout << puzzle;

    std::cout << std::endl;

    system("pause");
}
