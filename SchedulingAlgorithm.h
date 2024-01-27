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

public:
    Scheduling() {}
    Scheduling(vector<Process> p)
    {
        this->process = p;
    }
    void CalculateTime()
    {
        for (int i = 0; i < process.size(); i++)
        {
            int timeCompleted1 = 0;
            int timeCompleted2 = 0;
            for (int j = 0; j < CPUScheduling.size(); j++)
            {
                if (CPUScheduling[j] == process[i].ID)
                    timeCompleted1 = j;
            }
            for (int j = 0; j < ResourceScheduling.size(); j++)
            {
                if (ResourceScheduling[j] == process[i].ID)
                    timeCompleted2 = j;
            }

            int total = 0;
            for (int j = process[i].ArrivalTime; j < CPUScheduling.size(); j++)
                if (CPUScheduling[j] != process[i].ID)
                    ++total;
            process[i].turnArroundTime = max(timeCompleted1, timeCompleted2) - process[i].ArrivalTime + 1;
            // process[i].WaitTime = total;
        }
    }

    void UpdateWaitingTime()
    {
        for (int i = 1; i < cpuQueue.size(); i++)
        {
            int id = cpuQueue[i].ID;
            process[id - 1].WaitTime++;
        }
    }

    void WriteIntoFile(const char *filename)
    {
        CalculateTime();
        ofstream os(filename);
        for (int i = 0; i < CPUScheduling.size(); i++)
        {
            if (CPUScheduling[i] == -1)
                os << "_";
            else
                os << CPUScheduling[i];

            os << " ";
        }
        os << endl;
        for (int i = 0; i < ResourceScheduling.size(); i++)
        {
            if (ResourceScheduling[i] == -1)
                os << "_";
            else
                os << ResourceScheduling[i];

            os << " ";
        }
        os << endl;
        for (int i = 0; i < process.size(); i++)
        {
            os << process[i].turnArroundTime << " ";
        }
        os << endl;
        for (int i = 0; i < process.size(); i++)
        {
            os << process[i].WaitTime << " ";
        }
        os.close();
    }
    virtual void Run() = 0;
};