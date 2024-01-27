#pragma once
#include "ShedulingAlgorithm.h"

class RoundRobin : public Sheduling
{
private:
    int time_quantum;

public:
    RoundRobin(Data d) : Sheduling(d.getProcess())
    {
        time_quantum = d.getTime_quantum();
    }
    void Run() override;
};