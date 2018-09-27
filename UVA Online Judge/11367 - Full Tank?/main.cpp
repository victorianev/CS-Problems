#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
const int inf=(1<<30);
typedef pair<int, int> pair_ii;
typedef tuple<int, int, int> tuple_iii;
int main()
{
    //ifstream cin("input.txt");
    int n, m, queries, i, u, v, w, tank;
    cin>>n>>m;
    vector<int> fuel_price(n+1);
    for(i=0; i<n; i++)
        cin>>fuel_price[i];
    vector< vector< pair<int, int> > > adj_list(n+1);
    for(i=1; i<=m; i++)
    {
        cin>>u>>v>>w;
        adj_list[u].push_back(make_pair(v, w));
        adj_list[v].push_back(make_pair(u, w));
    }
    cin>>queries;
    while(queries--)
    {
        int c, s, e;
        cin>>c>>s>>e;
        vector< vector<int> > dp(n+1, vector<int> (105, inf));
        priority_queue< tuple_iii, vector<tuple_iii>, greater<tuple_iii> > heap;
        heap.push(make_tuple(0, 0, s));
        dp[s][0]=0;
        int result=inf;
        while(!heap.empty())
        {
            int d=get<0>(heap.top());
            int g=get<1>(heap.top());
            int u=get<2>(heap.top());
            heap.pop();
            if(u==e)
            {
                result=d;
                break;
            }
            if(dp[u][g]<d)
                continue;
            if(g<c && d+fuel_price[u]<dp[u][g+1])
            {
                dp[u][g+1]=d+fuel_price[u];
                heap.push(make_tuple(dp[u][g+1], g+1, u));
            }
            for(auto& vp: adj_list[u])
            {
                int v=vp.first;
                int duv=vp.second;
                if(g>=duv)
                {
                    int new_gas=g-duv;
                    if(d<dp[v][new_gas])
                    {
                        dp[v][new_gas]=d;
                        heap.push(make_tuple(d, new_gas, v));
                    }
                }
            }
        }
        if(result==inf)
            cout<<"impossible\n";
        else
            cout<<result<<'\n';
    }
    return 0;
}
