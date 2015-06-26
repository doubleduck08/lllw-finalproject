# include <iostream>
# include <algorithm>
# include <ctime>
# include <cstdlib>
# include <sstream>
# include "../lib/tm_usage.h"
#include "pattern.h"

using namespace std;

void setting(Pattern &);
void help_message();
bool sortByDiffSum(Component *, Component *);

int main(int argc, char **argv)
{ /*
  if(argc != 3) {
    help_message();
    return 0;
  }
  */
  CommonNs::TmUsage tmusg;
  CommonNs::TmStat stat;

  srand(time(NULL));

  tmusg.periodStart(); 

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

  cout << "final score = " << pat.finalScore(tmp) << ", fixNum = " << pat.fixNum << endl;
  tmusg.getPeriodUsage(stat);

  cout <<"# run time = " << (stat.uTime + stat.sTime) / 1000000.0 << "sec" << endl;
  cout <<"# memory =" << stat.vmPeak / 1000.0 << "MB" << endl;

  return 0;
}

void setting(Pattern &p)
{
  ifstream fin( "./bin/setting.txt" );
  if( fin.fail() ){
    cout << "SETTING FAIL!\n";

    p.RAND_TIME = 1000;
    p.RANDOMBEST =  100;
    p.ITER_NUM = 100;
    p.FINAL_ITER_NUM = 10000;
    p.BOUND_RATIO = 0.75;
    p.BOUND_FIX = 0.9;
    p.NBEST = 30;
    p.AMP_FACTOR = 10;
    p.MUTATION = 2;
    return;
  }

  stringstream ss("");
  string buf, name;
  char ch;
  double num[8];

  for(int i = 0 ; i < 8 ; i++)
  {
    getline(fin, buf);
    ss.str("");
    ss.clear();
    ss << buf;
    ss >> name >> ch >> num[i];
    // cout << name << " = " << num[i] << endl;
  }

  p.RAND_TIME = num[0];
  p.RANDOMBEST =  num[1];
  p.ITER_NUM = num[2];
  p.FINAL_ITER_NUM = num[3];
  p.BOUND_RATIO = num[4];
  p.BOUND_FIX = num[5];
  p.NBEST = num[6];
  p.AMP_FACTOR = num[7];
}

bool sortByDiffSum(Component *i, Component *j)
{
  return (i->_diffSum > j->_diffSum);
}

void help_message() {
  cout << "usage: lllw -[GD|DP] <input_file> <output_file>" << endl;
  cout << "options:" << endl;
  cout << "   GD  - Greedy" << endl;
  cout << "   DP  - Dynamic Programming" << endl;
}
