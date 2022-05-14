//
// Created by Ryan Evans on 5/14/22.
//

#ifndef INC_361_PROJECT_READYQUEUE_HPP
#define INC_361_PROJECT_READYQUEUE_HPP


#include "HoldQueueTwo.hpp"

class ReadyQueue : public HoldQueueTwo {
public:
    ReadyQueue();
    void printHoldQueue() override;
};


#endif //INC_361_PROJECT_READYQUEUE_HPP
