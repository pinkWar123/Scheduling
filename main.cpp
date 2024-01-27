#include <iostream>
#include <string.h>
#include "Data.h"
#include "RoundRobin.h"
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
        cout << "Wrong syntax" << endl;
    else{
        Data d(argv[1]);
        RoundRobin r(d);
        r.Run();
        r.WriteIntoFile(argv[2]);
    }
    return 0;
}