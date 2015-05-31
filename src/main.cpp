<<<<<<< HEAD
#include <iostream>
#include "pattern.h"
using namespace std;

#define INIT_CAND_NUM 4

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
    gen_Gene(initExp[i]);
  
  for(int i=0; i < ITER_NUM; ++i){
    Example* seleteExp = findBest(initExp); // return INIT_CAND_NUM / 2 number of Example
    
    for(int i=0; i < INIT_CAND_NUM; ++i){
      if(i < INIT_CAND_NUM/2)
        tmpExp[i] = seleteExp[i];
      else
        gen_Gene(tmpExp[i]);
    }
  }

  return 0;
}
=======
#include <iostream>
#include "pattern.h"
using namespace std;

int main(int argc, char **argv)
{
  Pattern pat;
  pat.readfile( argv[1] );
  pat.nodeInitailize();
  pat.edgeInitailize();
  pat.findcomponent();
  pat.color_comps();

  // for(int i = 0 ; i < pat._compSize ; i++)
  //   cout << "#" << i+1 <<" "<<pat._comps[i]->_colorable << endl;

  return 0;
}
>>>>>>> component
