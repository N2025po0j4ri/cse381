// Copyright 2023 Nirupama Poojari
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;
using std::stringstream;


int main(int argc, char* argv[]) {  // main starts here
    if (argc != 3) {  // if starts here
        cout << "Usage: lab01 integer1 integer2" << endl;
        return 0;
    }

    stringstream stream1;  // used to read commandlines
   // stream1 << 'a';
    stream1 << argv[1];  // insertion operator
    int num1;
    stream1 >> num1;
    if (stream1.fail()) { // extraction operator
        cout << "Error: arguments must be integers" << endl;
        cout << stream1.failbit;
        return 0;
    }  
   // cout << num1 << endl;
    int num2;
    stringstream stream2;
    stream2 << argv[2];
    stream2 >> num2;   // extraction operator
 //   cout << num2<< endl;
     if (stream2.fail()) { // extraction operator
        cout << "Error: arguments must be integers" << endl;
        return 0;
    }  

    
    int sum = num1 + num2;
    cout << sum << endl;
        
    return 0;
}   // main ends here
