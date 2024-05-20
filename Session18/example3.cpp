// Copyright 2024 Nirupama Poojari

#include <iostream>
#include <vector>
#include <future>
#include <cmath>
#include <mutex>

std::mutex mtx;
using std::cout;
using std::endl;

// Method that performs calculations and returns a double value
double increment() {
    double result = 0;
    for (int i = 0; i < 10000; i++) {
        double argument = static_cast<double>(i);
        mtx.lock();
        result += sin(argument);
        mtx.unlock();
    }
    return result;
}

int main() {
    const int num_threads = 4;
    double total = 0;
    std::vector<std::future<double>> futures;

    for (int i = 0; i < num_threads; i++) {
        futures.emplace_back(std::async(std::launch::async, increment));
    }

    for (auto &f : futures) {
        total += f.get();
    }

    // Print out the total
    cout << "Total: " << total << endl;

    return 0;
}
