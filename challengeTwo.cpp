// Copyright 2024 Alan Ferrenberg
#include <iostream>
#include <fstream>

// Prompt the user for a filename.  If the file can be opened, open it and
// return a std::ifstream to read from.  If the file can't be opened,
// reprompt the user for the filename until they enter something valid.
std::ifstream getValidFile() {
    std::ifstream myFile;
    bool ok = false;
    while (!ok) {
        std::string filename;
        std::cout << "Enter the name of the file to read: ";
        std::cin >> filename;
        myFile.open(filename);
        if (myFile.is_open()) {
            ok = true;
        } else {
            std::cerr << "Could not open file.  Try again\n";
        }
    }
    return myFile;
}

int main() {
    // Prompt the user for the name of a file to open.  If the file doesn't
    // exist, reprompt the user until they enter something value.  The
    // std::ifstream returned will alredy be open
    std::ifstream myFile = getValidFile();

    // Read until the end of file is reached
    int wordCount = 0;
    while (!myFile.eof()) {
        std::string word;
        // Extract a whitespace-delimitted string into word
        myFile >> word;
        // Increment the word count
        wordCount++;
        std::cout << word << std::endl;
    }

    // Close the file
    myFile.close();

    // Print out the count of words
    std::cout << "\nThe file contains " << wordCount << " words\n";
    exit(0);
}
