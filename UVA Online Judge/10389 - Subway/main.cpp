#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;
const int NMAX=205;
const int INF=(1<<30);
double distance(int x1, int y1, int x2, int y2)
{
    int dx=x1-x2;
    int dy=y1-y2;
    return sqrt(dx*dx+dy*dy)*60/10000;
}
int main()
{
    //ifstream cin("input.txt");
    int tests;
    cin>>tests;
    int new_line=0;
    while(tests--)
    {
        vector< vector< pair<int, double> > > g(NMAX);
        vector<int> x(NMAX), y(NMAX);
        cin>>x[1]>>y[1]>>x[2]>>y[2];
        double d=distance(x[1], y[1], x[2], y[2]);
        g[1].push_back(make_pair(2, d));
        g[2].push_back(make_pair(1, d));
        int n=3;
        cin.get();
        string line;
        while(getline(cin, line) && line!="" && line[0]!=' ')
        {
            stringstream sin(line);
            int p=0;
            while(sin>>x[n]>>y[n])
            {
                if(x[n]==-1 && y[n]==-1)
                    break;
                if(p>0)
                {
                    double d=distance(x[n-1], y[n-1], x[n], y[n])/4;
                    g[n-1].push_back(make_pair(n, d));
                    g[n].push_back(make_pair(n-1, d));
                }
                for(int i=1; i<=n; i++)
                {
                    double d=distance(x[n], y[n], x[i], y[i]);
                    g[i].push_back(make_pair(n, d));
                    g[n].push_back(make_pair(i, d));
                }
                n++;
                p++;
            }
        }
        n--;
        vector<double> dist(n+1, INF);
        dist[1]=0;
        typedef pair<double, int> pair_di;
        priority_queue< pair_di, vector<pair_di>, greater<pair_di> > heap;
        heap.push(make_pair(0, 1));
        int total=1;
        while(total<=n && !heap.empty())
        {
            int u=heap.top().second;
            double d=heap.top().first;
            heap.pop();
            if(d>dist[u])
                continue;
            total++;
            for(auto& vp:g[u])
            {
                int v=vp.first;
                double duv=vp.second;
                if(dist[u]+duv<dist[v])
                {
                    dist[v]=dist[u]+duv;
                    heap.push(make_pair(dist[v], v));
                }

            }

        }
        if(new_line++)
            cout<<"\n";
        cout<<(int)round(dist[2])<<"\n";
    }
    return 0;
}
