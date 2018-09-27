#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int NMAX=1005;
int n, m, a[NMAX][NMAX], s=0;
void fill(int x, int y)
{
    if(x<1 || y<1 || x>n || y>m)
        return ;
    if(a[x][y]==1 || a[x][y]==2 || a[x][y]==4)
        return ;
    if(a[x][y]==3)
    {
        s++;
        //cout<<s<<'\n';
        a[x][y]=4;
    }
    if(a[x+1][y]==2 || a[x][y+1]==2 || a[x-1][y]==2 || a[x][y-1]==2)
        return ;

    a[x][y]=4;
    fill(x, y+1);
    fill(x, y-1);
    fill(x-1, y);
    fill(x+1, y);
}
int main()
{
    //ifstream cin("input.txt");
    int i, j, posx, posy;
    char x;
    while(cin>>m>>n)
    {
        memset(a, 0, sizeof(a));
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=m; j++)
            {
                cin>>x;
                if(x=='#')a[i][j]=1;
                else if(x=='T')a[i][j]=2;
                else if(x=='G')a[i][j]=3;
                else if(x=='P')
                {
                    posx=i;
                    posy=j;
                }
            }
        }
        s=0;
        fill(posx, posy);
        cout<<s<<'\n';
    }
    return 0;
}
