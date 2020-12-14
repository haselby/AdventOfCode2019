// Day7Proto_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

#include <chrono>
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;



class Wallet
{
    int mMoney;
    std::mutex mutex;

public:
    Wallet() :mMoney(0) {}
    
    Wallet(int initialValue) {
        mMoney = initialValue;
    }
    
    
    int getMoney() { return mMoney; }
    
    void addMoney(int number_bills, int billDenomination)
    {
        for (int i = 0; i < number_bills; ++i)
        {
            mutex.lock();
            mMoney += billDenomination;
            mutex.unlock();
            sleep_for(500ms);
        }
        std::cout << "Wallet: "<< mMoney << std::endl;
    }
    
    void subtractMoney(int money)
    {
        mutex.lock();
        for (int i = 0; i < money; ++i)
        {
            mMoney--;
        }
        mutex.unlock();
        std::cout << "subtracted: " << mMoney << std::endl;
    }
};


int main()
{
    std::cout << "Let's get started.." << std::endl;
    
    int val = 0;

    Wallet walletObject(10);

    auto j1 = std::thread(&Wallet::addMoney, &walletObject, 10, 5);
    auto j2 = std::thread(&Wallet::addMoney, &walletObject, 20, 5);
    auto j3 = std::thread(&Wallet::addMoney, &walletObject, 30, 5);
    auto j4 = std::thread(&Wallet::subtractMoney, &walletObject, 10);

    j1.join();
    j2.join();
    j3.join();
    j4.join();

    val = walletObject.getMoney();
    
    std::cout << val << std::endl;
    return 0;
}