//
// Created by Ryan Evans on 5/13/22.
//

#include "CompleteQueue.hpp"
#include <iostream>
#include <iomanip>

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

double CompleteQueue::calculateAvgTurnaround() {
    double sumTimes = 0.0;
    double numJobs = 0.0;
    QueueNode *iterationNode = head;
    while (iterationNode != nullptr) {
        sumTimes += iterationNode->job->getTurnAroundTime();
        numJobs++;
        iterationNode = iterationNode->next;
    }
    if (numJobs == 0) return 0;
    return sumTimes / numJobs;
}

void CompleteQueue::printAvgTurnaround() {
    for (int i = 0; i < 33; i++) {
        cout << "-";
    } cout << endl;
    int x = calculateAvgTurnaround()/1;
    int length = 0;
    while(x > 0){
        x /= 10;
        length++;
    }
    cout << "Average System Turnaround Time: "<< setprecision(length + 1) << calculateAvgTurnaround() << endl;
}


void CompleteQueue::insertInOrder(QueueNode *nodeToInsert) {
    QueueNode *holder = head;
    if (head == nullptr && tail == nullptr) {
        head = nodeToInsert;
        tail = nodeToInsert;
    } else {
        if(nodeToInsert->job->jobNumber < head->job->jobNumber){
            nodeToInsert->next = head;
            head = nodeToInsert;
        }
        else{
            while(holder->next != nullptr &&  nodeToInsert->job->jobNumber >= holder->next->job->jobNumber){
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
    length++;
}

