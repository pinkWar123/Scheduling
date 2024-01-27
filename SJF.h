#include "SchedulingAlgorithm.h"

class SJF : public Scheduling
{
private:
    void InsertProcessIntoQueue(Process &other);
public:
    SJF(){}
    SJF(Data &d);

    void Run();
};