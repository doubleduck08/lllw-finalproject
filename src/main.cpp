#include <iostream>
#include "pattern.h"
using namespace std;

#define INIT_CAND_NUM 4
#define ITER_NUM 100

int main(int argc, char **argv)
{
  Pattern pat;
  pat.readfile( argv[1] );
  pat.nodeInitailize();
  pat.edgeInitailize();

  pat.findcomponent();
  pat.color_comps();

  pat.setBox();
  pat.setWindows();
  pat.setGeneBase();
  // for(int i = 0 ; i < pat._compSize ; i++)
  //   cout << "#" << i+1 <<" "<<pat._comps[i]->_colorable << endl;
  Example initExp[INIT_CAND_NUM];
  Example tmpExp[INIT_CAND_NUM];

  for(int i=0; i < INIT_CAND_NUM; ++i)
    pat.genGene(initExp[i]);
  
  for(int i=0; i < ITER_NUM; ++i){
    Example* seleteExp = pat.findbest(initExp); // return INIT_CAND_NUM / 2 number of Example
    
    for(int i=0; i < INIT_CAND_NUM; ++i){
      if(i < INIT_CAND_NUM/2)
        tmpExp[i] = seleteExp[i];
      else
        pat.genGene(tmpExp[i]);
    }
  }

  return 0;
}
