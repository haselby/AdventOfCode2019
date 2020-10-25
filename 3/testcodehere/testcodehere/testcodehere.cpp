// testcodehere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// C++ code to demonstrate tuple, get() and make_pair() 
#include<iostream> 
#include<tuple> // for tuple 

int main()
{
    // Declaring tuple 
    std::tuple <int, int, int, int> geek;

    // Assigning values to tuple using make_tuple() 
    geek = std::make_tuple(0, 0, 0, 0);

    // Printing initial tuple values using get() 
    std::cout << "The initial values of tuple are : ";
    std::cout << get<0>(geek) << " " << get<1>(geek);
    std::cout << " " << get<2>(geek) << std::endl;

    // Use of get() to change values of tuple 
    std::get<0>(geek) = 42;
    std::get<1>(geek) = 42;
    std::get<2>(geek) = 42;
    std::get<3>(geek) = 42;

    // Printing modified tuple values 
    std::cout << "The modified values of tuple are : " << std::endl;
    std::cout << get<0>(geek) << std::endl;
    std::cout << get<1>(geek) << std::endl;
    std::cout << get<2>(geek) << std::endl;
    std::cout << get<3>(geek) << std::endl;

    return 0;
}