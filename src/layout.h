# ifndef LAYOUT_H
# define LAYOUT_H

# include <queue>
# include <algorithm>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <cstring>
# include "graph.h"
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

  bool sortX1();
  bool sortY1();

  int _alpha;
  int _beta;
  int _omega;
  Box _box;

  int _shapeNum;
  vector<Shape *> _shapes;
  map<int, Shape *> _shapesMap;
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

  Node* _node;
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

# endif
