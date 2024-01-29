#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Process
{
public:
    int ID;
    int ArrivalTime;
    vector<int> CPUBurstTime;
    vector<int> ResourceBurstTime;

    int turnArroundTime = 0;
    int WaitTime = 0;

    friend void swap(Process& first, Process& second) noexcept {
        using std::swap;
        swap(first.ID, second.ID);
        swap(first.ArrivalTime, second.ArrivalTime);
        swap(first.CPUBurstTime, second.CPUBurstTime);
        swap(first.ResourceBurstTime, second.ResourceBurstTime);
        swap(first.turnArroundTime, second.turnArroundTime);
        swap(first.WaitTime, second.WaitTime);
    }
};