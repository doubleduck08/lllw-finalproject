# include "pattern.h"
using namespace std;
#define MUT_NUM 3

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
    if(buf.size() < 3)
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
      case '\r':
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
  _colorCompsSize = 0;
  for(int i=0; i < _compSize; ++i){
    if(_comps[i]->_colorable){
      ++_colorCompsSize;
      _comps[i]->_geneId = _colorCompsSize;
      _colorComps.push_back(_comps[i]);
    }
  }
}

void Pattern::clear_traveled()
{
  for(int i=0; i<_nodeSize; ++i)
    _nodes[i]->_traveled = false;
}

bool Pattern::setBox()
{
  Component *comp;
  Node *node;
  bool firstNode = true;
  int nodeSizeInComp;
  for(int i = 0 ; i < _compSize ; i++)
  {
    comp = _comps[i];
    if(comp->_colorable == false) continue;

    nodeSizeInComp = comp->_nodes.size();
    for(int j = 0 ; j < nodeSizeInComp ; j++)
    {
      node = comp->_nodes[j];
      if(firstNode)
      {
        _boxX1 = node->_shape->_x1;
        _boxX2 = node->_shape->_x2;
        _boxY1 = node->_shape->_y1;
        _boxY2 = node->_shape->_y2;
        firstNode = false;
      }
      else
      {
        if(_boxX1 > node->_shape->_x1) _boxX1 = node->_shape->_x1;
        if(_boxX2 < node->_shape->_x2) _boxX2 = node->_shape->_x2;
        if(_boxY1 > node->_shape->_y1) _boxY1 = node->_shape->_y1;
        if(_boxY2 < node->_shape->_y2) _boxY2 = node->_shape->_y2;
      }
    }
  }
  return true;
}

Window::Window(int id, int x1, int x2, int y1, int y2)
{
  _id = id;
  _x1 = x1;
  _x2 = x2;
  _y1 = y1;
  _y2 = y2;
}


bool Pattern::setWindows()
{
  int x_count = 0, y_count = 0;
  if( (_boxX2 - _boxX1)%_omega != 0 ) x_count += 1;
  if( (_boxY2 - _boxY1)%_omega != 0 ) y_count += 1;
  x_count += (_boxX2 - _boxX1) / _omega;
  y_count += (_boxY2 - _boxY1) / _omega;

  int x1, y1;
  _windowSize = 0;
  Window* win;
  for(int j = 0 ; j < y_count ; j++)
  {
    if(j == y_count-1)
      y1 = _boxY2 - _omega;
    else
      y1 = _boxY1 + _omega * j;

    for(int i = 0 ; i < x_count ; i++)
    {
      if(i == x_count-1)
        x1 = _boxX2 - _omega;
      else
        x1 = _boxX1 + _omega * i;

      _windowSize++;
      win = new Window(_windowSize, x1, x1+_omega, y1, y1+_omega);
      _windows.push_back(win);
    }
  }
  return true;
}

bool Pattern::setGeneBase()
{
  Component* comp;
  Shape* shape;
  Window* win;
  int n, color, win_x_pos, win_y_pos, win_id;

  int x_count = 0, y_count = 0;
  if( (_boxX2 - _boxX1)%_omega != 0 ) x_count += 1;
  if( (_boxY2 - _boxY1)%_omega != 0 ) y_count += 1;
  x_count += (_boxX2 - _boxX1) / _omega;
  y_count += (_boxY2 - _boxY1) / _omega;

  for(int ii = 0 ; ii < _compSize ; ii++)
  {
    comp = _comps[ii];
    if(comp->_colorable == false) continue;

    n = comp->_nodes.size();
    for(int jj = 0 ; jj < n ; jj++)
    {
      shape = comp->_nodes[jj]->_shape;
      color = comp->_nodes[jj]->_color;
      win_x_pos = (shape->_x1 - _boxX1) / _omega;
      win_y_pos = (shape->_y1 - _boxY1) / _omega;
      win_id    = win_y_pos * x_count + win_x_pos + 1;

      int i = 0, j = 0, x, y;
      while(i < y_count - win_y_pos)
      {
        j = 0;
        while(j < x_count - win_x_pos)
        {
          win = _windows[ win_id + i * x_count + j -1 ];

          if( shape->_x2 <= win->_x2 && shape->_x1 >= win->_x1 ) x = shape->_x2 - shape->_x1;
          else if( shape->_x1 < win->_x2 && shape->_x2 > win->_x2 ) x = win->_x2 - shape->_x1;
          else if( shape->_x2 > win->_x1 && shape->_x1 < win->_x1 ) x = shape->_x2 - win->_x1;
          else if( shape->_x1 < win->_x1 && shape->_x2 > win->_x2) x = _omega;
          else x = 0;

          if( shape->_y2 <= win->_y2 && shape->_y1 >= win->_y1 ) y = shape->_y2 - shape->_y1;
          else if( shape->_y1 < win->_y2 && shape->_y2 > win->_y2 ) y = win->_y2 - shape->_y1;
          else if( shape->_y2 > win->_y1 && shape->_y1 < win->_y1 ) y = shape->_y2 - win->_y1;
          else if( shape->_y1 < win->_y1 && shape->_y2 > win->_y2) y = _omega;
          else y = 0;

          if( x * y > 0 )
          {
            WindowInComp* wic = new WindowInComp;
            wic->_window = win;
            wic->_areaA  = x * y * ( 1 - color );
            wic->_areaB  = x * y * color;
            comp->_winInComp.push_back(wic);

            CompInWindows* ciw = new CompInWindows;
            ciw->_comp  = comp;
            ciw->_areaA = x * y * ( 1 - color );
            ciw->_areaB = x * y * color;
            win->_compInWin.push_back(ciw);
          }

          if(x == 0) break;
          else j++;
        }
        if(y == 0) break;
        else i++;
      }
    }
  }
  return true;
}

