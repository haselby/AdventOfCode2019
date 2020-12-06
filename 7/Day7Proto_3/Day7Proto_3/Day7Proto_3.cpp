// Day7Proto_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// CPP program to demonstrate multithreading 
// using three different callables. 
#include <iostream> 
#include <thread> 
#include <future>

// A dummy function 
long long calculate(long long Z)
{
    long long max = 0;
    for (long long i = 0; i < Z; i++) {
        if (i > max)
            max = i;
    }
    std::cout << "Max value: " << max << std::endl;
    return max;
}

// A callable object 
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            std::cout << "Thread using function object as  callable: " << i << std::endl;
    }
};

void haselFunc() {
    std::thread th1(calculate, 300'000'000);
    th1.join();
}

int main()
{
    std::cout << "Launching Proto ..." << std::endl;


    long long resultFinal;


    auto future1 = std::async(calculate, 9'000'000'000);
    auto future2 = std::async(calculate, 6'000'000'000);
    auto future3 = std::async(calculate, 3'000'000'000);
    
    long long result1 = future1.get();
    long long result2 = future2.get();
    long long result3 = future3.get();

    resultFinal = result1 + result2 + result3;

    std::cout << "Final countdown: " << resultFinal << std::endl;

    return 0;
}
