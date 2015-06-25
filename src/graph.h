# ifndef GRAPH_H
# define GRAPH_H

# include <queue>
# include <algorithm>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <cstring>
# include "layout.h"
using namespace std;

class Node;
class Edge;
class Component;
class Graph
{
public:
  Graph(){};
  ~Graph(){};

  bool setNode(Layout &);
  bool setEdge();
  bool addEdge(Node *, Node *);

  int _nodeSize;
  vector<Node *> _nodes; // all
  int _edgeSize;
  vector<Edge *> _edges; // all
  int _compSize;
  vector<Component *> _comps;
};

class Node
{
public:
  Node(){};
  Node(Shape*);
  ~Node(){};

  int _id; // the same with Shape
  int _color;
  bool _traveled;
  vector<Edge *> _edge;

  Shape* _shape;
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