bool Pattern::measureArea(Example &exp)
{
  Window* win;
  Component* comp;
  int n, areaA, areaB;

  for(int i=0; i < _windowSize; ++i){
    win = _windows[i];
    n = win->_compInWin.size();
    areaA = areaB = 0;

    for(int j=0; j < n ; ++j){
      comp = win->_compInWin[j]->_comp;
      if(exp._colorGene[comp->_geneId - 1]){
        areaA += win->_compInWin[j]->_areaB;
        areaB += win->_compInWin[j]->_areaA;
      }
      else{
        areaA += win->_compInWin[j]->_areaA;
        areaB += win->_compInWin[j]->_areaB;
      }
    }
    exp._areaA.push_back(areaA);
    exp._areaB.push_back(areaB);
  }
  return true;
}

void Pattern::genGene(Example& exp)
{
  srand(time(0));
  for (int j=0 ; j < _colorCompsSize; j++)
    exp._colorGene.push_back(rand()%2);
}

void Pattern::mut_function(Example& exp)
{
  srand(time(0));
  int mut_num = rand() % MUT_NUM;
  int mut_pos;

  for( int i = 0; i < mut_num; i++){
    mut_pos = rand() % (_colorCompsSize);
    exp._colorGene[mut_pos] = (exp._colorGene[mut_pos]+1) % 2; //XOR
  }
}

void Pattern::mutation(Example *exp)
{
  int len = sizeof(exp) / sizeof(*exp);
  for( int i = 0; i < len; ++i ){
    mut_function(exp[i]);
  }
}

int Pattern::drawExample(Example* candidate, const double *ratio)
{
  srand(time(0));
  int CandNum = sizeof(candidate) / sizeof(*candidate);
  double randNum = rand() / RAND_MAX;
  int select=0;
  for(; select < CandNum; ++select){
    if(randNum < ratio[select])
      break;
  }
  return select;
}

void Pattern::compulate(Example &ori1, Example &ori2)
{
  int compuRatio = _colorCompsSize / 10 + 1;

  bool tmp[_colorCompsSize];
  memset(tmp, 0, sizeof(bool) * _colorCompsSize);

  for(int i=0; i < compuRatio; ++i){
    tmp[i] = ori1._colorGene[i];
    ori1._colorGene[i] = ori2._colorGene[i];
    ori2._colorGene[i] = tmp[i];
  }
}

double Pattern::getScore(const Example &exp)
{
  int expCompSize = exp._areaA.size();
  int score = 0;
  for(int i=0; i < expCompSize; ++i){
    int sub = exp._areaA[i] - exp._areaB[i];
    score += sub > 0 ? sub : -sub;
  }

  return score / (_omega*_omega);
}

Example* Pattern::findbest(Example* candidate)
{
  //Example candidate[CandNum];
  int CandNum = 8;//sizeof(candidate) / sizeof(*candidate);
  Example* seleteExp = new Example [CandNum/2];
  double score[CandNum];
  double sum = 0;
  double ratio[CandNum];
  memset(ratio, 0, sizeof(double) * CandNum);

  //
  for(int i=0; i < CandNum; ++i){
    measureArea(candidate[i]);
  }

    for(int i=0; i < CandNum; ++i){
      score[i] = getScore(candidate[i]);
      sum += (1 / score[i]);
    }

  for(int i=0; i < CandNum; ++i){
    ratio[i] = (score[i] / sum);
    if(i > 0)
      ratio[i] += ratio[i-1];
  }

  for(int i=0; i < CandNum; ++i){
    seleteExp[i] = candidate[drawExample(candidate, ratio)];
  }

  //compulate
  for(int i=0; i < CandNum / 2; i+=2){
    compulate(seleteExp[i], seleteExp[i+1]);
  }

  //mutation
  mutation(seleteExp);

  return seleteExp;
}


// measure final score
double finalScore(Example &ex)
{
  int x_count = 0, y_count = 0;
  if( (_boxX2 - _boxX1)%_omega != 0 ) x_count += 1;
  if( (_boxY2 - _boxY1)%_omega != 0 ) y_count += 1;
  x_count += (_boxX2 - _boxX1) / _omega;
  y_count += (_boxY2 - _boxY1) / _omega;

  int win_count = x_count * y_count;
  int expCompSize = ex._areaA.size();
  double score = 0;
  for(int i=0; i < expCompSize; ++i){
    int sub = ex._areaA[i] - ex._areaB[i];
    score += sub > 0 ? sub : -sub;
  }

  score = 100 * score / (_omega*_omega);
  score = 100 - score / 5.0;
  return score;
}