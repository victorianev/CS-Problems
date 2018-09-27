#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int NMAX=105;
map<int, string> ns;
map<string, int> sn;
vector<int> g[NMAX], low, discover, parent;
vector<bool> articulation_vertex;
int timp, dfsRoot, rootChildren;
void tarjan(int u)
{
    timp++;
    discover[u]=low[u]=timp;
    for(int i=0; i<g[u].size(); i++)
    {
        int v=g[u][i];
        if(discover[v]==-1)
        {
            parent[v]=u;
            if(u==dfsRoot)
                rootChildren++;
            tarjan(v);
            if(low[v]>=discover[u])
                articulation_vertex[u]=1;
            low[u]=min(low[u], low[v]);
        }
        else if(v!=parent[u])
        {
            low[u]=min(low[u], discover[v]);
        }

    }
}
int main()
{
    //ifstream cin("input.txt");
    int n, m, i, tests=0, number, first=1;
    while(cin>>n && n)
    {
        string s;
        int nr=0;
        number=0;
        if(tests>=1)
        {
            cout<<'\n';
        }
        for(i=1; i<=n; i++)
        {
            cin>>s;
            nr++;
            sn[s]=nr;
            ns[nr]=s;
        }

        cin>>m;
        for(i=1; i<=n; i++)
            g[i].clear();
        string s1, s2;
        for(i=1; i<=m; i++)
        {
            cin>>s1>>s2;
            g[sn[s1]].push_back(sn[s2]);
            g[sn[s2]].push_back(sn[s1]);
        }

        discover.assign(n+1, -1);
        low.assign(n+1, 0);
        parent.assign(n+1, 0);
        articulation_vertex.assign(n+1, 0);
        for(i=1; i<=n; i++)
            if(discover[i]==-1)
            {
                dfsRoot=i;
                rootChildren=0;
                tarjan(i);
                articulation_vertex[dfsRoot]=(rootChildren>1);
            }
        ++tests;
        vector<string> solution;
        for(i=1; i<=n; i++)
            if(articulation_vertex[i])
                solution.push_back(ns[i]);

        cout<<"City map #"<<tests<<": "<< solution.size() <<" camera(s) found"<<'\n';

        sort(solution.begin(), solution.end());

        for(auto& name : solution)
            cout << name << "\n";
    }
    return 0;
}
