#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector< vector<int> > g;
vector<int> colour;
bool f(int u)
{
    bool sol=1;
    for(int i=0; i<g[u].size(); i++)
    {
        int v=g[u][i];
        if(colour[v] && colour[u]==colour[v])
            return 0;
        if(colour[v]==0)
        {
            colour[v]=(colour[u]==1? 2:1);
            sol=sol&f(v);
        }
    }
    return sol;

}
int main()
{
    //ifstream cin("input.txt");
    int m, n, i, u, v;
    while(cin>>n&& n)
    {
        cin>>m;
        g.clear();
        g.resize(n);
        colour.assign(n, 0);
        for(i=1; i<=m; i++)
        {
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        colour[0]=1;
        if(f(0))
            cout<<"BICOLORABLE.\n";
        else cout<<"NOT BICOLORABLE.\n";
    }
    return 0;
}
