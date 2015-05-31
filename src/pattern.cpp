#include "pattern.h"
#include <time.h>
using namespace std;

Shape::Shape(int id, int x1, int x2, int y1, int y2)
{
  _id = id;
  _x1 = x1;
  _x2 = x2;
  _y1 = y1;
  _y2 = y2;
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
        Shape* tmp = new Shape(id, x1, x2, y1, y2);
        _shapes.push_back(tmp);
        break;
    }
    buf.clear();
  }
}

Node::Node(Shape* s)
{
  _id = s->_id;
  _shape = s;
  _color = -1;
  _traveled = false;
}

bool Pattern::nodeInitailize()
{
  _nodeSize = _shapes.size();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    Node* n = new Node(_shapes[i]);
    _nodes.push_back(n);

    _shapes[i]->_node = n;
    _shapesMap[_shapes[i]->_id] = _shapes[i];
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

bool findRangeX(vector<Shape *> &shapes, double lower, double upper, int &left, int &right)
{
  int l, m, r;
  lower -= 0.5;
  upper += 0.5;

  l = 0;
  r = shapes.size() - 1;
  while(l <= r)
  {
    m = (l + r) / 2;
    if(shapes[m]->_x1 > lower) r = m - 1;
    if(shapes[m]->_x1 < lower) l = m + 1;
  }
  left = r;

  l = 0;
  r = shapes.size() - 1;
  while(l <= r)
  {
    m = (l + r) / 2;
    if(shapes[m]->_x1 > upper) r = m - 1;
    if(shapes[m]->_x1 < upper) l = m + 1;
  }
  right = l;
}

bool findRangeY(vector<Shape *> &shapes, double lower, double upper, int &left, int &right)
{
  int l, m, r;
  lower -= 0.5;
  upper += 0.5;

  l = 0;
  r = shapes.size() - 1;
  while(l <= r)
  {
    m = (l + r) / 2;
    if(shapes[m]->_y1 > lower) r = m - 1;
    if(shapes[m]->_y1 < lower) l = m + 1;
  }
  left = r;

  l = 0;
  r = shapes.size() - 1;
  while(l <= r)
  {
    m = (l + r) / 2;
    if(shapes[m]->_y1 > upper) r = m - 1;
    if(shapes[m]->_y1 < upper) l = m + 1;
  }
  right = l;
}

bool Pattern::addEdge(Node* A, Node* B)
{
  Edge* edge = new Edge();
  edge->_node[0] = A;
  edge->_node[1] = B;
  A->_edge.push_back(edge);
  B->_edge.push_back(edge);
  _edges.push_back(edge);
}

bool Pattern::edgeInitailize()
{
  Shape* shapeA;
  int left, right;
  _edgeSize = 0;

  sortX1();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    shapeA = _shapesMap[i+1];  // A = _shapes[i]
    // check if A.x2 < B.x1 < A.x2 + alpha
    findRangeX(_shapes, shapeA->_x2, shapeA->_x2 + _alpha, left, right);
    for(int j = left + 1 ; j < right; j++)
    {
      bool inRange = false;
      // check if A.y1 < B.y1 or B.y2 < A.y2
      if(_shapes[j]->_y1 >= shapeA->_y1 && _shapes[j]->_y1 <= shapeA->_y2) inRange = true;
      if(_shapes[j]->_y2 >= shapeA->_y1 && _shapes[j]->_y2 <= shapeA->_y2) inRange = true;
      if(!inRange) continue;
      // set conection
      addEdge(_shapes[j]->_node, shapeA->_node);
      _edgeSize++;
    }
  }

  sortY1();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    shapeA = _shapesMap[i+1];  // A = _shapes[i]
    findRangeY(_shapes, shapeA->_y2, (shapeA->_y2 + _beta), left, right);
    for(int j = left + 1 ; j < right; j++)
    {
      bool inRange = false;
      if(_shapes[j]->_x1 >= shapeA->_x1 && _shapes[j]->_x1 <= shapeA->_x2) inRange = true;
      if(_shapes[j]->_x2 >= shapeA->_x1 && _shapes[j]->_x2 <= shapeA->_x2) inRange = true;
      if(!inRange) continue;
      addEdge(_shapes[j]->_node, shapeA->_node);
      _edgeSize++;
    }
  }

  return true;
}

Node* Edge::getNeighbor(Node *n)
{
  if ( _node[0] == n ) return _node[1];
  if ( _node[1] == n ) return _node[0];

  return 0;
}

void Pattern::findcomponent()
{
  clear_traveled();
  _compSize = 0;

  int n_num=_nodes.size();
  int e_num=_edges.size();

  for(int i=0; i<n_num; ++i){
    if(_nodes[i]->_traveled == 0){
      Component *comp = new Component;
      _compSize++;
      comp->_id = _compSize;
      dfs_visit(_nodes[i],comp);
      _comps.push_back(comp);
    }
  }
}

void Pattern::dfs_visit(Node* u,Component* comp)
{
  u->_traveled = true;
  comp->_nodes.push_back(u);
  for(int i=0; i<u->_edge.size(); ++i){
    if(u->_edge[i]->getNeighbor(u)->_traveled == false)
      dfs_visit(u->_edge[i]->getNeighbor(u), comp);
  }
}

void be_uncolorable(Component* comp)
{
  vector<Node*>::iterator it_N = comp->_nodes.begin();
  for ( ; it_N!=comp->_nodes.end() ; it_N++)
  {
    (*it_N)->_color=-1;
  }
}

void Pattern::color_comps()
{
  clear_traveled();

  Node *current, *neibor; //Node* a,b means one ptr, one var!!!!!!
  queue<Node*> q;
  vector<Component*>::iterator it_C;
  vector<Edge*>::iterator it_E;
  // int color_pair = 1; //if color_pair=n , it provides color(2n) & color(2n-1)
  for (it_C=_comps.begin() ; it_C!=_comps.end() ; it_C++)
  {
    (*it_C)->_colorable = true;
    current=(*it_C)->_nodes[0];
    // current->_color = 2*color_pair-1;
    current->_color = 0;
    current->_traveled = true;
    q.push(current);
    while (!q.empty()) {
      current = q.front();
      q.pop();
      for (it_E=current->_edge.begin() ;
          it_E!=current->_edge.end() ; it_E++)
      {
        neibor = (*it_E)->getNeighbor(current);
        if ( !(neibor->_traveled) ){
          // neibor->_color = (4*color_pair-1) - current->_color;
          neibor->_color = 1 - current->_color;
          neibor->_traveled=true;
          q.push(neibor);
        }
        else if (neibor->_color == current->_color) {
          be_uncolorable(*it_C);
          {queue<Node*> tmp; swap(q, tmp);}
          //q.clean();
          (*it_C)->_colorable=false;
          break;
        }
      }
    }
    // color_pair++;
  }
}

void Pattern::clear_traveled()
{
  for(int i=0; i<_nodeSize; ++i)
    _nodes[i]->_traveled = false;
}

bool Pattern::setBox()
{
  return true;
}

bool Pattern::setWindows()
{
  //
  return true;
}

bool setGeneBase()
{
  return true;
}

bool Example::measureArea()
{
  return true;
}

void mutation( string& a, string& b, string& c, string& d ){
  mut_function(a);
  mut_function(b);
  mut_funvtion(c);
  mut_function(d);
}

void mut_function( string& gene ){
  int mut_num = srand(0)%10;
  int mut_pos;

  for( int i = 0; i < mut_num; i++){
    mut_pos = srand(0)%(gene.length());
    gene[mut_pos] = srand(0)%1;
  }
}
  
