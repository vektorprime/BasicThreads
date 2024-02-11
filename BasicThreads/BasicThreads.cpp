// BasicThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>


void basic_print_string()
{
    std::cout << "inside of basic_print_string" << std::endl;
}


void print_string(std::string test)
{
    std::cout << "PRINTING STRING : " << test << std::endl << std::flush;
}

void print_name(std::string name_string)
{
    std::cout << "Name in thread is " << name_string << std::endl;
}

std::mutex thread_mutex{};

void add_one_to_number(int &num)
{
    std::lock_guard<std::mutex> guard(thread_mutex);
    std::cout << "num1 in func before inc is " << num << std::endl;
    ++num;
    std::cout << "num1 in func after inc is " << num << std::endl;
}

int main()
{
    int num1 = 10;
    std::cout << "num1 in main is " << num1 << std::endl;
    std::thread worker1(add_one_to_number, std::ref(num1));

    {
        std::lock_guard<std::mutex> guard(thread_mutex);
        std::cout << "num1 in main before inc is  " << num1 << std::endl;
        ++num1;
    }

    worker1.join();
    std::cout << "num1 at end of main is " << num1 << std::endl;
}

