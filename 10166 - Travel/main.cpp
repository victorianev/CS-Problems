#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <tuple>
#include <iomanip>
using namespace std;
const int inf=(1<<30);
typedef tuple<int, int, int> tiii;
int main()
{
    //ifstream cin("input.txt");
    int n;
    while(cin>>n && n)
    {
        unordered_map<string, int> si;
        vector< vector<tiii> > g(n, vector< tiii > ());
        for(int i=0; i<n; i++)
        {
            string s;
            cin>>s;
            si[s]=i;
        }
        int lines;
        cin>>lines;
        for(int i=0; i<lines; i++)
        {
            vector< pair<int, int> > v;
            int m;
            cin>>m;
            for(int j=0; j<m; j++)
            {
                int time;
                string city;
                cin>>time>>city;
                v.push_back(make_pair(time, si[city]));

            }
            sort(v.begin(), v.end());
            for(int j=0; j<v.size()-1; j++)
            {
                int departure=v[j].first;
                int arrival=v[j+1].first;
                int start_nod=v[j].second;
                int end_nod=v[j+1].second;
                g[start_nod].push_back(make_tuple(end_nod, departure, arrival));
            }
        }

        int earliest_start_time, start_node, end_node;
        string s;
        cin>>earliest_start_time;
        cin>>s;
        start_node=si[s];
        cin>>s;
        end_node=si[s];

        int earliest_arrival_time=inf;
        int actual_start_time=0;

        for(auto &it: g[start_node])
        {
            int destination=get<0>(it);
            int departure=get<1>(it);
            int arrival=get<2>(it);
            if(earliest_start_time<=departure)
            {
                vector<int> dist(n, inf);
                priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > heap;
                dist[destination]=arrival;
                heap.push(make_pair(arrival, destination));

                while(!heap.empty())
                {
                    int d=heap.top().first;
                    int u=heap.top().second;
                    heap.pop();

                    if(dist[u]<d)
                        continue;

                    for(auto &it2: g[u])
                    {
                        int v=get<0>(it2);
                        int dep=get<1>(it2);
                        int duv=get<2>(it2);
                        if(d<=dep && duv<dist[v])
                        {
                            dist[v]=duv;
                            heap.push(make_pair(duv, v));
                        }
                    }
                }

                if(dist[end_node]<earliest_arrival_time)
                {
                    actual_start_time=departure;
                    earliest_arrival_time=dist[end_node];
                }
                else if(dist[end_node]==earliest_arrival_time)
                {
                    actual_start_time=max(actual_start_time, departure);
                    earliest_arrival_time=dist[end_node];
                }


            }
        }

        if(earliest_arrival_time!=inf)
            cout<<setfill('0')<<setw(4)<<actual_start_time<<' '<<setfill('0')<<setw(4)<<earliest_arrival_time<<'\n';
        else
            cout<<"No connection\n";
    }

    return 0;
}
