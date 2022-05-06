//
// Created by Ryan Evans on 4/20/22.
//

#ifndef INC_361_PROJECT_HOLDQUEUETWO_HPP
#define INC_361_PROJECT_HOLDQUEUETWO_HPP


#include "QueueNode.hpp"

class HoldQueueTwo {
public:
    QueueNode *head;
    QueueNode *tail;
    HoldQueueTwo();
    void insertAtFront(QueueNode *nodeToInsert);
    void printHoldQueue();
    QueueNode* popTask();
};


#endif //INC_361_PROJECT_HOLDQUEUETWO_HPP
