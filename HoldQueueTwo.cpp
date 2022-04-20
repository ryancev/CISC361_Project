//
// Created by Ryan Evans on 4/20/22.
//

#include "HoldQueueTwo.hpp"
#include <iostream>

/**
 * Default Constructor: Initializes the head and tail pointers to nullptr
 */
HoldQueueTwo::HoldQueueTwo() {
    head = nullptr;
    tail = nullptr;
}

/**
 * Inserts a node at the front of the linked list.
 *
 * @param nodeToInsert The node that will be inserted into the linked list
 */
void HoldQueueTwo::insertAtFront(QueueNode *nodeToInsert) {
    if (head == nullptr && tail == nullptr) {
        head = nodeToInsert;
        tail = nodeToInsert;
    }
    else {
        nodeToInsert->next = head;
        head = nodeToInsert;
    }
}

/**
 * Prints out the command codes of the jobs in the linked list - currently for debugging purposes
 */
void HoldQueueTwo::printHoldQueue() {
    QueueNode *iterationNode = head;
    while (iterationNode != nullptr) {
        std::cout << iterationNode->job->commandCode << " ";
        iterationNode = iterationNode->next;
    }
}