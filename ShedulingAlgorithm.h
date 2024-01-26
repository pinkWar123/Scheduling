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
    void WriteIntoFile(const char* filename)
    {

    }
    virtual void Run() = 0;
};