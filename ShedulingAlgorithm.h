#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <fstream>
#include "Process.h"
#include "Data.h"
using namespace std;

class Sheduling
{
protected:
    vector<Process> process;

    queue<Process> cpuQueue;
    queue<Process> ioQueue;

    vector<int> CPUsheduling;
    vector<int> Resourcesheduling;

public:
    Sheduling(vector<Process> p)
    {
        this->process = p;
    }
    void WriteIntoFile(const char *filename)
    {
        ofstream os(filename);
        for (int i = 0; i < CPUsheduling.size(); i++)
        {
            if (CPUsheduling[i] == -1)
                os << "_";
            else
                os << CPUsheduling[i];

            os << " ";
        }
        os << endl;
        for (int i = 0; i < Resourcesheduling.size(); i++)
        {
            if (Resourcesheduling[i] == -1)
                os << "_";
            else
                os << Resourcesheduling[i];

            os << " ";
        }
        os.close();
    }
    virtual void Run() = 0;
};