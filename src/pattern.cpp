#include "pattern.h"
#include <fstream>
#include <sstream>

Shape::Shape(int, int, int, int, int)
{
  _x1 = 0;
  _x2 = 0;
  _y1 = 0;
  _y2 = 0;
}


Pattern::Pattern()
{
  _alpha = 0;
  _beta = 0;
  _omega = 0;
}

bool Pattern::readfile( char *filename )
{
  ifstream fin( filename );
  if( fin.fail() )
    return false;

  stringstream ss("");
  string buf;
  char ch;
  int id=0;
  int x1, x2, y1, y2;
  while( getline(fin, buf) ){
    if(buf.size()==0)
      continue;
    ss.str("");
    ss.clear();
    ss << buf;
    switch(buf[0]){
      case 'A':
        for(int i=0; i<6; ++i)
          ss >> ch;
        ss >> _alpha;
        break;
      case 'B':
        for(int i=0; i<5; ++i)
          ss >> ch;
        ss >> _beta;
        break;
      case 'O':
        for(int i=0; i<6; ++i)
          ss >> ch;
        ss >> _omega;
        break;
      default:
        ss >> x1 >> ch >> y1 >> ch >> x2 >> ch >> y2;
        ++id;
        Shape tmp(id, x1, x2, y1, y2);
        _shapes.push_back(tmp);
        break;
    }
    buf.clear();
  }
}

