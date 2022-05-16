//
// Created by Ryan Evans on 5/14/22.
//

#ifndef INC_361_PROJECT_WAITQUEUE_HPP
#define INC_361_PROJECT_WAITQUEUE_HPP

#include "HoldQueueTwo.hpp"

class WaitQueue : public HoldQueueTwo {
public:
    WaitQueue();
    QueueNode* deQueueBank(Job* newJob);
    void printHoldQueue() override;
};


#endif //INC_361_PROJECT_WAITQUEUE_HPP
