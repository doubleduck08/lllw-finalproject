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
};

class Node
{
public:
  Node();
  ~Node();
  vector<Edge *> _edge;

  /* data */
private:
  int _color;
  bool _traveled;
  
};

class Edge
{
public:
  Edge();
  ~Edge();
  Node *getNeighbor(Node *n);

  /* data */
private:
  Node* _node[2];
};

class Component
{
public:
  Component();
  ~Component();
  vector<Node *> _nodes;
  vector<Edge *> _edges;

private:
  /* data */
  
};

class pattern
{
public:
  pattern();
  ~pattern();
  void findcomponent();
  vector<Shape *> _shapes;
  vector<Component *> _comps;
  vector<Node *> _nodes; // all
  vector<Edge *> _edges; // all
  /* data */
private:
  int _alpha;
  int _beta;
  int _omega;
  

};

# endif