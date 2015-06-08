#include<iostream>
#include<fstream>
#include"pattern.h"
using namespace std;

void Pattern::gene_output(Eample* exa) 
{
   fstream fout("output.txt",ios::out);
   vector<bool>::iterator it_B;
   vector<Node*>::iterator it_N;
   for (it_B=exa->_colorGene.begin() ; it_B!=exa->_colorGene.end() ; it_B++)
   {
      int pos=it_B-exa->_colorGene.begin();
      int total_area_A=0;
      int total_area_B=0;
      
      int total_area_WA=0;
      int total_area_WB=0;

      fout<<"colorcomp["<<_colorComps[pos]->id<<"] :\n"
      fout<<"  compute_area(node):"
      for (it_N=_colorComps[pos]->_nodes.begin() ; 
           it_N!=_colorComps[pos]->_nodes.end() ; it_N++) {
          fout<<"    node["<<(*it_N)->id<<"] :\n"
          int area=((*it_N)->_shape->x2-(*it_N)->_shape->x1)*
                   ((*it_N)->_shape->y2-(*it_N)->_shape->y1);
          if (*it_B) {
             if ((*it_N)->color) {
             fout<<"      color : A\n"
                 <<"      area  : "<<area<<endl; 
             total_area_A+=area;
             }
             else
             fout<<"      color : B\n"
                   "      color : "<<area<<endl;
             total_area_B+=area;
          }
          else {
             if ((*it_N)->color)
             fout<<"      color : B\n"
                 <<"      area  : "<<area<<endl; 
             total_area_B+=area;
             else
             fout<<"      color : A\n"
                 <<"      area  : "<<area<<endl; 
             total_area_A+=area;
          }
      }
      fout<<"  total_area_A : "<<toral_area_A<<endl;
      fout<<"  total_area_B : "<<toral_area_B<<endl;
      fout<<"  compute_area(window):"
      for (int i=0 ; i<_winInComp.size() ; i++) { 
          fout<<"    window["<<_winInComp[i]->_window->id<<"] :\n"
          int area=((*it_N)->_shape->x2-(*it_N)->_shape->x1)*
                   ((*it_N)->_shape->y2-(*it_N)->_shape->y1);
          if (*it_B) {
             if ((*it_N)->color) {
             fout<<"      color : A\n"
                 <<"      area  : "<<area<<endl; 
             total_area_A+=area;
             }
             else
             fout<<"      color : B\n"
                   "      color : "<<area<<endl;
             total_area_B+=area;
          }
          else {
             if ((*it_N)->color)
             fout<<"      color : B\n"
                 <<"      area  : "<<area<<endl; 
             total_area_B+=area;
             else
             fout<<"      color : A\n"
                 <<"      area  : "<<area<<endl; 
             total_area_A+=area;
          }
      }
      fout<<"  total_area_A : "<<toral_area_A<<endl;
      fout<<"  total_area_B : "<<toral_area_B<<endl;
   } 
}

