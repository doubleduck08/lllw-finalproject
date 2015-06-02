#include <cstdlib>
#include <time.h>
#include <string>
#include "pattern.h"
using namespace std;

string example[8];

void genexample () {
    srand(time(0));
    for (int i=0 ; i<8 ; i++)
       for (int j=0 ; j<Pattern._comp.size() ; j++)
           example[i].append('0'+rand()%2);
}
