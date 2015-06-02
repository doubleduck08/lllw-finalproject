#include<queue>

void be_uncolorable(Component* comp)
{
    vector <Node*> iterator it_N=comp->_nodes.begin();
    for ( ; it_N!=comp->_nodes.end() ; it_N++)
    {
        (*it_N)->color=0;
    }
}

void color_comp(vector <Components*> &_comp)
{
    Node* current,neibor;
    queue<Node*> q;
    vector <Components*> iterator it_C;
    vector <Edge*> iterator it_E;
    int color_pair=1; //if color_pair=n , it provides color(2n) & color(2n-1)
    for (it_C=_comp.begin() ; it_C!=_comp.end() ; it_C++)
    {
        (*it_C)->colorable=true;
        current=(*it_C)->_nodes[0];
        current->color=2*color_pair-1;
        current->traveled=true;
        q.push(current);
        while (!q.empty()) {
           current=q.front();
           q.pop();
           for (it_E=current->_edge.begin() ; 
                it_E!=current->_edge.end() ; it_E++)
           {
               neibor=(*it_E)->get_neibor(current);
               if (!neibor->traveled) {
                  neibor->color=4*color_pair-1-current->color;
                  neibor->traveled=true;
                  q.push(neibor);
               }
               else if (neibor->color==current->color) {
                  be_uncolorable(*it_C);
                  q.clear();
                  (*it_C)->colorable=false;
                  break;
               }
           }
       }
       color_pair++;
    }
}



