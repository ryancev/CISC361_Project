#include <iostream>
#include <fstream>
#include <sstream>
#include "Job.hpp"
#include "HoldQueueTwo.hpp"
#include <string>


int countSpaces(const std::string& currentLine);
void processLine(const std::string& currentLine);

HoldQueueTwo *holdQueueTwo = new HoldQueueTwo();

int main() {
    // C = System Configuration
    //    C __ = The system to be simulated starts at time __
    //    M = Main memory with __ memory
    //    S = Serial Devices with __ devices
    //    Q = Time quantum
    //
    // A = Job Arrival
    //    A __ = Arrives at time __
    //    J =    Job number
    //    M __ = Units of main memory required
    //    S __ = Max devices at any point during execution
    //    P __ = Priority number
    // Q = Request for devices (I/O)
    //    Q __ = At time __
    //    J __ = Job number
    //    D __ = Requests __ devices
    // L = Release for devices (I/O)
    //    L __ = At time __
    //    J __ = Job number __
    //    D __ = Number of devices released
    // D = Display of current system status
    //    D __ = At time __ an event is generated that prints
    //    List of jobs that have entered the system
    //    Print:
    //        state of job (e.g. running on CPU, in Hold Queue, or finished at time __
    //        Remaining service time if job is unfinished, turnaround time and weighted turnaround time if finished.
    //        The contents of each queue
    //        If it is the last display, print system turnaround time, system weighted turnaround time
    std::string currentLine;
    std::ifstream inputFile("../test_input.txt");
    while (std::getline(inputFile, currentLine)) {
        std::cout << currentLine << std::endl;
        processLine(currentLine);
    }
    holdQueueTwo->printHoldQueue();
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
        ++wordIndex;
    }
    // This is just to make sure that the linked list was working correctly - will get removed
    Job *job = new Job(splitString->at(0));
    holdQueueTwo->insertAtFront(new QueueNode(job));
    // Checking the command code of the input
    switch (splitString->at(0)) {
        case 'C': {
            // Call constructor for C commands
            break;
        }
        case 'A': {
            // Call constructor for A commands
            break;
        }
        case 'Q': {
            // Call constructor for Q commands
            break;
        }
        case 'L': {
            // Call constructor for L commands
            break;
        }
        case 'D': {
            // Call constructor for D commands
            break;
        }
    }
}
