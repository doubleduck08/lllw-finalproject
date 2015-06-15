#include <iostream>
#include <cstdlib>
#include "pattern.h"
#include "gene_output.cpp"
using namespace std;

int main(int argc, char **argv)
{
  Pattern pat;
  Example exa;
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
  pat.genGene(exa);
  pat.gene_output(&exa);
  return 0;
}
