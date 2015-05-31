# ifndef PATTERN_H
# define PATTERN_H
# include <queue>
# include <algorithm>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
#include <cstring>
using namespace std;

class Node;
class Edge;
class Shape
{
public:
  Shape(int, int, int, int, int);
  ~Shape(){};

  int _id;
  int _x1, _x2, _y1, _y2;

  Node* _node;
};

class Node
{
public:
  Node(){};
  Node(Shape*);
  ~Node(){};
  vector<Edge *> _edge;

  Shape* _shape;

  int _id; // the same with Shape
  int _color;
  bool _traveled;
};

class Edge
{
public:
  Edge(){};
  ~Edge(){};
  Node* getNeighbor(Node *n);

  Node* _node[2];
};

class Window;
struct WindowInComp
{
  Window *_window;
  int _areaA;
  int _areaB;
};

class Component
{
public:
  Component(){};
  ~Component(){};

  int _id;
  int _geneId;
  bool _colorable;
  vector<Node *> _nodes;
  // bool _switchColor; // used by final solution
  // int _windowSize;
  vector<WindowInComp *> _winInComp;
};

struct CompInWindows
{
  Component*_comp;
  int _areaA;
  int _areaB;
};

class Window
{
public:
  Window(int, int, int, int, int);
  ~Window(){};

  int _id;
  int _x1;
  int _x2;
  int _y1;
  int _y2;
  // int _totalAreaA; // "total of (Switch ? Area A : Area B)"
  // int _totalAreaB; // used by final solution
  // int _compSize;
  vector<CompInWindows *> _compInWin;
};

class Example
{
public:
  Example(){};
  ~Example(){};

  // gene
  vector<bool> _colorGene;
  // character
  vector<int> _areaA;
  vector<int> _areaB;
};

class Pattern
{
public:
  Pattern();
  ~Pattern(){};
  bool readfile(char*);
  bool nodeInitailize();
  bool sortX1();
  bool sortY1();
  bool edgeInitailize();
  bool addEdge(Node *, Node *);

  void findcomponent();
  void dfs_visit(Node*, Component*);
  void color_comps();
  void clear_traveled();

  bool setBox();
  bool setWindows();
  bool setGeneBase();

  int _alpha;
  int _beta;
  int _omega;
  map<int, Shape *> _shapesMap;
  vector<Shape *> _shapes;
  
  int _nodeSize;
  int _edgeSize;
  int _compSize;
  int _colorCompsSize;
  vector<Node *> _nodes; // all
  vector<Edge *> _edges; // all
  vector<Component *> _comps;
  vector<Component *> _colorComps;
  
  int _boxX1;
  int _boxX2;
  int _boxY1;
  int _boxY2;
  int _windowSize;
  vector<Window*> _windows;

  vector<Example*> _examples;
  
  //findbest
  void genGene(Example &);
  double getScore(const Example &);
  void mut_function(Example &);
  void mutation(Example *);
  void compulate(Example &, Example &);
  int drawExample(Example *, const double *);
  Example* findbest(Example*);
  bool measureArea(Example &);



};

# endif
