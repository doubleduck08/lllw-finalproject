#include <cstdlib>
#include <time.h>
#include <string>
#include "pattern.h"
using namespace std;

void gen_gene (Example& exa) {
    srand(time(0));
    for (int j=0 ; j<Pattern.color_comp.size() ; j++)
        exa.colorGene.push_back(rand()%2);
}
