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
