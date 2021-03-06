//
// Created by Ryan Evans on 5/13/22.
//

#ifndef INC_361_PROJECT_COMPLETEQUEUE_HPP
#define INC_361_PROJECT_COMPLETEQUEUE_HPP


#include "HoldQueueTwo.hpp"

class CompleteQueue : public HoldQueueTwo {
public:
    CompleteQueue();
    void printHoldQueue() override;
    double calculateAvgTurnaround();
    void printAvgTurnaround();
    void insertInOrder(QueueNode *nodeToInsert);
};


#endif //INC_361_PROJECT_COMPLETEQUEUE_HPP
