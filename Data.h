#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Process.h"
using namespace std;

class Data
{
private:
    int Type;
    int time_quantum; // this is used for Schedule Round Robin 
    vector<Process> process;

    // Private functions
    bool loadfromFile(char* inputFile);

public: 
    Data(){}
    Data(char* inputfile);

    vector<Process> getProcess()
    {
        return process; 
    }
    int getType()
    {
        return Type;
    }
    int getTime_quantum()
    {
        return time_quantum;
    }
};