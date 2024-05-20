// Copyright 2024 Nirupama Poojari
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
std::mutex mtx;
using std::thread, std::cout, std::cin,
        std::endl;

// Simple method that performs some calculations
void increment(double& result) {
    for (int i = 0; i < 10000; i++) {
        double argument = static_cast<double>(i);
        mtx.lock();
        result += sin(argument);
        mtx.unlock();
    }
}

int main() {
    const int num_threads = 4;
    double total = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(increment, std::ref(total));
    }
    for (auto &t : threads) {
        t.join();
    }
    // Print out the total
    cout << "Total: " << total << endl;

    return 0;
}
