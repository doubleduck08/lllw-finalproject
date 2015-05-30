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

  pat.setBox();
  pat.setWindows();
  // for(int i = 0 ; i < pat._compSize ; i++)
  //   cout << "#" << i+1 <<" "<<pat._comps[i]->_colorable << endl;

  return 0;
}
