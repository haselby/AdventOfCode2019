// Day7Proto_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// CPP program to demonstrate multithreading 
// using three different callables. 
#include <iostream> 
#include <thread> 

// A dummy function 
void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        std::cout << "Thread using function pointer as callable: " << i << std::endl;
    }
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

int main()
{
    std::cout << "Threads 1 and 2 and 3 operating independently" << std::endl;

    // This thread is launched by using  
    // function pointer as callable 
    std::thread th1(foo, 3000);

    // This thread is launched by using 
    // function object as callable 
    std::thread th2(thread_obj(), 3000);

    // Define a Lambda Expression 
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            std::cout << "Thread using lambda expression as callable"  << std::endl;
    };

    // This thread is launched by using  
    // lamda expression as callable 
    std::thread th3(f, 3000);

    // Wait for the threads to finish 
    // Wait for thread t1 to finish 
    th1.join();

    // Wait for thread t2 to finish 
    th2.join();

    // Wait for thread t3 to finish 
    th3.join();

    return 0;
}
