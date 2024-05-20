// Copyright 2024 Nirupama Poojari
#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <random>
#include <mutex>
#include <atomic>

/**
 * Define constants and shared data
*/

const int MaxQueueSize = 10;
const int NumProducers = 3;
const int NumConsumers = 2;

/**
 * namespace pc lists a bunch of variables to use.
*/

namespace pc {
    std::queue<int> queue;
    std::mutex mtx;
    std::atomic<bool> isTerminated(false);
}

/**
 * Function to simulate image processing by the producer
*/

void produceImage() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    auto startTime = std::chrono::steady_clock::now();
    auto targetTime = startTime
    + std::chrono::seconds(18);  // Adjusted to run for approximately 18 seconds

    while (std::chrono::steady_clock::now() < targetTime) {
        // Simulate image processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        int imageData = dist(gen);

        while (true) {
            std::lock_guard<std::mutex> lock(pc::mtx);
            if (pc::queue.size() < MaxQueueSize && !pc::isTerminated) {
                pc::queue.push(imageData);
                std::cout << "Producer processed"
                          << " image: " << imageData << std::endl;
                break;  // Exit the busy-wait loop once data is pushed
            }
        }
    }
}

/**
 * Function to simulate image rendering by the consumer
*/

void consumeImage() {
    auto startTime = std::chrono::steady_clock::now();
    auto targetTime = startTime
    + std::chrono::seconds(18);  // Adjusted to run for approximately 18 seconds

    while (std::chrono::steady_clock::now() < targetTime) {
        int imageData = 0;
        while (true) {
            std::lock_guard<std::mutex> lock(pc::mtx);
            if (!pc::queue.empty()) {
                imageData = pc::queue.front();
                pc::queue.pop();
                break;  // Exit the busy-wait loop once data is consumed
            } else if (pc::isTerminated) {
                return;  // Exit the function if termination signal is received
            }
        }
        // Simulate image rendering time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Consumer rendered image: " << imageData << std::endl;
    }
}

/**
 * Generates consumer and producter threads to join.
*/
int main() {
    // Create producer threads
    std::vector<std::thread> producerThreads;
    for (int i = 0; i < NumProducers; ++i) {
        producerThreads.emplace_back(produceImage);
    }

    // Create consumer threads
    std::vector<std::thread> consumerThreads;
    for (int i = 0; i < NumConsumers; ++i) {
        consumerThreads.emplace_back(consumeImage);
    }

    // Wait for all producer threads to finish
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // Notify consumers of termination
    pc::isTerminated = true;

    // Wait for all consumer threads to finish
    for (auto& thread : consumerThreads) {
        thread.join();
    }

    return 0;
}
