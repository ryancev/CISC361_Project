#include <iostream>
#include <fstream>
#include <sstream>
#include "Job.hpp"
#include "HoldQueueTwo.hpp"
#include "CPU.hpp"
#include <string>
#include "CompleteQueue.hpp"
#include "HoldQueueOne.hpp"
#include "ReadyQueue.hpp"
#include "WaitQueue.hpp"

using namespace std;

int countSpaces(const string& currentLine);
void processLine(const string& currentLine);
void simulateInBetween(int lastEventTime, int duration);
void checkHoldQueues();
bool addNewToCPU();
void queryWaitQueue();
void printSystemInfo();

int currentTime = 0;
int iterationsCompleted, quantumRemainder;


/** Current system configuration **/
CPU *currentSystem;
/** First Hold Queue */
HoldQueueOne *holdQueueOne;
/** Second hold queue, FIFO **/
HoldQueueTwo *holdQueueTwo;
/** Complete Queue, contains jobs that were completed */
CompleteQueue *completeQueue;
ReadyQueue *readyQueue;
WaitQueue *waitQueue;

int main() {
    string currentLine;
    ifstream inputFile("../test_input.txt");
    completeQueue = new CompleteQueue();
    readyQueue = new ReadyQueue();
    holdQueueOne = new HoldQueueOne();
    holdQueueTwo = new HoldQueueTwo();
    waitQueue = new WaitQueue();
    while (getline(inputFile, currentLine)) {
        cout << currentLine << endl;
        processLine(currentLine);
    }
    return 0;
}

/**
 * Counts the number of spaces within the passed in string
 * @param currentLine The string that will have its spaces counted
 * @return int representing the number of spaces
 */
