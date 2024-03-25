// Copyright 2024 Nirupama Poojari
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using std::cin, std::cout, std::cerr, std::endl;

/**
 * user permissions is a seperate method for displaying read, write, and execute
 * @param struct stat sb
 * 
*/
void userPermis(struct stat sb) {   // userPermis starts here
    if (sb.st_mode & S_IRUSR) {   // if-else starts here
        printf("r");
    } else {    // else starts here
        printf("-");
    }   // if-else ends here

    if (sb.st_mode & S_IWUSR) {   // if-else starts here
        printf("w");
    } else {    // else starts here
        printf("-");
    }   // if-else ends here
    if (sb.st_mode & S_IXUSR) {   // if-else starts here
        printf("x");
    } else {    // else starts here
        printf("-");
    }   // if-else ends here
}  // userPermis ends here

/**
 * group permissions is a seperate method for displaying read, write, and execute
 * @param struct stat sb
 * 
*/
void groupPermis(struct stat sb) {   // groupPermis starts here
    if (sb.st_mode & S_IRGRP) {   // if starts here
        printf("r");
    } else {    // else starts here
         printf("-");
    }    // else if-else ends here
    if (sb.st_mode & S_IWGRP) {   // if starts here
        printf("w");
    } else {    // else starts here
        printf("-");
    }    // else if-else ends here
    if (sb.st_mode & S_IXGRP) {   // if starts here
        printf("x");
    } else {    // else starts here
        printf("-");
    }     // else if-else ends here
}   // groupPermis starts here

/**
 * Other permissions is a seperate method for displaying read, write, and execute
 * @param struct stat sb
 * 
*/
void otherPermis(struct stat sb) {   // otherPermis() starts here
    if (sb.st_mode & S_IROTH) {   // if starts here
        printf("r");
    } else {    // else starts here
        printf("-");
    }     // else if-else ends here
    if (sb.st_mode & S_IWOTH) {   // if starts here
        printf("w");
    } else {    // else starts here
        printf("-");
    }     // else if-else ends here
    if (sb.st_mode & S_IXOTH) {   // if starts here
        printf("x");
    } else {    // else starts here
         printf("-");
    }     // else if-else ends here
}   // otherPermis() ends here

/**
 * toString() method is used to display permissions
 * @param struct stat sb
 * 
*/
void permissions(struct stat sb) {   // permisions() start here
    userPermis(sb);
    groupPermis(sb);
    otherPermis(sb);
    cout << endl;
}   // permisions() end here

/**
 * User is prompted to enter commandline arguments
 * @param int argc
 * @arg argv[]
 * 
*/
int main(int argc, char* argv[]) {  // main starts here
    struct stat sb;
    if (argc == 1) {  // if starts here
        cout << "Usage: lab03 filename" << endl;
    } else {   // else starts here
        std::string line;
        std::string fileName = argv[1];
        fileName = argv[1];
        std::ifstream myfile(fileName);
        if (myfile.is_open()) {  // if starts here
            if (stat(argv[1], &sb) == -1) {  // if starts here
            perror("stat");
            exit(EXIT_FAILURE);
            }  // if ends here
            cout << fileName <<  " permissions: ";
            permissions(sb);
        } else {   // else starts here
            cout << "Error: Could not stat file " <<
            "\'"<<  fileName << "\'"<< endl;
        }    // if-else ends here
         myfile.close();
    }    // if-else ends here
    return 0;
}   // main starts here
