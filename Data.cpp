#include "Data.h"

Data::Data(char *inputFile)
{
    loadfromFile(inputFile);
}

Process getDatafromLine(string line, int ID)
{
    stringstream ss(line);
    int number;
    ss >> number;

    Process result;
    result.ID = ID;
    result.ArrivalTime = number;

    int count = 0;
    while (ss >> number)
    {
        if (count % 2 == 0)
            result.CPUBurstTime.push_back(number);
        else
            result.ResourceBurstTime.push_back(number);

        count++;
    }

    return result;
}

bool Data::loadfromFile(char *inputFile)
{
    ifstream is(inputFile);
    int numberProcess;

    // check error file
    if (!is.is_open())
    {
        cout << "unable to open " << inputFile << endl;
        return false;
    }

    is >> Type;
    if (Type == 2)
        is >> time_quantum;

    is >> numberProcess;
    is.ignore();
    int ID = 1;
    while (numberProcess)
    {
        string line;
        getline(is, line);
        process.push_back(getDatafromLine(line, ID++));
        numberProcess--;
    }
    is.close();
    return true;
}