# include "pattern.h"
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;

Shape::Shape(int, int, int, int, int)
{
  _x1 = 0;
  _x2 = 0;
  _y1 = 0;
  _y2 = 0;
}


Pattern::Pattern()
{
  _alpha = 0;
  _beta = 0;
  _omega = 0;
}

bool Pattern::readfile( char *filename )
{
  ifstream fin( filename );
  if( fin.fail() )
    return false;

  stringstream ss("");
  string buf;
  char ch;
  int id=0;
  int x1, x2, y1, y2;
  while( getline(fin, buf) ){
    if(buf.size()==0)
      continue;
    ss.str("");
    ss.clear();
    ss << buf;
    switch(buf[0]){
      case 'A':
        for(int i=0; i<6; ++i)
          ss >> ch;
        ss >> _alpha;
        break;
      case 'B':
        for(int i=0; i<5; ++i)
          ss >> ch;
        ss >> _beta;
        break;
      case 'O':
        for(int i=0; i<6; ++i)
          ss >> ch;
        ss >> _omega;
        break;
      default:
        ss >> x1 >> ch >> y1 >> ch >> x2 >> ch >> y2;
        ++id;
        Shape tmp(id, x1, x2, y1, y2);
        _shapes.push_back(tmp);
        break;
    }
    buf.clear();
  }

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
    _shapesMap[i] = (_shapes + i);
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

bool findRangeX(vector<Shape *> &shapes,int &lower, int &upper, int &left, int &right)
{
  int a, b, c;
  a = 0;
  b = shapes.size() - 1;
  while(a <= b)
  {
    c = (a + b) / 2
    if(a == c){ left = c + 1; break; }
    if(shapes[c]->x1 >= lower) b = c - 1;
    else a = c;
  }
  a = 0;
  b = shapes.size() - 1;
  while(a <= b)
  {
    c = (a + b + 1) / 2
    if(b == c){ right = c - 1; break; }
    if(shapes[c]->x1 <= upper) a = c + 1;
    else b = c;
  }
}

bool findRangeY(vector<Shape *> &shapes,int &lower, int &upper, int &left, int &right)
{
  int a, b, c;
  a = 0;
  b = shapes.size() - 1;
  while(a <= b)
  {
    c = (a + b) / 2
    if(a == c){ left = c + 1; break; }
    if(shapes[c]->y1 >= lower) b = c - 1;
    else a = c;
  }
  a = 0;
  b = shapes.size() - 1;
  while(a <= b)
  {
    c = (a + b + 1) / 2
    if(b == c){ right = c - 1; break; }
    if(shapes[c]->y1 <= upper) a = c + 1;
    else b = c;
  }
}

bool addEdge(Node* A, Node* B)
{
  Edge* edge = new Edge();
  edge->_node[0] = A;
  edge->_node[1] = B;
  A->_edge.push_back(edge);
  B->_edge.push_back(edge);
}

bool Pattern::edgeInitailize()
{
  Shape* shapeA;
  int left, right;
  _edgeSize = 0;

  sortX1();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    shapeA = _shapesMap[i];  // A = _shapes[i]
    // check if A.x2 < B.x1 < A.x2 + alpha
    findRangeX(_shapes, shapeA->x2, shapeA->x2 + alpha, left, right);
    for(int j = left + 1 ; j < right; j++)
    {
      // check if A.y1 < B.y1 or B.y2 < A.y2
      if(_shapes[j]->y1 < shapeA->y1 || _shapes[j]->y1 > shapeA->y2) continue;
      if(_shapes[j]->y2 < shapeA->y1 || _shapes[j]->y2 > shapeA->y2) continue;
      // set conection
      addEdge(_shapes[j]->_node, shapeA->_node);
    }
  }

  sortY1();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    shapeA = _shapesMap[i];  // A = _shapes[i]
    findRangeY(_shapes, shapeA->y2, shapeA->y2 + alpha, left, right);
    for(int j = left + 1 ; j < right; j++)
    {
      if(_shapes[j]->x1 < shapeA->x1 || _shapes[j]->x1 > shapeA->x2) continue;
      if(_shapes[j]->x2 < shapeA->x1 || _shapes[j]->x2 > shapeA->x2) continue;
      addEdge(_shapes[j]->_node, shapeA->_node);
    }
  }

  return true;
}

