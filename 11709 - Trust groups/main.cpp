#include <cstdio>

#include <iostream>

#include <algorithm>

#include <string>

#include <stack>
#include <vector>
#include <map>

using namespace std;

map < string, int > sn;
map < int, string > ns;

int map_nodes;

int get_node(string name)
{
    if(sn.find(name) == sn.end())
    {
        sn[name] = ++map_nodes;
        ns[sn[name]] = name;
    }

    return sn[name];
}

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


        map_nodes = 0;
        sn.clear();
        ns.clear();

        comp_count=0;

        adj_list.assign(n + 1, vector < int > ());
        disc.assign(n + 1, -1);
        low.assign(n + 1, 0);
        in_stack.assign(n + 1, false);

        cin.ignore(1);

        for(int i=1; i<=n; i++)
        {
            string name;
            getline(cin, name);
            get_node(name);
        }

        for(int j = 1 ; j <= m ; ++j)
        {
            string name1, name2;
            getline(cin, name1);
            getline(cin, name2);

            int na, nb;
            na = get_node(name1);
            nb = get_node(name2);

            if(find(adj_list[na].begin(), adj_list[na].end(), nb) == adj_list[na].end())
                adj_list[na].push_back(nb);

        }

        for(int i = 1 ; i <= n ; ++i)
        {
            if(disc[i] == -1)
            {
                tarjan(i);
            }
        }

        cout<<comp_count<<'\n';
    }

    return 0;
}




