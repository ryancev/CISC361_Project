#ifndef INC_361_PROJECT_HOLDQUEUEONE_HPP
#define INC_361_PROJECT_HOLDQUEUEONE_HPP


#include "QueueNode.hpp"

class HoldQueueOne {
public:
    QueueNode *head;
    QueueNode *tail;
    int length;
    HoldQueueOne();
    void insertInOrder(QueueNode *nodeToInsert);
    void printHoldQueue();
    QueueNode* popTask();
};


#endif //INC_361_PROJECT_HOLDQUEUEONE_HPP