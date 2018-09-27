#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
using namespace std;
const int NMAX=10005;
int n, Time, dfsRoot, rootChildren;
vector<int> g[NMAX], dfs_discover, dfs_low, articulation_vertex, dfs_parent;
void articulationPoint(int u)
{
    int i, v;
    ++Time;
    dfs_discover[u]=dfs_low[u]=Time;
    for(i=0; i<g[u].size(); i++)
    {
        v=g[u][i];
        if(!dfs_discover[v])
        {
            dfs_parent[v]=u;
            if(u==dfsRoot)rootChildren++;
            articulationPoint(v);
            if(dfs_low[v]>=dfs_discover[u])
                articulation_vertex[u]=1;
            dfs_low[u]=min(dfs_low[u], dfs_low[v]);
        }
        else if(v!=dfs_parent[u])
            dfs_low[u]=min(dfs_low[u], dfs_discover[v]);
    }
}
int main()
{
    int m, u, v, i;
    char s[1000], emp[10];
    while ( scanf ("%d", &n) && n )
    {
        getchar ();
        char input [10000];
        for(i=0; i<=n; i++)
            g[i].clear();//int u=0;
        while ( gets (input) && strcmp (input, "0"))
        {
            char *pch;
            pch = strtok (input, " ");

            int u = atoi (pch);
            // u++;
            pch = strtok (NULL, " ");

            while ( pch != NULL )
            {
                int v = atoi (pch);
                g[u].push_back (v);
                g[v].push_back (u);
                pch = strtok (NULL, " ");
            }
        }


        dfs_parent.assign(n+1, 1);
        articulation_vertex.assign(n+1, 0);
        dfs_low.assign(n+1, 0);
        dfs_discover.assign(n+1, 0);
        for(i=1; i<=n; i++)
            if(!dfs_discover[i])
            {
                dfsRoot=i;
                rootChildren=0;
                articulationPoint(i);
                articulation_vertex[dfsRoot]=(rootChildren>1);
            }
        int theirnumber=0;
        for(i=1; i<=n; i++)
            if(articulation_vertex[i])
                theirnumber++;
        printf("%d\n", theirnumber);
    }
    return 0;
}
