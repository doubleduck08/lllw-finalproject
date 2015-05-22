# ifndef PATTERN_H
# define PATTERN_H

# include <vector>
using namespace std;

class Edge;

class Shape
{
public:
  Shape(int, int, int, int, int);
  Shape();
  ~Shape(){};

private:
  int _id;
  int _x1, _x2, _y1, _y2;
};

class Node
{
public:
  Node();
  ~Node();

  /* data */
private:
  int _color;
  bool _traveled;
  vector<Edge *> _edge;
};

class Edge
{
public:
  Edge();
  ~Edge();

  /* data */
private:
  Node* _node[2];
};

class Component
{ 
public:
  Component();
  ~Component(){};

private:
  /* data */
  vector<Node *> _nodes;
  vector<Edge *> _edges;
};

class Pattern
{
public:
  Pattern();
  ~Pattern(){};
  bool readfile(char*);

  /* data */
private:
  int _alpha;
  int _beta;
  int _omega;
  vector<Shape> _shapes;
  vector<Component *> _comps;
  vector<Node *> _nodes; // all
  vector<Edge *> _edges; // all
};

# endif
