//
// Created by Ryan Evans on 5/4/22.
//

#ifndef INC_361_PROJECT_CPU_HPP
#define INC_361_PROJECT_CPU_HPP


#include "Job.hpp"

class CPU {
    /** Max allocatable memory for this system */
    int MAIN_MEMORY;
    /** Max allocatable devices for this system */
    int SERIAL_DEVICES;
    /** How long jobs are allowed to run for */
    int TIME_QUANTUM;
    /** Current amount of memory being used */
    int memoryUsed;
    /** Current number of devices being used */
    int devicesUsed;
    /** The job that is currently running on the CPU */
    Job *currentJob;
public:
    CPU(int mainMemory, int serialDevices, int timeQuantum);
};


#endif //INC_361_PROJECT_CPU_HPP
