//
// Created by Ryan Evans on 4/20/22.
//

#include "Job.hpp"

Job::Job(int arrivalTime, int jobNumber, int memoryNeeded, int maxDevices, int runningTime, int priorityNumber) {
    Job::arrivalTime = arrivalTime;
    Job::jobNumber = jobNumber;
    Job::memoryNeeded = memoryNeeded;
    Job::maxDevices = maxDevices;
    Job::priorityNumber = priorityNumber;
    Job::runningTime = runningTime;
}