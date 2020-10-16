// Puzzle1p2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


int fuelPartialCalculation(int weight) { 
    int partialFuel = (weight / 3) - 2;

    if ((partialFuel / 3) - 2 < 0) return partialFuel; // stub of recursive function
    else {
        partialFuel += fuelPartialCalculation(partialFuel);
    }
    return partialFuel;
}

int fuelCalculation(int inventory[], int numberOfItems) {
    int fuel{ 0 };

    for (size_t i = 0; i < numberOfItems; i++)
    {
        fuel += fuelPartialCalculation(inventory[i]);
    }
    return fuel;
}

int main()
{
    std::cout << "Advent of Code, Puzzle 1\n";

    int rocketInventory[] = { 71343, 60747, 122054, 67364, 53017, 81716, 55910, 120565, 59809, 148941, 124539, 108258, 77377, 97572, 56164, 57858, 97899, 53786, 129974, 88645, 89330, 136628, 139228, 128560, 88358, 85431, 68350, 61458, 61833, 104279, 127850, 111139, 94752, 95037, 141723, 96355, 89433, 78355, 108635, 59567, 55589, 141992, 104238, 68291, 147546, 73476, 70991, 62313, 58672, 121783, 63158, 112817, 117776, 134302, 107446, 124540, 84279, 51193, 78829, 142544, 102528, 131341, 121502, 78165, 127783, 81012, 106876, 90403, 62091, 58090, 74824, 109657, 55042, 108119, 56850, 69635, 107792, 131462, 106842, 83864, 127170, 88563, 138150, 117904, 75996, 78850, 76719, 133639, 55213, 111209, 126243, 123495, 89420, 54618, 110194, 79674, 109834, 77521, 110024, 115217 };
    int inventoryNumberItems = sizeof(rocketInventory) / sizeof(int);
    std::cout << inventoryNumberItems << std::endl;

    std::cout << "Fuel required: " << fuelCalculation(rocketInventory, inventoryNumberItems) << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
