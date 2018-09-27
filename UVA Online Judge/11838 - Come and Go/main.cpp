#include <cstdio>

#include <iostream>

#include <algorithm>

#include <string>

#include <stack>
#include <vector>

using namespace std;

vector < vector < int > > adj_list, components;
vector < int > disc, low;
vector < bool > in_stack;

stack < int > st;

int timp, comp_count;

void tarjan(int u)
{
    disc[u] = low[u] = timp++;
    st.push(u);
    in_stack[u] = true;

    size_t i;
    for(i = 0 ; i < adj_list[u].size() ;  ++i)
    {
        int v = adj_list[u][i];

        if(disc[v] == -1)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(in_stack[v])
        {
            low[u] = min(low[u], low[v]);
        }
    }

    if(disc[u] == low[u])
    {
        int node;

        do
        {
            node = st.top();
            st.pop();
            in_stack[node] = false;
        }
        while(node != u);

        comp_count++;
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;

    int data_set = 0;

    while(cin >> n >> m)
    {
        if(n==0&&m==0)
            return 0;

        comp_count=0;

        adj_list.assign(n + 1, vector < int > ());
        disc.assign(n + 1, -1);
        low.assign(n + 1, 0);
        in_stack.assign(n + 1, false);

        for(int j = 1 ; j <= m ; ++j)
        {
            int na, nb, way;
            cin>>na>>nb>>way;
            adj_list[na].push_back(nb);
            if(way==2)
                adj_list[nb].push_back(na);

        }

        for(int i = 1 ; i <= n ; ++i)
        {
            if(disc[i] == -1)
            {
                tarjan(i);
            }
        }
        if(comp_count==1)
            cout<<1<<'\n';
        else cout<<0<<'\n';
    }

    return 0;
}
