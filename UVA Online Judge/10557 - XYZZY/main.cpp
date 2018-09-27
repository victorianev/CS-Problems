#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
typedef vector<int> v;
typedef vector<v> m;
v d;
m g, w;
int nrn, nrm, s, useless1, useless2, NMAX = 100, INF = (1 << 20);
int bellmanford()
{
    d = v(nrn+1, 0);
    d[1] = 100;
    for (int ct = 0; ct < nrn +20005; ct++)
    {
        for (int i = 1; i <= nrn; i++)
        {
            for (int j = 0, u, v; j < g[i].size(); j++)
            {
                v = g[i][j];
                 u = i;
                if (d[u]>0)
                {
                    if (d[v] < d[u] + w[u][v])
                        d[v] = d[u] + w[u][v];
                }
            }
        }
    }
    if (d[nrn]>0)
        return 1;
    return 0;
}
int main()
{
    //ifstream cin("aici.in");
    //ofstream cout("aici.out");
    while(cin>>nrn&&nrn!=-1)
    {

        g = m(nrn+1, v());
        w = m(nrn+1, v(nrn+2, -INF));
        for (int i = 1; i <=nrn; i++)
        {
            int a, b, c, vic;
            cin>>a>>b;
            for(vic=1; vic<=b; vic++)
            {
                cin>>c;
                g[i].push_back(c);
                w[i][c] = a;
                //cout<<i<<' '<<c<<endl;
            }
        }
        
        if (bellmanford())
            cout << "winnable"<<'\n';

        else
            cout << "hopeless"<<'\n';
    }
    return 0;
}


