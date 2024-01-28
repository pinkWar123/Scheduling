#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <fstream>
#include "Process.h"
#include "Data.h"
using namespace std;

class Scheduling
{
protected:
    vector<Process> process;

    vector<Process> cpuQueue;
    vector<Process> ioQueue;

    vector<int> CPUScheduling;
    vector<int> ResourceScheduling;

    vector<Process> ReadyQueue;

public:
    Scheduling();
    Scheduling(vector<Process> p);
    void CalculateTime();

    void UpdateWaitingTime();
    void UpdateCPUQueue(vector<Process> &p, int time);
    bool UpdateIOQueue(int currentId, int &time);
    bool hasAllProcessesCompleted(vector<Process> &p);
    void SortReadyQueue();

    void WriteIntoFile(const char *filename);
    virtual void Run() = 0;
};