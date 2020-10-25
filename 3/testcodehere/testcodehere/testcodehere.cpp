// testcodehere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <iostream>
#include <sstream> //Required for std::stringstream  (Used for string to int conversion)
#include <iterator> // Required for map (similar to a Dictionary)
#include <map>      // Required for map (similar to a Dictionary)

//PathOfWires x_loc, y_loc = wireId, numberOfSteps
static std::map<std::pair<int, int>, std::pair<int, int>> PathOfWires;

static std::map<std::pair<int, int>, std::pair<int, int>> PathOfWires2;

int main() {
	PathOfWires[std::make_pair(42, 24)].first = 5;

	for (auto elem : PathOfWires)
	{
		std::cout << elem.first.first << "," << elem.first.second << " " << elem.second.first << "," << elem.second.second << "\n";
	}

	PathOfWires[std::make_pair(42, 24)].second = 9;

	for (auto elem : PathOfWires)
	{
		std::cout << elem.first.first << "," << elem.first.second << " " << elem.second.first << "," << elem.second.second << "\n";
	}

}


//int main()
//{
//    std::map<int, int> marks;
//    marks.insert(std::pair<int, int>(160, 42));
//    marks.insert(std::pair<int, int>(161, 30));
//    marks.insert(std::pair<int, int>(162, 40));
//    marks.insert(std::pair<int, int>(163, 50));
//    marks.insert(std::pair<int, int>(164, 31));
//    marks.insert(std::pair<int, int>(165, 12));
//    marks.insert(std::pair<int, int>(166, 34));
//    marks[180] = 42;
//
//    std::map<int, int>::iterator itr;
//    for (itr = marks.begin(); itr != marks.end(); ++itr) {
//        std::cout << itr->first << " " << itr->second << "\n";
//    }
//   
//    //
//   // build a pair from two ints
//    auto p1 = std::make_pair(42, 25);
//    std::cout << "The value of p1 is "
//        << "(" << p1.first << ", " << p1.second << ")\n";
//
//
//    std::map<std::pair<int, int>, int> luckyvar;
//    luckyvar[p1] = 5;
//
//    auto p2 = std::make_pair(42, 24);
//
//    std::cout << luckyvar[p2] << "\n";
//
//    //---------------------------------------------
//    std::map<int, int> wordMap = {
//                    { 43, 6 },
//                    { 45, 5 },
//                    { 46, 9 },
//                    { 47, 6 }
//    };
//    // Check if key 'hat' exists in the map
//    if (wordMap.count(44) > 0)
//    {
//        std::cout << "44 Found" << std::endl;
//    }
//    else
//    {
//        std::cout << "44 Not Found" << std::endl;
//    }
//
//    return 0;
//}