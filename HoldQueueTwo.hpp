//
// Created by Ryan Evans on 4/20/22.
//

#ifndef INC_361_PROJECT_HOLDQUEUETWO_HPP
#define INC_361_PROJECT_HOLDQUEUETWO_HPP


#include "QueueNode.hpp"

class HoldQueueTwo {
    friend class CompleteQueue;
public:
    QueueNode *head;
    QueueNode *tail;
    HoldQueueTwo();
    void queueTask(QueueNode *nodeToInsert);

    virtual void printHoldQueue();
    QueueNode* deQueueTask();
};


#endif //INC_361_PROJECT_HOLDQUEUETWO_HPP
