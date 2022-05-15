//
// Created by Ryan Evans on 5/14/22.
//


#include <iostream>
#include "WaitQueue.hpp"

using namespace std;

WaitQueue::WaitQueue() {
    head = nullptr;
    tail = nullptr;
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
