#include <iostream>
#include <fstream>
#include <sstream>
#include "Job.hpp"
#include "HoldQueueTwo.hpp"
#include "CPU.hpp"
#include <string>


int countSpaces(const std::string& currentLine);
void processLine(const std::string& currentLine);

/** Current system configuration **/
CPU *currentSystem;
/** Second hold queue, FIFO **/
HoldQueueTwo *holdQueueTwo;

int main() {
    std::string currentLine;
    std::ifstream inputFile("../test_input.txt");
    while (std::getline(inputFile, currentLine)) {
        std::cout << currentLine << std::endl;
        processLine(currentLine);
    }
    return 0;
}

/**
 * Counts the number of spaces within the passed in string
 * @param currentLine The string that will have its spaces counted
 * @return int representing the number of spaces
 */
int countSpaces(const std::string& currentLine) {
    int numSpaces = 0;
    for (char i : currentLine) {
        if (i == ' ')  {
            numSpaces++;
        }
    }
    return numSpaces;
}

/**
 * Processes a line of input to determine which job constructor should be called.
 * @param currentLine
 */
void processLine(const std::string& currentLine) {
    int numSpaces = countSpaces(currentLine);
    std::string splitString[numSpaces + 1];
    std::stringstream ssin(currentLine);
    int wordIndex = 0;
    // splitString[i]
    // 0 = Command Code
    // 1 = Command Value
    // 2...n = Commands with values, ex.) M=200 or S=12 or Q=4
    while (ssin.good() && wordIndex < numSpaces + 1) {
        ssin >> splitString[wordIndex];
        if (wordIndex > 1) {
            splitString[wordIndex] = splitString[wordIndex].substr(2);
        }
        // Uncomment for viewing indexes of the command codes
//        std::cout << "CURRENT SPLIT STRING IS: " << "Index:" << wordIndex << " - " << splitString[wordIndex] << std::endl;

        ++wordIndex;
    }

    // C = System Configuration
    // [i]
    //  1  C __ = The system to be simulated starts at time __
    //  2  M = Main memory with __ memory
    //  3  S = Serial Devices with __ devices
    //  4  Q = Time quantum
    // A = Job Arrival
    //  1  A __ = Arrives at time __
    //  2  J =    Job number
    //  3  M __ = Units of main memory required
    //  4  S __ = Max devices at any point during execution
    //  5  R __ = Run Time
    //  6  P __ = Priority number
    // Q = Request for devices (I/O)
    //  1  Q __ = At time __
    //  2  J __ = Job number
    //  3  D __ = Requests __ devices
    // L = Release for devices (I/O)
    //  1  L __ = At time __
    //  2  J __ = Job number __
    //  3  D __ = Number of devices released
    // D = Display of current system status
    //  1  D __ = At time __ an event is generated that prints
    //    List of jobs that have entered the system
    //    Print:
    //        state of job (e.g. running on CPU, in Hold Queue, or finished at time __
    //        Remaining service time if job is unfinished, turnaround time and weighted turnaround time if finished.
    //        The contents of each queue
    //        If it is the last display, print system turnaround time, system weighted turnaround time
    // Checking the command code of the input
    switch (splitString->at(0)) {
        case 'C': {
            // Set proper system configuration variables
            int arrivalTime = std::stoi(splitString[1]);
            int mainMemory = std::stoi(splitString[2]);
            int serialDevices = std::stoi(splitString[3]);
            int timeQuantum = std::stoi(splitString[4]);
            currentSystem = new CPU(mainMemory, serialDevices, timeQuantum);
            break;
        }
        case 'A': {
            // Call constructor Job
            int arrivalTime = std::stoi(splitString[1]);
            int jobNumber = std::stoi(splitString[2]);
            int memoryRequired = std::stoi(splitString[3]);
            int maxDevices = std::stoi(splitString[4]);
            int runTime = std::stoi(splitString[5]);
            int priorityNumber = std::stoi(splitString[6]);
            break;
        }
        case 'Q': {
            // Process device request
            int arrivalTime = std::stoi(splitString[1]);
            int jobNumber = std::stoi(splitString[2]);
            int devicesRequested = std::stoi(splitString[3]);
            break;
        }
        case 'L': {
            // Process device release request
            int arrivalTime = std::stoi(splitString[1]);
            int jobNumber = std::stoi(splitString[2]);
            int devicesReleased = std::stoi(splitString[3]);
            break;
        }
        case 'D': {
            // Process system info display
            break;
        }
    }
}
