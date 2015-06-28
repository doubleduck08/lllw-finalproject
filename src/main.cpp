# include <iostream>
# include <algorithm>
# include <ctime>
# include <cstdlib>
# include <sstream>

# include "pattern.h"
# include "../lib/tm_usage.h"

using namespace std;

void setting(Pattern &);
bool sortByDiffSum(Component *, Component *);
bool sortByWinSize(Component *, Component *);
bool sortByWeight(Component *, Component *);

int main(int argc, char **argv)
{
  CommonNs::TmUsage tmusg;
  CommonNs::TmStat stat;
  tmusg.periodStart();
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

  cout << "    DATA OF pat:" << endl;
  cout << "    _nodeSize = " << pat._nodeSize << endl;
  cout << "    _windowSize = " << pat._windowSize << endl;
  cout << "    _compSize = " << pat._compSize << endl;
  cout << "    _colorCompsSize = " << pat._colorCompsSize << endl;
  cout << endl;

  Example max, tmp;
  double max_score = 0.0;
  cout << "    ============== Random ===============" << endl;
  max_score = 0.0;
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
  cout << "    score = " << max_score << endl << endl;

  cout << "    ============== Greedy ===============" << endl;
  pat.resetWeight();  // edit weight of comps
  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
  pat.greedy(tmp, 0);
  pat.measureArea(tmp);
  pat.addWeight(pat.WEIGHTONDIFF);  // edit weight of comps
  // for(int i = 0 ; i < 20 ; i++) cout << pat._colorComps[i]->_id << " "; cout << endl;
  cout << "    score = " << pat.finalScore(tmp) << " (sortByDiffSum)" << endl;


  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByWinSize);
  pat.greedy(tmp, 0);
  pat.measureArea(tmp);
  pat.addWeight(100 - pat.WEIGHTONDIFF);  // edit weight of comps
  // for(int i = 0 ; i < 20 ; i++) cout << pat._colorComps[i]->_id << " "; cout << endl;
  cout << "    score = " << pat.finalScore(tmp) << " (sortByWinSize)" << endl;

  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByWeight);
  pat.greedy(tmp, 0);
  pat.measureArea(tmp);
  // for(int i = 0 ; i < 20 ; i++) cout << pat._colorComps[i]->_id << " "; cout << endl;
  cout << "    score = " << pat.finalScore(tmp) << " (sortByWeight)" << endl << endl;


  cout << "    ========= Shuffle & Greedy ==========" << endl;
  max_score = 0.0;
  for(int i = 0 ; i < 10 ; i++) {
    random_shuffle ( pat._colorComps.begin(), pat._colorComps.end() );
    pat.greedy(tmp,0);
    pat.measureArea(tmp);
    // cout << "#" << i << " score = " << pat.finalScore(tmp) << endl << endl;
    if(pat.finalScore(tmp) > max_score) max_score = pat.finalScore(tmp);
  }
  cout << "    score = " << max_score << endl << endl;

  cout << "    === Shuffle & Greedy & Statistics ==="<<endl;
  tmp = pat.statistics();
  pat.measureArea(tmp);
  // cout << "final score = " << pat.finalScore(tmp) << ", fixNum = " << pat.fixNum << endl;
  cout << "    score = " << pat.finalScore(tmp) << endl << endl;

  tmusg.getPeriodUsage(stat);
  
  cout << "final score = " << pat.finalScore(tmp) << ", fixNum = " << pat.fixNum << endl;
  
  pat.print(tmp, argv[2]);
  
  cout << "    runtime = " << (stat.uTime + stat.sTime) / 1000000.0 << " sec \n";
  cout << "    memory  = " << stat.vmPeak / 1000.0 << " MB \n";

  return 0;
}

void setting(Pattern &p)
{
  // defult setting
  p.RAND_TIME = 1000;
  // p.RANDOMBEST =  100;
  p.RAND_TIME_IN_FIXGENE = 100;
  // p.FINAL_ITER_NUM = 10000;
  p.BOUND_RATIO = 0.75;
  p.BOUND_FIX = 0.9;
  p.FIRST_AGE = 30;
  p.NUM_PER_AGE = 30;
  p.AMP_FACTOR = 10;
  p.PROB = 3;
  p.WEIGHTONDIFF = 10;

  ifstream fin( "./bin/setting.txt" );
  if( fin.fail() ){
    cout << "SETTING FAIL!\n";
    return;
  }

  stringstream ss("");
  string buf, name;
  char ch;
  double num;
  while(getline(fin, buf))
  {
    ss.str("");
    ss.clear();

    ss << buf;
    ss >> name >> ch >> num;

    if(name == "RAND_TIME")      p.RAND_TIME = num;
    // else if(name == "RANDOMBEST")     p.RANDOMBEST =  num;
    else if(name == "RAND_TIME_IN_FIXGENE") p.RAND_TIME_IN_FIXGENE = num;
    // else if(name == "FINAL_ITER_NUM") p.FINAL_ITER_NUM = num;
    else if(name == "BOUND_RATIO")    p.BOUND_RATIO = num;
    else if(name == "BOUND_FIX")      p.BOUND_FIX = num;
    else if(name == "FIRST_AGE")      p.FIRST_AGE = num;
    else if(name == "NUM_PER_AGE")    p.NUM_PER_AGE = num;
    else if(name == "AMP_FACTOR")     p.AMP_FACTOR = num;
    else if(name == "PROB")           p.PROB = num;
    else if(name == "WEIGHTONDIFF")   p.WEIGHTONDIFF = num;
  }
}

bool sortByDiffSum(Component *i, Component *j)
{
  return (i->_diffSum > j->_diffSum);
}
bool sortByWinSize(Component *i, Component *j)
{
  return (i->_winInComp.size() > j->_winInComp.size());
}
bool sortByWeight(Component *i, Component *j)
{
  return (i->_weight > j->_weight);
}
