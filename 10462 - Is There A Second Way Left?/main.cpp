#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int tests;
    cin>>tests;
    for(int t=1; t<=tests; t++)
    {
        int n, m;
        cin>>n>>m;
        if(n==1 && m==0)
        {
            cout<<"Case #"<<t<<" : "<<"No second way\n";
            continue;
        }

        vector< vector< pair<int, int> > > g(n+1, vector< pair<int, int >>());
        for(int i=1; i<=m; i++)
        {
            int u, v, c;
            cin>>u>>v>>c;
            g[u].push_back(make_pair(v, c));
            g[v].push_back(make_pair(u, c));
        }
        vector<bool> vis(n+1, 0);
        priority_queue< tuple<int, int, int>, vector< tuple<int, int, int> >, greater< tuple<int, int, int> > > heap;
        vis[1]=1;
        int nr1, nr2;
        nr1=1;
        for(auto &it: g[1])
        {
            int v=it.first;
            int c=it.second;
            if(!vis[v])
                heap.push(make_tuple(c, v, 1));
        }
        int cost1=0;
        vector< tuple<int, int, int> > vic;
	// first minimum spanning tree
        while(!heap.empty())
        {
            int d=get<0>(heap.top());
            int u=get<1>(heap.top());
            int v=get<2>(heap.top());
            heap.pop();

            if(vis[u])
                continue;

            vis[u]=1;
            nr1++;
            vic.push_back(make_tuple(u, v, d));
            for(auto &it: g[u])
            {
                int v=it.first;
                int c=it.second;
                if(!vis[v])
                    heap.push(make_tuple(c, v, u));
            }
            cost1+=d;
        }
        int cost2=(1<<29);
        int ok=0;
        for(auto &it: vic)
        {
            int u=get<0>(it);
            int v=get<1>(it);
            int c=get<2>(it);

            auto edge1=find(g[u].begin(), g[u].end(), make_pair(v, c));
            g[u].erase(edge1);
            auto edge2=find(g[v].begin(), g[v].end(), make_pair(u, c));
            g[v].erase(edge2);

            vector<bool> vis(n+1, 0);
            priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > heap;
            vis[1]=1;
            for(auto &it: g[1])
            {
                int v=it.first;
                int c=it.second;
                if(!vis[v])
                    heap.push(make_pair(c, v));
            }

            // second minimum spanning tree
            nr2=1;
            int cost=0;
            while(!heap.empty())
            {
                int d=heap.top().first;
                int u=heap.top().second;
                heap.pop();

                if(vis[u])
                    continue;

                vis[u]=1;
                nr2++;
                for(auto &it: g[u])
                {
                    int v=it.first;
                    int c=it.second;
                    if(!vis[v])
                        heap.push(make_pair(c, v));
                }
                cost+=d;
            }

            if(nr2==n)
                cost2=min(cost2, cost);

            g[u].push_back(make_pair(v, c));
            g[v].push_back(make_pair(u, c));
        }
        if(nr1!=n)
            cout<<"Case #"<<t<<" : "<<"No way\n";
        else if(cost2 == (1<<29))
            cout<<"Case #"<<t<<" : "<<"No second way\n";
        else
            cout<<"Case #"<<t<<" : "<<cost2<<'\n';
    }
    return 0;
}
