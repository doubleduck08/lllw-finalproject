#include "pattern.h"
using namespace std;

double Pattern::getScore(const Example &exp)
{
  int compsize = exp.AreaA.size();
  int score = 0;
  for(int i=0; i < compsize; ++i){
    int sub = exp.AreaA[i] - exp.AreaB[i];
    score += sub > 0 ? sub : -sub;
  }

  return score / (_omega*_omega);
}
