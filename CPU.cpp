//
// Created by Ryan Evans on 5/4/22.
//

#include "CPU.hpp"

CPU::CPU(int mainMemory, int serialDevices, int timeQuantum) {
    MAIN_MEMORY = mainMemory;
    SERIAL_DEVICES = serialDevices;
    TIME_QUANTUM = timeQuantum;
    memoryUsed = 0;
    devicesUsed = 0;
    currentJob = nullptr;
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
