#pragma once
#include "SchedulingAlgorithm.h"

class RoundRobin : public Scheduling
{
private:
    int time_quantum;

public:
    RoundRobin(Data d) : Scheduling(d.getProcess())
    {
        time_quantum = d.getTime_quantum();
    }
    void Run() override;
};