# ifndef PATTERN_H
# define PATTERN_H

# include <vector>
using namespace std;

class Shape
{
public:
  Shape();
  ~Shape();

private:
  int _id;
  int _x1, _x2, _y1, _y2;

  Node* _node;
  int _x2WithAlpha;
  int _y2WithBeta;
};

class Node
{
public:
  Node(Shape*);
  ~Node();

private:
  Shape* _shape;

  int _color;
  bool _traveled;
  vector<Edge *> _edge;
};

class Edge
{
public:
  Edge();
  ~Edge();

private:
  Node* _node[2];
};

class Component
{
public:
  Component();
  ~Component();

private:
  vector<Node *> _nodes;
  vector<Edge *> _edges;
};

class Pattern
{
public:
  Pattern();
  ~Pattern();
  bool nodeInitailize();
  bool sortX1();
  bool sortY1();
  bool edgeInitailize();

private:
  int _alpha;
  int _beta;
  int _omega;
  vector<Shape *> _shapes;

  int _nodeSize;
  int _edgeSize;
  vector<Node *> _nodes; // all
  vector<Edge *> _edges; // all
  vector<Component *> _comps;
};

# endif