//  Copyright 2024 Nirupama Poojari
#include <thread>
#include <vector>
#include <iostream>
#include <cmath>
using std::cout, std::thread, std::cin, std::endl;

/**
 * Displays greeting with value generated in a thread
 * @param: x, type - referenced integer 
*/

void displayHello(int &x) {  // display() starts here
  cout << "Hello " << x << endl;
}

/**
 * Will display all the threads
 * @param: x, type - referenced integer 
*/
int main() {  // main starts here
  int i = 0;
  cout << "Prints two threads without using a vector"  << endl;
  thread a(displayHello, std::ref(i));
  a.join();
  thread b(displayHello, std::ref(i));
  b.join();
  cout << "Runs 8 threads, using a for-loop and stores a vector"  << endl;
  std::vector<thread> threads;
  for (int i=0; (i < 8); i++) {  // for loop starts here
    threads.push_back(thread(displayHello, std::ref(i)));
  }   // for loop ends here
  for (auto& t : threads) {   // for loop starts here
    t.join();
  }   // for loop ends here
  exit(0);
}  // main ends here

/**
 * Note:  From threads 3 - 8, nothing changed here
 * 
*/
