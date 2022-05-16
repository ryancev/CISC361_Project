//
// Created by Ryan Evans on 5/14/22.
//


#include <iostream>
#include "WaitQueue.hpp"

using namespace std;

WaitQueue::WaitQueue() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

QueueNode *WaitQueue::deQueueBank(Job* newJob){
    //Special instance of dequeueing for banker algorithm applications
    //While device requests are checked in FIFO order, they may not be fulfillable in that order
    QueueNode* holder = head;
    if(holder->job = newJob){
        head = holder->next;
    }else{
        while(holder->next->job!=newJob){
            holder = holder->next;
        }
        QueueNode* holder2 = holder;
        holder = holder->next;
        if(holder == tail){
            tail = holder2;
            holder2->next = nullptr;
        }else{
            holder2->next = holder->next;
        }
    }
    holder->next = nullptr;
    length--;
    return holder;
}

void WaitQueue::printHoldQueue() {
    QueueNode *iterationNode = head;
    cout << "----------------------------------" << endl;
    cout << "Job ID    Run Time    Time Accrued" << endl;
    cout << "==================================" << endl;
    while (iterationNode != nullptr) {
        cout << "   " << iterationNode->job->jobNumber;
        if (iterationNode->job->runningTime < 10) {
            cout << "          ";
        } else {
            cout << "         ";
        }
        cout << iterationNode->job->runningTime;
        cout << "             ";
        cout << iterationNode->job->timeRanFor;
        cout << endl;
        iterationNode = iterationNode->next;
    }
    cout << endl;
}
