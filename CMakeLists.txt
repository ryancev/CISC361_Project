cmake_minimum_required(VERSION 3.21)
project(361_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(361_Project main.cpp Job.cpp Job.hpp HoldQueueOne.cpp HoldQueueOne.hpp HoldQueueTwo.cpp HoldQueueTwo.hpp QueueNode.cpp QueueNode.hpp CPU.cpp CPU.hpp CompleteQueue.cpp CompleteQueue.hpp ReadyQueue.cpp ReadyQueue.hpp WaitQueue.cpp WaitQueue.hpp)
