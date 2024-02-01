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
    int time_quantum; 
    vector<Process> process;

    bool loadfromFile(char *inputFile);

public:
    Data();
    Data(char *inputfile);

    vector<Process> getProcess();
    int getType();
    int getTime_quantum();
};