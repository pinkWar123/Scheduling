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

    int turnArroundTime;
    int WaitTime;
    
};