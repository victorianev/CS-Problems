#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <fstream>
using namespace std;
const int inf=(1<<29);
const int NMAX=505;
typedef tuple<int, int, int> tiii;
int main()
{
    //ifstream cin("input.txt");
    int tests;
    cin>>tests;
    while(tests--)
    {
        int a, b, m, l, nr;
        cin>>a>>b>>m>>l>>nr;
        vector< vector<int> > adj(a+b+1, vector<int>(a+b+1, inf));

        for(int i=1; i<=m; i++)
        {
            int u, v, c;
            cin>>u>>v>>c;
            adj[u][v]=c;
            adj[v][u]=c;
        }

        for(int k=1; k<=a; k++)
            for(int i=1; i<=a+b; i++)
                for(int j=1; j<=a+b; j++)
                    adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);

        priority_queue< tiii, vector<tiii>, greater<tiii> > heap;
        heap.push(make_tuple(0, a+b, nr));
        vector< vector<int> > dp(a+b+1, vector<int>(nr+1, inf));
        dp[a+b][nr]=0;

        while(!heap.empty())
        {
            int d=get<0>(heap.top());
            int u=get<1>(heap.top());
            int left=get<2>(heap.top());
            heap.pop();

            if(u==1)
            {
                cout<<d<<'\n';
                break;
            }

            for(int i=1; i<=a+b; i++)
            {
                if(i==u || adj[u][i]==inf)
                    continue;

                if(dp[i][left]>dp[u][left]+adj[u][i])
                {
                    dp[i][left]=dp[u][left]+adj[u][i];
                    heap.push(make_tuple(dp[i][left], i, left));
                }

                if(adj[u][i]<=l && dp[i][left-1]>dp[u][left] && left>0)
                {
                    dp[i][left-1]=dp[u][left];
                    heap.push(make_tuple(dp[i][left-1], i, left-1));
                }

            }
        }
    }
    return 0;
}
