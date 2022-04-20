//
// Created by Ryan Evans on 4/20/22.
//

#include "QueueNode.hpp"

QueueNode::QueueNode(Job *j) {
    job = nullptr;
    next = nullptr;
    job = j;
}
