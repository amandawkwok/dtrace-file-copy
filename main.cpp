/*
 ** Author: Amanda Kwok
 ** CS 4310 - Assignment 1
 */

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

#define maxBytes 256
#define readWritePermissions 0644

int main (int argc, char* argv[])
{
    int inputFD, outputFD;
    string inputFile, outputFile;
    ssize_t bytesRead;
    char buffer[maxBytes];

    // Acquire input file name - write prompt to screen & accept input
    cout << "Input file name: ";
    cin >> inputFile;
    
    // Acquire output file name - write prompt to screen & accept input
    cout << "Output file name: ";
    cin >> outputFile;
    
    // Open the input file - if file doesn't exist, abort
    inputFD = open(inputFile.c_str(), O_RDONLY);
    if (inputFD == -1) {
        cout << "Error! " + inputFile + " doesn't exist.\n";
        return 1;
    }
    
    // Create output file - if file exists, abort
    outputFD = open(outputFile.c_str(), O_WRONLY | O_CREAT | O_EXCL , 0644);
    if (outputFD == -1) {
        cout << "Error! There was a problem creating " + outputFile + ".\n";
        return 2;
    }
    
    // Loop - Read from input file & write to output file until read fails
    while ((bytesRead = read(inputFD, &buffer, maxBytes)) > 0) {
        write(outputFD, &buffer, bytesRead);
    }
    
    if (bytesRead == -1) {
        cout << "Error! There was a problem writing to " + outputFile + ".\n";
    }
    
    // Close output file
    close(outputFD);
    
    // Write completion message to screen
    cout << "Contents were copied to " + outputFile + ".\n";
    
    // Terminate normally
    return 0;
}
