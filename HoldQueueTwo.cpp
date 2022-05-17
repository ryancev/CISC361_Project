//
// Created by Ryan Evans on 4/20/22.
//

#include "HoldQueueTwo.hpp"
#include <iostream>


using namespace std;

/**
 * Default Constructor: Initializes the head and tail pointers to nullptr
 */
HoldQueueTwo::HoldQueueTwo() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

/**
 * Inserts a node at the front of the linked list.
 *
 * @param nodeToInsert The node that will be inserted into the linked list
 */
void HoldQueueTwo::queueTask(QueueNode *nodeToInsert) {
    if (head == nullptr && tail == nullptr) {
        head = nodeToInsert;
        tail = nodeToInsert;
    }
    else {
        tail->next = nodeToInsert;
        tail = nodeToInsert;
    }
    tail->next = nullptr;
    length++;
}

void HoldQueueTwo::addBank(Job* newJob){
    //Special instance of adding for banker algorithm
    //adding a node to this list requires creating a new instance of the QueueNode, to make sure no pointers are "damaged"
    //adds only unique instances of jobs to the SLL
    QueueNode* holder = head;
    if(holder == nullptr){
        QueueNode* add = new QueueNode(newJob);
        head = add;
        tail = add;
        length++;
    }else{
    while(holder->next != nullptr && holder->job->jobNumber != newJob->jobNumber){
        holder = holder->next;
    }
        if(holder->next == nullptr){
            if(holder->job->jobNumber != newJob->jobNumber){
                QueueNode* add = new QueueNode(holder->job);
                tail->next = add;
                tail = add;
                length++;
            }
        }
    }
}


/**
 * Prints out the command codes of the jobs in the linked list - currently for debugging purposes
 */
void HoldQueueTwo::printHoldQueue() {
    QueueNode *iterationNode = head;
    cout << "-------------------------" << endl;
    cout << "Job ID    Run Time" << endl;
    cout << "=========================" << endl;
    while (iterationNode != nullptr) {
        cout << "   " << iterationNode->job->jobNumber;
        if (iterationNode->job->runningTime < 10) {
            cout << "          ";
        } else {
            cout << "         ";
        }
        cout << iterationNode->job->runningTime;
        cout << endl;
        iterationNode = iterationNode->next;
    }
    cout << endl;
}

QueueNode* HoldQueueTwo::deQueueTask(){
    QueueNode *holder = head;
    head = holder->next;
    length--;
    if(head == nullptr){
        tail = nullptr;
    }
    return holder;
}

HoldQueueTwo::~HoldQueueTwo(){
    QueueNode* holder = head;
    QueueNode* holder2 = holder;
    if(holder != nullptr){
        while(holder2 != nullptr){
            holder2 = holder2->next;
            delete holder;
            holder = holder2;
        }
    }
}