# ifndef LAYOUT_H
# define LAYOUT_H

# include <queue>
# include <algorithm>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <cstring>
using namespace std;

class Shape;
class Group;
class Window;
class Box;
class Layout
{
public:
  Layout();
  ~Layout();

  int _alpha;
  int _beta;
  int _omega;
  Box _box;

  int _shapeNum;
  vector<Shape *> _shapes;
  int _groupNum;
  vector<Group *> _groups;
  int _windowNum;
  vector<Window *> _windows;
};

class Shape
{
public:
  Shape(int, int, int, int, int);
  ~Shape(){};

  int _id;
  int _color;
  int _x1, _x2, _y1, _y2;
};

class Group
{
public:
  Group();
  ~Group();

  vector<Shape *> _shapes;
};

class Window
{
public:
  Window(int, int, int, int, int);
  ~Window(){};

  int _id;
  int _x1, _x2, _y1, _y2;
};

class Box
{
public:
  Box();
  ~Box();

  int _x1, _x2, _y1, _y2;
  int _winCountX, _winCountY;
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
