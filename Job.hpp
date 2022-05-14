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
    int finishTime = 0;
    int turnAroundTime = 0;
    int timeRanFor = 0;

    int getTimeRanFor() const;

    /**
     * Constructor: Creates a new job with the specified parameters
     *
     * @param arrivalTime The time that the job arrived at
     * @param jobNumber A number representing this job
     * @param memoryNeeded Amount of memory needed for the job
     * @param maxDevices The max devices needed at any point during execution
     * @param runningTime The amount of time that the job will run for
     * @param priorityNumber A number representing the priority of the job
     */
    Job(int arrivalTime, int jobNumber, int memoryNeeded, int maxDevices, int runningTime, int priorityNumber);

    int getTurnAroundTime() const;
};


#endif //INC_361_PROJECT_JOB_HPP
