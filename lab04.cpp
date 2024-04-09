// Copyright 2024 Nirupama Poojari
#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <chrono>

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::mutex;
using std::unordered_map;
using std::ref;

using fVector = std::vector<float>;
using MutexMap = std::unordered_map<int, std::mutex>;

// Function declarations
void deposit(int acc, fVector& account, double amt, MutexMap& mutexes);
void withdraw(int acc, fVector& account, double amt, MutexMap& mutexes);
void transfer(int from, int to, fVector& account, double amt, MutexMap& mutexes);
void processTransactions(fVector& accts, MutexMap& mutexes);
void initializeAccounts(fVector& accts);

// Function to deposit money into an account
void deposit(int acc, fVector& account, double amt, MutexMap& mutexes) {
    std::lock_guard<std::mutex> lock(mutexes[acc]);
    account[acc] += amt;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Function to withdraw money from an account
void withdraw(int acc, fVector& account, double amt, MutexMap& mutexes) {
    std::lock_guard<std::mutex> lock(mutexes[acc]);
    if (account[acc] >= amt) {
        account[acc] -= amt;
    } else {
        std::cerr << "Insufficient funds to withdraw $" << amt << endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Function to transfer money from one account to another
void transfer(int from, int to, fVector& account, double amt, MutexMap& mutexes) {
    std::scoped_lock lock(mutexes[from], mutexes[to]);
    if (account[from] >= amt) {
        account[from] -= amt;
        account[to] += amt;
    } else {
        std::cerr << "Insufficient funds to transfer $" << amt << endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Initialize the account balances
void initializeAccounts(fVector& accts) {
    accts = {1000, 1400, 2300, 5500, 6000};
}

// Process all transactions
void processTransactions(fVector& accts, MutexMap& mutexes) {
    vector<double> transactions = {100, 50, 75, 200, 800, 950, 230};
    vector<thread> threads;

    for (double amt : transactions) {
        threads.emplace_back([&](){ deposit(0, accts, amt, mutexes); });
        threads.emplace_back([&](){ transfer(1, 2, accts, amt, mutexes); });
        threads.emplace_back([&](){ withdraw(3, accts, amt, mutexes); });
        threads.emplace_back([&](){ transfer(4, 3, accts, amt, mutexes); });
        threads.emplace_back([&](){ deposit(4, accts, amt, mutexes); });
        threads.emplace_back([&](){ withdraw(0, accts, amt, mutexes); });
        threads.emplace_back([&](){ transfer(2, 0, accts, amt, mutexes); });
        threads.emplace_back([&](){ transfer(4, 1, accts, amt, mutexes); });
        threads.emplace_back([&](){ deposit(1, accts, amt, mutexes); });
        threads.emplace_back([&](){ withdraw(3, accts, amt, mutexes); });
    }

    // Join all threads
    for (auto& th : threads) {
        th.join();
    }
}

int main() {
    fVector accts;
    initializeAccounts(accts);

    MutexMap mutexes;
    processTransactions(accts, mutexes);

    cout << "Final balances\n";
    for (size_t acc = 0; acc < accts.size(); acc++) {
        cout << acc << " $" << accts[acc] << endl;
    }
    return 0;
}
