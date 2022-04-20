//
// Created by Ryan Evans on 4/20/22.
//

#ifndef INC_361_PROJECT_QUEUENODE_HPP
#define INC_361_PROJECT_QUEUENODE_HPP


#include "Job.hpp"

class QueueNode {
public:
    Job *job;
    QueueNode *next;
    QueueNode(Job *j);
};


#endif //INC_361_PROJECT_QUEUENODE_HPP
