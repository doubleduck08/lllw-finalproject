#include <iostream>
#include "pattern.h"
using namespace std;
# include <algorithm>
# include <ctime>
# include <cstdlib>

bool sortByWinNum(Component *i, Component *j)
{
  return (i->_winInComp.size() > j->_winInComp.size());
}
bool sortByDiffSum(Component *i, Component *j)
{
  return (i->_diffSum > j->_diffSum);
}

int diffGene(Example&, Example&);

int main(int argc, char **argv)
{
  srand(time(NULL));
  Pattern pat;
  pat.readfile( argv[1] );
  //pat.readfile( "input/test1" );
  pat.nodeInitailize();
  pat.edgeInitailize();

  pat.findcomponent();
  pat.color_comps();

  pat.setBox();
  pat.setWindows();
  pat.setGeneBase();
  // for(int i = 0 ; i < pat._compSize ; i++)
  //   cout << "#" << i+1 <<" "<<pat._comps[i]->_colorable << endl;
  Example* best = new Example [2];
  pat.randomBest(best, 2);
  //pat.findbadGene(best[0]);
  cout << pat.finalScore(best[0]) << endl;	
  cout << pat.finalScore(best[1]) << endl;	

  while(pat.seletSameGene(best[0], best[1])){
    //  cout << pat._colorCompsSize << endl;	
    cout << "_colorCompsSize = "<< pat._colorCompsSize << endl;
    cout << " diff = " << diffGene(best[0], best[1]) << endl;
  }

  cout << pat.finalScore(best[0]) << endl;	
  
  cout <<"====="<<endl;

  Example tmp = pat.statistics();
  cout << pat.finalScore(tmp) << endl;
  
  //version 1
  /*
     Example parUnsort;
     Example parSort;
     Example parDiffSumSort;
     pat.genGene(parUnsort);
     pat.genGene(parSort);
     pat.genGene(parDiffSumSort);

     pat.greedy(parUnsort);

     sort(pat._colorComps.begin(), pat._colorComps.end(), sortByWinNum);
     pat.greedy(parSort);
     sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
     pat.greedy(parDiffSumSort);
     cout << "unsort = " << pat.finalScore(parUnsort) << endl;
     cout << "sort = " << pat.finalScore(parSort) << endl;
     cout << "diff = " << pat.finalScore(parDiffSumSort) << endl;
   */
  return 0;
}

int diffGene(Example& ex1, Example& ex2)
{ 
  int same = 0;
  int size = ex1._colorGene.size();
  for(int i=0; i < size; ++i){
    if(ex1._colorGene[i] == ex2._colorGene[i])
      ++same;
  }
  return same;
}
