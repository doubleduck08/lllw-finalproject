#include<fstream>
#include<cstdlib>
#include<ctime>

int max(int a,int b)
{
    if (a>b) return a;
    else return b;
}

int min(int a,int b)
{
    if (a<b) return a;
    else return b;
}

int main()
{
    srand((unsigned)time(NULL));
    bool all[1861][1261];
    for (int i=0 ; i<1261 ; i++)
        for (int j=0 ; j<1861 ; j++)
            all[i][j]=false;
    int x1[16],y1[16],x2[16],y2[16];
    int pos=0;
    bool test=true;
    for (int i=1 ; i<=4 ; i++)
    {
        x1[pos]=rand()%930;
        y1[pos]=rand()%630;
        while (all[x1[pos]][y1[pos]]) {           
           x1=rand()%930;
           y1=rand()%630;
        }
        x2[pos]=rand()%930;
        y2[pos]=rand()%630;
        test=false;
        while (all[x2[pos]][y2[pos]] || 
               (x1[pos]==x2[pos]||y1[pos]==y2[pos]) || test)
        {    
           x2[pos]=rand()%930;
           y2[pos]=rand()%630;
           for (int j=min(x1[pos],x2[pos]) ; j<=max(x1[pos],x2[pos]) ; j++)
               for (int k=min(y1[pos],y2[pos]) ; k<=max(y1[pos],y2[pos]) ; k++)
                   if (all[j][k]) 
        }   
        
    }
    for (int i=1 ; i<=4 ; i++)
    {
        
    }
    for (int i=1 ; i<=4 ; i++)
    {
        
    }
    for (int i=1 ; i<=4 ; i++)
    {
        
    }
}
