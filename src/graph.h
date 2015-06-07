# ifndef GRAPH_H
# define GRAPH_H

# include <queue>
# include <algorithm>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <cstring>
using namespace std;

class Node;
class Edge;
class Component;
class Graph
{
public:
  Graph();
  ~Graph();

  /* data */
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

class Component
{
public:
  Component(){};
  ~Component(){};

  int _id;
  int _geneId;
  bool _colorable;
  vector<Node *> _nodes;
};

# endif