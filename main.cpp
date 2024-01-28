#include <iostream>
#include <string.h>
#include "Data.h"
#include "RoundRobin.h"
#include "FCFS.h"
#include "SJF.h"
#include "SRTN.h"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
        cout << "Wrong syntax" << endl;
    else
    {
        Data d(argv[1]);
        int type = d.getType();
        Scheduling *algo;
        switch (type)
        {
        case 1:
            algo = new FCFS(d);
            break;
        case 2:
            algo = new RoundRobin(d);
            break;
        case 3:
            algo = new SJF(d);
            break;
        case 4:
            algo = new SRTN(d);
            break;
        }
        algo->Run();
        algo->WriteIntoFile(argv[2]);
        delete algo;
    }
    return 0;
}