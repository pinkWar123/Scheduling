#pragma once
#include "SchedulingAlgorithm.h"

class FCFS : public Scheduling
{
public:
    FCFS(Data &d);
    void Run();
};