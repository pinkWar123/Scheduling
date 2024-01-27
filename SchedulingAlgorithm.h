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

    queue<Process> cpuQueue;
    queue<Process> ioQueue;

    vector<int> CPUScheduling;
    vector<int> ResourceScheduling;

public:
    Scheduling(vector<Process> p)
    {
        this->process = p;
    }
    void WriteIntoFile(const char *filename)
    {
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
        os.close();
    }
    virtual void Run() = 0;
};