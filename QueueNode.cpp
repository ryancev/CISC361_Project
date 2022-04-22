//
// Created by Ryan Evans on 4/20/22.
//

#include "QueueNode.hpp"

QueueNode::QueueNode(Job *j) {
    next = nullptr;
    job = j;
}
