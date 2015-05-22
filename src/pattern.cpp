#include "pattern.h"
#include <iostream>
using namespace std;

Node * Edge::getNeighbor(Node *n)
{
	if ( node[0] == n ) return node[1];
	if ( node[1] == n ) return node[0];

	return 0;	
}

void pattern::findcomponent(){
	int node_num = _nodes.size();
    int edge_number = _edges.size();
    for( int i=0; i<node_num; i++)
        _nodes[i]->color = 0;

    for( int i=0; i < node_num; i++)
    	if( _nodes[i]->color ==0){

    		Component* my_comp;
        	(my_comp->_nodes).push_back(_patt ->_nodes[i])
    		_node[i]->color = 1;
    		queue< Node* > my_queue;
    		my_queue.push(_node[i])

    		while( !my_queue.empty()){
    			Node* popNode = my_queue.front();
        		my_queue.pop();
        		
        		for( int i = 0 ; i < (popNode->_edge ).size() ; i++){

            		Edge* tmpEdge = popNode->_edge[i];
            		(my_comp->_edges).push_back(tmpEdge);
            		Node* neighborNode = tmpEdge->getNeighbor(popNode);

            		if( neighborNode->color == 0){
            			(my_comp->_nodes).push_back(neighborNode);
                		neighborNode->color = 1;
                		my_queue.push(neighborNode);
            		}
        		} 

        	popNode->color = 2;
    		}

    _comps.push_back(my_comp);
    cout << "There are " << _comps.size() << "components\n";
    }   	
}