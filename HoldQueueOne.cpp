//
// Created by Ryan Evans on 4/20/22.
//

#include "HoldQueueOne.hpp"
#include "QueueNode.hpp"
#include <iostream>

using namespace std;


/**
 * Default Constructor: Initializes the head and tail pointers to nullptr
 */
HoldQueueOne::HoldQueueOne() {
    head = nullptr;
    tail = nullptr;
}

/**
 * Inserts a node in SJF order into the linked list.
 * O(n) runtime, on length of queue.
 * param nodeToInsert The node that will be inserted into the linked list
 * note: double-check code
 */
void HoldQueueOne::insertInOrder(QueueNode *nodeToInsert) {
    QueueNode *holder = head;
    if (head == nullptr && tail == nullptr) {
        head = nodeToInsert;
        tail = nodeToInsert;
    } else {
        if(nodeToInsert->job->runningTime < head->job->runningTime){
            nodeToInsert->next = head;
            head = nodeToInsert;
        }
        else{
            while(holder->next != nullptr &&  nodeToInsert->job->runningTime > holder->next->job->runningTime){
                holder = holder->next;
            }
            if(holder->next != nullptr){
                nodeToInsert->next = holder->next;
                holder->next = nodeToInsert;
            }
            else{
                holder->next = nodeToInsert;
                nodeToInsert->next = nullptr;
                tail = nodeToInsert;
            }
        }
    }
}

static void makeLines() {
}

static void makeThickLines() {
}

/**
 * Prints out the command codes of the jobs in the linked list - currently for debugging purposes
 */
void HoldQueueOne::printHoldQueue() {
    QueueNode *iterationNode = head;
    cout << "-------------------------" << endl;
    cout << "Job ID    Run Time" << endl;
    while (iterationNode != nullptr) {
        cout << "   " << iterationNode->job->jobNumber << "         " << iterationNode->job->runningTime;
        cout << endl;
        iterationNode = iterationNode->next;
    }
    cout << "=========================" << endl;
    cout << endl;
}

QueueNode* HoldQueueOne::popTask(){
    QueueNode *holder = head;
    head = holder->next;
    return holder;
}