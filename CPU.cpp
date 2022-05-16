//
// Created by Ryan Evans on 5/4/22.
//

#include "CPU.hpp"
#include "HoldQueueTwo.hpp"
#include <iostream>

using namespace std;

CPU::CPU(int mainMemory, int serialDevices, int timeQuantum) {
    MAIN_MEMORY = mainMemory;
    SERIAL_DEVICES = serialDevices;
    TIME_QUANTUM = timeQuantum;
    memoryUsed = 0;
    devicesUsed = 0;
    currentJob = nullptr;
    processArr = new vector<Process>(serialDevices);
    for (int i = 0; i < serialDevices; i++) {
        processArr->at(i).isUsed = false;
        processArr->at(i).jobUsing = nullptr;
    }
}

int CPU::getTimeQuantum() const {
    return TIME_QUANTUM;
}

void CPU::updateCurrentJob(QueueNode *newJob) {
    currentJob = newJob ;
}

/**
 * Calculated the available amount of memory by subtracting the memory used from the total memory
 */
int CPU::getAvailableMemory() const {
    return MAIN_MEMORY - memoryUsed;
}

int CPU::getAvailableDevices() const {
    return SERIAL_DEVICES - devicesUsed;
}

void CPU::printCurrentJob() {
    cout << "-----------------------------------" << endl;
    cout << "Job ID    Time Accrued    Time Left" << endl;
    cout << "===================================" << endl;
    if (currentJob != nullptr) {
        cout << "   " << currentJob->job->jobNumber;
        cout << "           ";
        cout << currentJob->job->timeRanFor;
        cout << "            ";
        cout << currentJob->job->getRemainingTime();
        cout << endl;
    }
    cout << endl;
}

/**
 *
 * @param testNode QueueNode - holding the the jobs being requested
 * @param devReq int - Number of devices being requested by the job
 * @param inWaitQueue bool - True if device is in wait queue, false if the device isn't in the wait queue
 * @param ready - ReadyQueue - The system's Ready queue
 * @param wait - WaitQueue - The system's Wait queue
 * @return true if request was safe & devices were allocated, false if request wasn't safe
 */
bool CPU::bankerAlg(QueueNode* testNode, int devReq, bool inWaitQueue, ReadyQueue* ready, WaitQueue* wait){
    /*
    takes the current active job in the CPU, and checks if it can safely receive the devices it has requested
    testNode is the Node holding the Job that is requesting the devices
    inWaitQueue handles the case of whether or not this call is being made from the CPU or the WaitQueue

    devReq is the number of devices being requested by testJob
    */
    Job* testJob = testNode->job;
    int available = getAvailableDevices();
    if(available >= devReq){
        HoldQueueTwo* deviceList = new HoldQueueTwo();
        //gets all of the unique jobs currently holding resources, by pulling from the process
        deviceList->addBank(testJob);
        for(int i=0; i < SERIAL_DEVICES; i++){
            if(processArr->at(i).isUsed){
                deviceList->addBank(processArr->at(i).jobUsing);
            }
        }

        //array holding the relevant device info from the list
        //first row holds held, second row holds max needed
        int simDeviceArray[deviceList->length][2];
        QueueNode* holder = deviceList->head;
        simDeviceArray[0][0] += devReq;
        //populates the array with the current number of devices held by each process
        for(int i=0; i<deviceList->length; i++){
            simDeviceArray[i][0] += holder->job->devicesHeld;
            simDeviceArray[i][1] = holder->job->maxDevices;
            holder = holder->next;
        }
        //frees memory to prevent garbage
        int deviceListSize = deviceList->length;
        delete deviceList;
        //the actual algorithm, checks if the state is safe.
        //once a process is known to be able to finish, its corresponding array value is set to -1
        //if the array does not finish with all -1, the the state is not safe
        bool modsMade = true;
        while(modsMade){
            modsMade = false;
            for(int j=0; j<deviceListSize; j++){
                if(simDeviceArray[j][0] != -1 && simDeviceArray[j][1]-simDeviceArray[j][0] <= available){
                    available += simDeviceArray[j][0];
                    simDeviceArray[j][0] = -1;
                    modsMade = true;
                }
            }
        }
        //checks to see if all of array are -1
        bool isSafe = true;
        for(int i=0; i<deviceListSize; i++){
            if(simDeviceArray[i][0] != -1){
                isSafe = false;
            }
        }
        //conditional for if the allocation can legally be made
        if(isSafe){
            //makes the changes, sinc it's safe
            testJob->devicesHeld += devReq;
            devicesUsed += devReq;
            int dedicate = 0;
            int processIterator = 0;
            while(dedicate < devReq){
                if(!processArr->at(processIterator).isUsed){
                    processArr->at(processIterator).isUsed = true;
                    processArr->at(processIterator).jobUsing = testJob;
                    dedicate++;
                }
                processIterator++;
            }
            if(inWaitQueue){
                //Moves to the ready queue now that the request is filled
                testJob->lastDevicesRequest = 0;
                QueueNode* removedJob = wait->deQueueBank(testJob);
                ready->queueTask(removedJob);
            }
            return true;
        }
        //if not safe, goes to next part below
    }
    //What to do if not enough resources exist for the request
    if(!inWaitQueue){
        //If it was in the CPU and failed, then it moves to the wait queue
        testJob->lastDevicesRequest = devReq;
        wait->queueTask(testNode);
        currentJob = nullptr;
    }
    //else, nothing is done about it
    return false;
}

void CPU::releaseDevice(QueueNode* freeNode, int devRelease, bool releaseAll){
    //Frees the specified number of devices
    if(releaseAll){
        devRelease = freeNode->job->devicesHeld;
    }
    freeNode->job->devicesHeld -= devRelease;
    devicesUsed -= devRelease;
    int numFreed = 0;
    int processIterator = 0;
    while(numFreed <= devRelease){
        if(processArr->at(processIterator).isUsed && processArr->at(processIterator).jobUsing->jobNumber == freeNode->job->jobNumber){
            processArr->at(processIterator).isUsed = false;
            processArr->at(processIterator).jobUsing = nullptr;
            numFreed +=1;
        }
        processIterator += 1;
    }
}

void CPU::setMemoryUsed(int jobsMaxMemory, bool isFreed) {
    if (!isFreed) {
        CPU::memoryUsed += jobsMaxMemory;
    }
    else {
        CPU::memoryUsed -=jobsMaxMemory;
    }
}

int CPU::getMainMemory() const {
    return MAIN_MEMORY;
}

QueueNode *CPU::getCurrentJob(){
    return currentJob;
}