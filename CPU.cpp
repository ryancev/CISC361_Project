//
// Created by Ryan Evans on 5/4/22.
//

#include "CPU.hpp"
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

void CPU::bankerAlg(int jobNo, int devReq){
    //takes the current active job in the CPU, and checks if it can safely receive the devices it has requested
    if(currentJob->jobNumber == jobNo && getAvailableDevices() >= devReq){
        
        /*
        int allocation[ready->length + 1];
        QueueNode* holder = ready->head;
        for(int i=0; i < ready->length; i++){
            allocation[i] = holder->job->currentDevicesAlloc;
            holder = holder->next;
        }
        allocation[ready->length] = currentJob->currentDevicesAlloc;
        int simMaxDev = cpu->getMaxDevices();
        int simDevUsed = cpu->getDevicesUsed();
        for(int i=0; i < ready->length + 1; i++){
            int simRelease = -1;
            holder = ready->head;
            for(int j=0; j<ready->length + 1; j++){
                if(allocation[j] != -1 && holder->job->maxDevices - holder->job->currentDevicesAlloc >= simMaxDev-simDevUsed){
                    
                }
                holder = holder->next;
            }
        }
        */
    }else{}
}