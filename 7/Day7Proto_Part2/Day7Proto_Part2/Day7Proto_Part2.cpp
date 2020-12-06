// Day7Proto_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


void printInt(int i) {
	std::cout << "Let's print an integer: " << i << std::endl;
}

void anotherFunction(void(*myFunc)(int)) {
	int a = 12345;
	myFunc(a);
}


int main()
{
	typedef void(*PrintIntFunction)(int);

	PrintIntFunction haselFunc = printInt;
	haselFunc(4);
	anotherFunction(haselFunc);

	// --

	auto simpleFunction = printInt;
	simpleFunction(2);
	anotherFunction(haselFunc);

}