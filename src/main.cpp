# include <iostream>
# include <algorithm>
# include <ctime>
# include <cstdlib>

#include "pattern.h"
using namespace std;

void setting(Pattern&);
bool sortByDiffSum(Component *, Component *);

int main(int argc, char **argv)
{
  srand(time(NULL));

  Pattern pat;
  setting(pat);

  pat.readfile( argv[1] );
  pat.nodeInitailize();
  pat.edgeInitailize();

  pat.findcomponent();
  pat.color_comps();

  pat.setBox();
  pat.setWindows();
  pat.setGeneBase();

  Example max, tmp;
  cout << "=== Random ===" << endl;
  double max_score = 0.0;
  for(int i = 0 ; i < pat.RAND_TIME ; i++)
  {
    pat.genGene(tmp);
    pat.measureArea(tmp);
    tmp._score = pat.finalScore(tmp);

    if(tmp._score > max_score)
    {
      max_score = tmp._score;
      max = tmp;
    }
  }
  cout << "score = " << max._score << endl;

  cout << "=== Greedy ===" << endl;
  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
  pat.greedy(tmp, 0);
  pat.measureArea(tmp);
  cout << "score = " << pat.finalScore(tmp) << endl;

  cout << "=== Shuffle & Greedy ===" << endl;
  for(int i = 0 ; i < 10 ; i++) {
    random_shuffle ( pat._colorComps.begin(), pat._colorComps.end() );
    pat.greedy(tmp,0);
    pat.measureArea(tmp);
    cout << "#" << i << " score = " << pat.finalScore(tmp) << endl;
  }

  cout <<"=== Shuffle & Greedy & Statistics ==="<<endl;
  tmp = pat.statistics();
  pat.measureArea(tmp);
  cout << endl;
  cout << "final score = " << pat.finalScore(tmp) << endl;

  return 0;
}

void setting(Pattern& pat)
{
  pat.RAND_TIME = 1000;
  pat.RANDOMBEST =  100;
  pat.ITER_NUM = 100;
  pat.FINAL_ITER_NUM = 10000;
  pat.BOUND_RATIO = 0.7;
  pat.BOUND_FIX = 0.9;
  pat.NBEST = 30;
  pat.AMP_FACTOR = 20;
}

bool sortByDiffSum(Component *i, Component *j)
{
  return (i->_diffSum > j->_diffSum);
}