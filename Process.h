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
};