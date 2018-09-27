#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
const int NMAX=10000;
vector<int> g[NMAX];
vector< pair<int, int> > critical;
int n, counter, seen[NMAX], low[NMAX];
void dfs(int x, int parent)
{
    low[x]=seen[x]=++counter;

    for(int i=0; i<g[x].size(); i++)
    {
        int y=g[x][i];
        if(y==parent)
            continue;
        if(seen[y]==0)
        {
            dfs(y, x);
            low[x]=min(low[x], low[y]);
            if(low[y]==seen[y])
            {
                critical.push_back(make_pair(min(x, y), max(x, y)));
            }
        }
        else
            low[x]=min(low[x], seen[y]);
    }
}
void clear()
{
    for(int i=0; i<n; i++)
    {
        seen[i]=0;
        g[i].clear();
    }
    counter=0;
    critical.clear();
}
int main()
{
    //ifstream cin("input.txt");
    //freopen("input.txt", "r", stdin);
    while(cin>>n)
    {
        int x, y, m;
        clear();
        for(int i=0; i<n; i++)
        {
            scanf("%d (%d) ", &x, &m);
            for(int j=0; j<m; j++)
            {
                scanf("%d", &y);
                g[x].push_back(y);
            }
        }

        for(x=0; x<n; x++)
            if(seen[x]==0)
                dfs(x, -1);

        cout<<critical.size()<<" critical links\n";
        sort(critical.begin(), critical.end());
        for(int i=0; i<critical.size(); i++)
            cout<<critical[i].first<<' '<<'-'<<' '<<critical[i].second<<'\n';
        cout<<"\n";
    }
    //cout<<"\n";
    return 0;
}
