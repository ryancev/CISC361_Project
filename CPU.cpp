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
    processArr = new Process[serialDevices];
    for (int i = 0; i < serialDevices; i++) {
        processArr[i].isUsed = false;
        processArr[i].jobUsing = nullptr;
    }
}

void CPU::updateCurrentJob(Job *newJob) {
    currentJob = newJob ;
}

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
        cout << "   " << currentJob->jobNumber;
        cout << "           ";
        cout << currentJob->runningTime;
        cout << "            ";
        cout << currentJob->getRemainingTime();
        cout << endl;
    }
    cout << endl;
}

void CPU::bankerAlg(Job* testJob, int devReq){
    //takes the current active job in the CPU, and checks if it can safely receive the devices it has requested
    //testJob is the job requesting the devices
    //devReq is the number of devices being requested by testJob
    int available = getAvailableDevices();
    if(available >= devReq){
        HoldQueueTwo* deviceList = new HoldQueueTwo();
        //gets all of the unique jobs currently holding resources
        deviceList->addBank(testJob);
        for(int i=0; i < SERIAL_DEVICES; i++){
            if(processArr[i].isUsed){
                deviceList->addBank(processArr[i].jobUsing);
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
        delete deviceList;
        //the actual algorithm, checks if the state is safe.
        //once a process is known to be able to finish, its corresponding array value is set to -1
        //if the array does not finish with all -1, the the state is not safe
        bool modsMade = true;
        while(modsMade){
            modsMade = false;
            for(int j=0; j<deviceList->length; j++){
                if(simDeviceArray[j][0] != -1 && simDeviceArray[j][1]-simDeviceArray[j][0] <= available){
                    available += simDeviceArray[j][0];
                    simDeviceArray[j][0] = -1;
                    modsMade = true;
                }
            }
        }
        //checks to see if all of array are -1
        bool isSafe = true;
        for(int i=0; i<deviceList->length; i++){
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
                if(!processArr[processIterator].isUsed){
                    processArr[processIterator].isUsed = true;
                    processArr[processIterator].jobUsing = testJob;
                    dedicate++;
                }
                processIterator++;
            }
        }else{
            //what to do if it's not safe???
        }
    }else{
        //what to do if not enough resources exist to begin with???
    }
}