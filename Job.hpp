//
// Created by Ryan Evans on 4/20/22.
//

#ifndef INC_361_PROJECT_JOB_HPP
#define INC_361_PROJECT_JOB_HPP

/**
 * Object to represent a job
 */
class Job {
    // A = Job Arrival
    //    A __ = Arrives at time __
    //    J =    Job number
    //    M __ = Units of main memory required
    //    S __ = Max devices at any point during execution
    //    R = Running time
    //    P __ = Priority number
public:
    int arrivalTime;
    int jobNumber;
    int memoryNeeded;
    int maxDevices;
    int runningTime;
    int priorityNumber;

    Job(int arrivalTime, int jobNumber, int memoryNeeded, int maxDevices, int runningTime, int priorityNumber);
};


#endif //INC_361_PROJECT_JOB_HPP
