// Copyright 2024 Nirupama Poojari
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>


/**
 * Define constants and shared data.
 */

const int MaxQueueSize = 10;
const int NumProducers = 3;
const int NumConsumers = 2;

/**
 * namespace pc allows access to variables.
 */

namespace pc {
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool isTerminated = false;
}

/**
 * Function to simulate image processing by the producer
 */

void produceImage() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 1; i <= 20; ++i) {  // Produce 20 images per producer
        // Adjusted sleep duration to approximately 30 milliseconds per image
        std::this_thread::sleep_for(std::chrono::milliseconds(800));

        int imageData = dist(gen);

        {
            std::unique_lock<std::mutex> lock(pc::mtx);
            // Wait until there is space in the queue
            pc::cv.wait(lock, [] {
                return pc::queue.size() < MaxQueueSize || pc::isTerminated;
            });
            // Enqueue processed image data
            if (!pc::isTerminated) {
                pc::queue.push(imageData);
                std::cout << "Producer"
                << " processed image: " << imageData << std::endl;
                // Notify consumers that data is available
                pc::cv.notify_all();
            }
        }
    }
}

/**
 * Function to simulate image rendering by the consumer
 */

void consumeImage() {
    while (true) {
        int imageData = 0;
        {
            std::unique_lock<std::mutex> lock(pc::mtx);
            // Wait until there is data in the queue
            // or termination signal is received
            pc::cv.wait(lock, [] {
                return !pc::queue.empty() || pc::isTerminated;
            });
            // Check if termination signal is received
            if (pc::isTerminated && pc::queue.empty()) break;
            // Dequeue image data
            imageData = pc::queue.front();
            pc::queue.pop();
            // Notify producers that space is available
            pc::cv.notify_all();
        }
        // Simulate image rendering time
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Consumer rendered image: " << imageData << std::endl;
    }
}

/**
 * Helper function for producer-consumer simulation
 */

void runProducerConsumer() {
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
    {
        std::lock_guard<std::mutex> lock(pc::mtx);
        pc::isTerminated = true;
        pc::cv.notify_all();
    }

    // Wait for all consumer threads to finish
    for (auto& thread : consumerThreads) {
        thread.join();
    }
}

/**
 * Will have timers and run producer-consumer simulation.
 */

int main() {
    // Record the start time
    auto startTime = std::chrono::steady_clock::now();

    // Run producer-consumer simulation
    runProducerConsumer();

    // Calculate the elapsed time
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime
    - startTime).count();

    // If the elapsed time is less than 30 seconds,
    // sleep for the remaining duration
    if (elapsedTime < 30) {
        std::this_thread::sleep_for(std::chrono::seconds(30
        - elapsedTime));
    }

    return 0;
}
