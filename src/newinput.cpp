# include <iostream>
# include <fstream>
# include <ctime>
# include <cstdlib>
# include <queue>
# include <vector>

using namespace std;

#define SHAPE_MAX_LEN 4
#define MAP_LEN 1000
#define TEST_NUM 100 //test can the random shape be put in

typedef struct
{
  int len[4]; // 1 for x1, 2 for y1, 3 for x2, 4 for y2
}Shape;

typedef struct
{
  int pos[2];
}Pos;

void writeMap(const char *, vector<Shape>&);
void writeFile(const char *, vector<Shape>&);

enum coordinate{x1, y1, x2, y2};

int alpha, beta, omega;

int main(int argc, char **argv)
{
  srand(time(NULL));
  int maxShapeNum;
  cout << "max shapeNum = ";
  cin >> maxShapeNum;
  cout << "ALPHA = ";
  cin >> alpha;
  cout << "BETA = ";
  cin >> beta;
  cout << "OMEGA = ";
  cin >> omega;


  bool **oriMap = new bool* [MAP_LEN];
  for(int i=0; i < MAP_LEN; ++i){
    oriMap[i] = new bool [MAP_LEN];
    for(int j=0; j < MAP_LEN; ++j)
      oriMap[i][j] = false;
  }

  vector<Shape> vecShape;
  queue<Pos> posQue;
  Pos initPos = {{0,0}};
  Pos nowPos;
  Pos tmpPos;
  posQue.push(initPos); 

  for(int n=0; n < maxShapeNum; ++n){   

    if(!posQue.empty()){
      nowPos = posQue.front();
      posQue.pop();
    }
    else
      break;

    Shape shape;
    bool isExist = false;
    for(int k=0; k<TEST_NUM; ++k){

      shape.len[x1] = nowPos.pos[x1];
      shape.len[y1] = nowPos.pos[y1];
      shape.len[x2] = rand() % SHAPE_MAX_LEN + nowPos.pos[x1];
      shape.len[y2] = rand() % SHAPE_MAX_LEN + nowPos.pos[y1];
      
      bool occupy = false;
      
      for(int m=0; m<4; ++m)
        if(shape.len[m] >= MAP_LEN) occupy = true;
      
      int i  = shape.len[x1] - 1; if(i<0) i=0;
      int j  = shape.len[y1] - 1; if(j<0) j=0;
      int tmp = j;
      int ii = shape.len[x2] + 1; if(ii>=MAP_LEN) ii = MAP_LEN-1;
      int jj = shape.len[y2] + 1; if(jj>=MAP_LEN) jj = MAP_LEN-1;
      for(; !occupy && i <= ii ; ++i)
        for(j = tmp; !occupy && j <= jj; ++j)
          if(oriMap[i][j]) occupy = true;
      
      if(!occupy){

        for(i=shape.len[x1]; i<=shape.len[x2]; ++i)
          for(j=shape.len[y1]; j<=shape.len[y2]; ++j)
            oriMap[i][j] = true;

        tmpPos.pos[x1] = shape.len[x2] + 2;
        tmpPos.pos[y1] = shape.len[y1];
        posQue.push(tmpPos);

        tmpPos.pos[x1] = shape.len[x1];
        tmpPos.pos[y1] = shape.len[y2] + 2;
        posQue.push(tmpPos);
        
        vecShape.push_back(shape); 
        isExist = true;
        break;
      }   
      //if(!isExist) --n;
    }
  }
  cout << vecShape.size();
  //writeFile(argv[1], oriMap);
  writeFile(argv[1], vecShape);
}


void writeFile(const char *fileName, vector<Shape>& vecShape)
{
  ofstream fout(fileName);

  int x_dir[MAP_LEN + 1] = {};
  int y_dir[MAP_LEN + 1] = {};

  for(int i = 1; i < MAP_LEN + 1; i++){
    x_dir[i] = x_dir[i-1] + rand() % MAP_LEN + 1;
    y_dir[i] = y_dir[i-1] + rand() % MAP_LEN + 1;
  }
  
  fout << "ALPHA=" << alpha << endl; 
  fout << "BETA="  << beta  << endl;
  fout << "OMEGA=" << omega << endl;
  
  int n = vecShape.size();
  Shape shape;
  for(int i = 0; i < n; i++){
    shape = vecShape[i];
    fout << x_dir[ shape.len[x1] ] << ","
         << y_dir[ shape.len[y1] ] << ","
         << x_dir[ shape.len[x2] + 1 ] << ","
         << y_dir[ shape.len[y2] + 1 ] << endl;
  }
  
  fout.close();
}

void writeMap(const char *fileName, vector<Shape>& vecShape)
{
  ofstream fout (fileName);
  
  char a[MAP_LEN][MAP_LEN];
  for(int i=0;i<MAP_LEN;++i)
    for(int j=0; j<MAP_LEN;++j)
      a[i][j]='.';
  
  char k='0';
  int xx1,xx2,yy1,yy2;
  
  for(int i=0; i < vecShape.size();++i){
    xx1 = vecShape[i].len[x1];
    yy1 = vecShape[i].len[y1];
    xx2 = vecShape[i].len[x2];
    yy2 = vecShape[i].len[y2];
    
    for(int ii = xx1 ; ii <= xx2 ; ++ii)
      for(int jj = yy1 ; jj <= yy2 ; ++jj)
        a[ii][jj] = k;
    
    if(k == '9') k = '0';
    else k = k + 1; 
  }

  for(int j=0 ; j < MAP_LEN ; ++j){
    for(int i=0 ; i < MAP_LEN ; ++i)
      fout << a[i][j];
    fout << endl;
  }
  fout.close();
}
