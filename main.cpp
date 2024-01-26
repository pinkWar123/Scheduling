#include <iostream>
#include <string.h>
#include "Data.h"
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
        cout << "Wrong syntax" << endl;
    else{
        Data d(argv[1]);
        
    }
    return 0;
}