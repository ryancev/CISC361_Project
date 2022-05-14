//
// Created by Ryan Evans on 5/13/22.
//

#include "CompleteQueue.hpp"
#include <iostream>

using namespace std;

CompleteQueue::CompleteQueue() {
    head = nullptr;
    tail = nullptr;
}


static void makeLines() {
    int numLines = 56;
    for (int i = 0; i < numLines; i++) {
        cout << "-";
    }
    cout << endl;
}

static void makeThickLines() {
    int numLines = 56;
    for (int i = 0; i < numLines; i++) {
        cout << "=";
    }
    cout << endl;
}

void CompleteQueue::printHoldQueue() {
    makeLines();
    cout << "Job ID    Arrival Time    Finish Time    Turnaround Time" << endl;
    makeThickLines();
    QueueNode *iterationNode = head;
    while (iterationNode != nullptr) {
        cout << "   " << iterationNode->job->jobNumber << "           " << iterationNode->job->arrivalTime;
        if (iterationNode->job->arrivalTime < 10) {
            cout << "               ";
        } else {
            cout << "              ";
        }
        cout << iterationNode->job->finishTime;
        cout << "                " << iterationNode->job->getTurnAroundTime() << endl;
        iterationNode = iterationNode->next;
    }
    makeLines();
}

