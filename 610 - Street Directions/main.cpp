#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
const int NMAX=1005;
vector<int> g[NMAX];
int counter, n, nr, low[NMAX], disc[NMAX], parent[NMAX], roads[NMAX][NMAX];
void find_bridge(int x)
{
    low[x]=disc[x]=++counter;
    for(int i=0; i<g[x].size(); i++)
    {
        int y=g[x][i];
        if(!disc[y])
        {
            parent[y]=x;
            find_bridge(y);
            low[x]=min(low[x], low[y]);
            if(low[y]>disc[x])
                roads[x][y]=roads[y][x]=1;
            else if(!roads[y][x])
                roads[x][y]=1;
        }
        else if(parent[x]!=y)
        {
            low[x]=min(low[x], disc[y]);
            if(!roads[y][x])
                roads[x][y]=1;
        }
    }
}
int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int m;
    while(cin>>n>>m && n && m)
    {
        for(int i=1; i<=m; i++)
        {
            int u, v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        counter=0;
        find_bridge(1);
        cout<<++nr<<"\n\n";
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(roads[i][j])
                    cout<<i<<' '<<j<<'\n';
        cout<<"#\n";

        memset(parent, 0, sizeof(parent));
        memset(low, 0, sizeof(low));
        memset(roads, 0, sizeof(roads));
        memset(disc, 0, sizeof(disc));
        for(int i=1; i<=n; i++)
            g[i].clear();
    }
    return 0;
}
