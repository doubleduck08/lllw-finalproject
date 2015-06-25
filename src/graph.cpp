# include "graph.h"
using namespace std;

Node::Node(Shape* s)
{
  _id = s->_id;
  _shape = s;
  _color = -1;
  _traveled = false;
}
bool Graph::setNode(Layout &layout)
{
  _nodeSize = layout._shapes.size();
  for(int i = 0 ; i < _nodeSize ; i++)
  {
    Node* node = new Node(layout._shapes[i]);
    _nodes.push_back(node);

    layout._shapes[i]->_node = node;
  }
  return true;
}