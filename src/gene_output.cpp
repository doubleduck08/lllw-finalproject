//#include<iostream>
//#include<fstream>
#include"pattern.h"
using namespace std;

void Pattern::genGene(Example& exp)
{ 
   for (int j=0 ; j < _colorCompsSize; j++){
      int tmp = rand();
      exp._colorGene.push_back(tmp%2);
   }
}

void Pattern::gene_output(Example* exa) 
{
   fstream fout("output1.txt",ios::out);
   vector<bool>::iterator it_B;
   vector<Node*>::iterator it_N;
   for (it_B=exa->_colorGene.begin() ; it_B!=exa->_colorGene.end() ; it_B++)
   {
      int pos=it_B-exa->_colorGene.begin();
      int total_area_A=0;
      int total_area_B=0;
      
      int total_area_WA=0;
      int total_area_WB=0;

      fout<<"colorcomp["<<_colorComps[pos]->_id<<"] :\n";
      fout<<"  compute_area(node):\n";
      for (it_N=_colorComps[pos]->_nodes.begin() ; 
           it_N!=_colorComps[pos]->_nodes.end() ; it_N++) {
          fout<<"    node["<<(*it_N)->_id<<"] :\n";
          fout<<"("<<(*it_N)->_shape->_x1<<","<<(*it_N)->_shape->_y1<<") "
              <<"("<<(*it_N)->_shape->_x2<<","<<(*it_N)->_shape->_y2<<") \n";
          int area=((*it_N)->_shape->_x2-(*it_N)->_shape->_x1)*
                   ((*it_N)->_shape->_y2-(*it_N)->_shape->_y1);
          if (*it_B) {
             if ((*it_N)->_color) {
             //fout<<"      color : A\n"
               //  <<"      area  : "<<area<<endl; 
             total_area_A+=area;
             }
             else{
            // fout<<"      color : B\n"
              //     "      color : "<<area<<endl;
             total_area_B+=area;}
          }
          else {
             if ((*it_N)->_color){
            // fout<<"      color : B\n"
              //   <<"      area  : "<<area<<endl; 
             total_area_B+=area;}
             else{
           //  fout<<"      color : A\n"
             //    <<"      area  : "<<area<<endl; 
             total_area_A+=area;}
          }
      }
      fout<<"  total_area_A : "<<total_area_A<<endl;
      fout<<"  total_area_B : "<<total_area_B<<endl;
      fout<<"  compute_area(window):\n";
      cout<<_colorComps[pos]->_windowSize<<endl;
      for (int i=0 ; i<_colorComps[pos]->_winInComp.size() ; i++) { 
          if (!(*it_B)) {
          /*fout<<"    window["
              <<_colorComps[pos]->_winInComp[i]->_window->_id<<"] :\n";
          fout<<"      color A : "
              <<_colorComps[pos]->_winInComp[i]->_AreaA<<endl;
          fout<<"      color B : "
              <<_colorComps[pos]->_winInComp[i]->_AreaB<<endl;*/
          total_area_WA+=_colorComps[pos]->_winInComp[i]->_AreaA;    
          total_area_WB+=_colorComps[pos]->_winInComp[i]->_AreaB;  
          }  
          else {
          /*fout<<"    window["
              <<_colorComps[pos]->_winInComp[i]->_window->_id<<"] :\n";
          fout<<"      color A : "
              <<_colorComps[pos]->_winInComp[i]->_AreaB<<endl;
          fout<<"      color B : "
              <<_colorComps[pos]->_winInComp[i]->_AreaA<<endl;*/
          total_area_WA+=_colorComps[pos]->_winInComp[i]->_AreaB;    
          total_area_WB+=_colorComps[pos]->_winInComp[i]->_AreaA;  
          }  
      }
      fout<<"  total_area_WA : "<<total_area_WA<<endl;
      fout<<"  total_area_WB : "<<total_area_WB<<endl;
   }
   fout.close(); 
}

