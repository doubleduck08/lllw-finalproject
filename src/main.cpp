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
  /*for(int i = 0; i<pat._nodeSize; i++){
    cout<<"#"<<i<<" "<<pat._shapesMap[i+1]->_id<<endl;
  }
  for(int i = 0; i<pat._edges.size(); ++i){
    cout<<"#"<<i<<" "<<pat._edges[i]->_node[0]->_shape->_id
                <<" "<<pat._edges[i]->_node[1]->_shape->_id<<endl;
  }*/
  return 0;
}
