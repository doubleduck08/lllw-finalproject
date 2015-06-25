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
  /*Example* best = new Example [2];
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
  */

  cout << "=== Greedy ===" << endl;
  
  Example tmp;
  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum)
  pat.greedy(tmp, 0);
  pat.measureArea(tmp);
  cout << pat.finalScore(tmp) << endl;

  cout << "=== Shuffle ===" << endl;
  
  for(int i = 0 ; i < 10 ; i++) {
    random_shuffle ( pat._colorComps.begin(), pat._colorComps.end() );
    pat.greedy(tmp,0);
    pat.measureArea(tmp);
    cout << pat.finalScore(tmp) << endl;
  }

  cout <<"=== Shuffle && Statistics ==="<<endl;

  //sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
  tmp = pat.statistics();
  pat.measureArea(tmp);
  cout << pat.finalScore(tmp) << endl;
  
  //version 1

     //Example parUnsort;
     //Example parSort;
     //Example parDiffSumSort;
/*
     pat.greedy(parUnsort);
     cout << "unsort = " << pat.finalScore(parUnsort) << endl;

     sort(pat._colorComps.begin(), pat._colorComps.end(), sortByWinNum);
     cout << pat._colorComps[0]->_id<<endl;
     pat.greedy(parSort);
     cout << "sort = " << pat.finalScore(parSort) << endl;
     
     sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
  */
     /*
     Example ee1, ee2;
     for(int i=1; i<pat._colorCompsSize; ++i){ 
       pat.greedy(parDiffSumSort,i);
       cout << "#" << i << " score = " << pat.finalScore(parDiffSumSort) << endl;
       if(i == 17) ee1 = parDiffSumSort;
       if(i == 18) ee2 = parDiffSumSort; 
     }
       cout << diffGene(ee1,ee2) <<endl;
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
