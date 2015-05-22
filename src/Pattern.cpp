#include "pattern.h"
#include <istream>
#include <sstream>

Patten::Pattern(int a, int b, int o)
{
    _alpha = a;
	_beta = b;
	_omega = o;
}

bool readfile( char *filename )
{
	ifstream fin( filename );
	if( fin.fail() )
		return false;

	string buf;
	char trash;
	int x1, x2, y1, y2;
    stringstream ss("");
	while( getline(fin, buf) ){
	    switch(buf[0]){
			case 'A':
				ss << buf;
				ss >> _alpha;
			case 'B':
				ss << buf;
				ss >> 
				
				
				
				
		}
	
	
	}

}
