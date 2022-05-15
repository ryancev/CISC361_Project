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
    /** The time that this job arrived at */
    int arrivalTime;
    /** The number representing the job */
    int jobNumber;
    /** The max amount of memory needed for the job */
    int memoryNeeded;
    /** The max number of devices that the job will ever request */
    int maxDevices;
    /** The total amount of time that the job will run (lifetime) */
    int runningTime;
    /** The number representing the job's level of priority*/
    int priorityNumber;
    /** The time that this job was completed at, 0 by default*/
    int finishTime = 0;
    /** The finish time minus the arrival time, calculated with getTurnAroundTime()*/
    int turnAroundTime = 0;
    /** The amount of time that the job has spent running on the CPU */
    int timeRanFor = 0;
    /** The current number of devices being held by this job */
    int devicesHeld = 0;
    /** Getter: Returns the number of time spent running on the CPU*/
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
    int getRemainingTime() const;
};


#endif //INC_361_PROJECT_JOB_HPP
