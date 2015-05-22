# include <vector>
# include "pattern.h"
using namespace std;


Node::Node(Shape* s)
{
  _shape = s;
  _color = 0
  _traveled = false;
}

bool Pattern::nodeInitailize()
{
  _nodeSize = _shapes.size();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    Node* n = new Node(_shapes + i);
    _nodes.push_back(n);

    _shapes[i]._node = n;
    _shapes[i]._x2WithAlpha = _shapes[i]._x2 + _alpha;
    _shapes[i]._y2WithBeta  = _shapes[i]._y2 + _beta;
  }
  return true;
}

bool x1Comp( const Shape* A, const Shape* B ){ return (*A)._x1 < (*B)._x1; }
bool Pattern::sortX1()
{
    sort(_shapes.begin(), _shapes.end(), x1Comp);
    return true;
}

bool y1Comp( const Shape* A, const Shape* B ){ return (*A)._y1 < (*B)._y1; }
bool Pattern::sortY1()
{
    sort(_shapes.begin(), _shapes.end(), y1Comp);
    return true;
}



bool Pattern::edgeInitailize()
{
  _edgeSize = 0;

  sortX1();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    // A = _shapes[i]
    // check A.x2 < B.x1 < A.x2 + alpha
    // check A.y1 < B.y1 or B.y2 < A.y2
    // set conection
  }

  sortY1();

  return true;
}