int countSpaces(const string& currentLine) {
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
void processLine(const string& currentLine) {
    int numSpaces = countSpaces(currentLine);
    string splitString[numSpaces + 1];
    stringstream ssin(currentLine);
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
//        cout << "CURRENT SPLIT STRING IS: " << "Index:" << wordIndex << " - " << splitString[wordIndex] << endl;

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
    int arrivalTime = stoi(splitString[1]);
    int timeSinceLastEvent = arrivalTime - currentTime;

    if (currentSystem != nullptr) {
        simulateInBetween(currentTime, timeSinceLastEvent);
    }

    currentTime = arrivalTime;
    switch (splitString->at(0)) {
        case 'C': {
            // Set proper system configuration variables
            int mainMemory = stoi(splitString[2]);
            int serialDevices = stoi(splitString[3]);
            int timeQuantum = stoi(splitString[4]);
            currentSystem = new CPU(mainMemory, serialDevices, timeQuantum);
            break;
        }
        case 'A': {
            // Call constructor Job
            int jobNumber = stoi(splitString[2]);
            int memoryRequired = stoi(splitString[3]);
            int maxDevices = stoi(splitString[4]);
            int runTime = stoi(splitString[5]);
            int priorityNumber = stoi(splitString[6]);

            // If job requests more memory than system has total, ignore job request
            if (memoryRequired > currentSystem->getMainMemory()) {
                // reject job, stop processing the line
                return;
            }
            // If available memory is greater than or equal to memory needed for job, update systems total memory
            if (currentSystem->getAvailableMemory() >= memoryRequired) {
                // create process for job, put process into ready queue
                Job *newJob = new Job(arrivalTime, jobNumber, memoryRequired, maxDevices, runTime, priorityNumber);
                QueueNode *queueNode = new QueueNode(newJob);
                currentSystem->setMemoryUsed(memoryRequired, false);

                // dont know when to actually begin moving tasks from queue to cpu
                if (readyQueue->length == 0 && waitQueue->length == 0) {
                    currentSystem->updateCurrentJob(queueNode);
                    break;
                }
                readyQueue->queueTask(queueNode);
            }
            else if (currentSystem->getMainMemory() <= memoryRequired && currentSystem->getAvailableMemory() < memoryRequired) {
                // If there is enough total memory, but not enough available memory, code below executes
                Job *newJob = new Job(arrivalTime, jobNumber, memoryRequired, maxDevices, runTime, priorityNumber);
                QueueNode *queueNode = new QueueNode(newJob);
                if (priorityNumber == 1) {
                    // add to hold queue one when insert works
                    holdQueueOne->insertInOrder(queueNode);
                } else {
                    // add to second hold queue
                    holdQueueTwo->queueTask(queueNode);
                }
            }
            break;
        }
        case 'Q': {
            // Process device request
            int jobNumber = stoi(splitString[2]);
            int devicesRequested = stoi(splitString[3]);
            // use bankers algo to check if request can be satisfied, move to ready queue if yes, wait queue if no
            if (currentSystem->bankerAlg(currentSystem->getCurrentJob(), devicesRequested, false, readyQueue, waitQueue)) {
                readyQueue->queueTask(currentSystem->getCurrentJob());
                currentSystem->updateCurrentJob(readyQueue->deQueueTask());
            }
            break;
        }
        case 'L': {
            // Process device release request
            int jobNumber = stoi(splitString[2]);
            int devicesReleased = stoi(splitString[3]);
            currentSystem->releaseDevice(currentSystem->getCurrentJob(), devicesReleased, false);
            break;
        }
        case 'D': {
            // Process system info display
            printSystemInfo();
            break;
        }
    }
}

static void makeLines() {
    int numLines = 56;
    for (int i = 0; i < numLines; i++) {
        cout << "-";
    }
    cout << endl;
}

void simulateInBetween(int currentTime, int duration){
    cout << "Testing" << endl;
    int simRunTime = 0;
    int nextCpuTime = 0;
    int jobFinishTime = 0;
    while(simRunTime < duration && currentSystem->getCurrentJob() != nullptr){
        if(currentSystem->getCurrentJob() == nullptr && readyQueue->head != nullptr){
            QueueNode* first = readyQueue->deQueueTask();
            currentSystem->updateCurrentJob(first);
        }
        nextCpuTime = simRunTime + currentSystem->getQuantumLeft();
        jobFinishTime = simRunTime + currentSystem->getCurrentJob()->job->getRemainingTime();
        if(jobFinishTime <= nextCpuTime && nextCpuTime <= duration){
            //if the job completely finishes before the next line is called
            //Adds to complete queue, releases its devices (and memory), and updates its finish time
            QueueNode* cpuJob = currentSystem->getCurrentJob();
            completeQueue->queueTask(cpuJob);
            currentSystem->releaseDevice(cpuJob, 0, true);
            cpuJob->job->finishTime = currentTime + jobFinishTime;
            //update the job's time on CPU
            cpuJob->job->timeRanFor += jobFinishTime - simRunTime;
            //see if freed devices can be used, and put next device on the CPU if possible
            queryWaitQueue();
            checkHoldQueues();
            //puts next device on the CPU
            addNewToCPU();
            //adjust the simRunTime
            simRunTime = jobFinishTime;
        }else if(nextCpuTime < jobFinishTime && nextCpuTime <= duration){
            //if the quantum ends before the job is done
            //adds the current job to the ready queue
            QueueNode* cpuJob = currentSystem->getCurrentJob();
            readyQueue->queueTask(cpuJob);
            //update the job's time on CPU
            cpuJob->job->timeRanFor += nextCpuTime - simRunTime;
            //put next device on the CPU
            addNewToCPU();
            //adjust the simRunTime
            simRunTime = nextCpuTime;
        }else{
            //if the next line arrives before the next cpu event
            //update the job's time on the CPU
            currentSystem->getCurrentJob()->job->timeRanFor += duration - simRunTime;
            currentSystem->updateQuantum(duration - simRunTime);
            simRunTime = duration;
        }
    }
    if(currentSystem->getCurrentJob() == nullptr && readyQueue->head != nullptr){
        QueueNode* first = readyQueue->deQueueTask();
        currentSystem->updateCurrentJob(first);
    }
}

void checkHoldQueues(){
    QueueNode* holder = holdQueueOne->head;
    QueueNode* holder2 = holder;
    if(holder != nullptr){
        while(holder != nullptr && holder->job->memoryNeeded <= currentSystem->getAvailableMemory()){
            //continues to repeat until either the end is reached, or the needed memory isn't available
            holder2 = holder->next;
            //moves to ready queue
            readyQueue->queueTask(holder);
            //allocates the cpu memory
            currentSystem->setMemoryUsed(holder->job->memoryNeeded, false);
            holder = holder2;
        }
    }
    //only check holdQueueTwo if holdQueueOne is empty
    if(holdQueueOne->head == nullptr){
        holder = holdQueueTwo->head;
        holder2 = holder;
        while(holder != nullptr && holder->job->memoryNeeded <= currentSystem->getAvailableMemory()){
            //continues to repeat until either the end is reached, or the needed memory isn't available
            holder2 = holder->next;
            //moves to ready queue
            readyQueue->queueTask(holder);
            //allocates the cpu memory
            currentSystem->setMemoryUsed(holder->job->memoryNeeded, false);
            holder = holder2;
        }
    }
}

bool addNewToCPU(){
    //adds a new process from the ready queue to the cpu
    QueueNode* toAdd = nullptr;
    int memoryReq = 0;
    int devicesReq = 0;
    if(readyQueue->head != nullptr){
        toAdd = readyQueue->deQueueTask();
    }
    currentSystem->updateCurrentJob(toAdd);
    if(toAdd == nullptr){
        return false;
    }else{
        return true;
    }
}

void queryWaitQueue(){
    if(waitQueue->length > 0){
        QueueNode* holder = waitQueue->head;
        QueueNode* holder2 = holder;
        while(holder != nullptr){
            holder2 = holder2->next;
            currentSystem->bankerAlg(holder, holder->job->lastDevicesRequest, true, readyQueue, waitQueue);
            holder = holder2;
        }
    }
}

void printSystemInfo() {
    makeLines();
    cout << "At time: " << currentTime << endl;
    cout << "Current Available Main Memory: " << currentSystem->getAvailableMemory() << endl;
    cout << "Current Devices: " << currentSystem->getAvailableDevices() << endl;
    makeLines();
    cout << "Completed Jobs:" << endl;
    completeQueue->printHoldQueue();
    cout << "Hold Queue 1:" << endl;
    holdQueueOne->printHoldQueue();
    cout << "Hold Queue 2:" << endl;
    holdQueueTwo->printHoldQueue();
    cout << "Ready Queue:" << endl;
    readyQueue->printHoldQueue();
    cout << "Process Running on CPU:" << endl;
    currentSystem->printCurrentJob();
    cout << "Wait Queue:" << endl;
    waitQueue->printHoldQueue();
    if (currentTime == 9999) {
        completeQueue->printAvgTurnaround();
    }
}