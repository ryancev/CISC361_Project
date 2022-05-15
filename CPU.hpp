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
    /**
     * Constructor: Creates a new CPU with a specified amount of main memory, devices, and a given quantum.
     * @param mainMemory The total amount of memory available to the system
     * @param serialDevices The total number of devices available to the system
     * @param timeQuantum The time quantum for the system
     */
    CPU(int mainMemory, int serialDevices, int timeQuantum);
    /**
     * Updates the currentJob field to contain the passed in job
     * @param newJob The job that will become the new currently running job
     */
    void updateCurrentJob(Job *newJob);
    int getAvailableMemory() const;
    int getAvailableDevices() const;
    void printCurrentJob();

    int getMainMemory() const;

    /**
     *
     * @param memoryUsed
     * @param isFreed False if the job is being received, true if the device is being freed
     */
    void setMemoryUsed(int memoryUsed, bool isFreed);

    struct Process {
        /** True if the process is used, false is the process is available */
        bool isUsed;
        /** Contains the job that is currently using the process*/
        Job *jobUsing;
    };
    /** Array containing the processes for the system*/
    Process *processArr;

    Process *returnProcess();
    Job* getCurrentJob();
    void bankerAlg(Job* testJob, int devReq);
};


#endif //INC_361_PROJECT_CPU_HPP
