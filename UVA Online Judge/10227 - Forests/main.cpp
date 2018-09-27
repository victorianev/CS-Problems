#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;
const int NMAX=105;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> vi;

vector<vi> opinionGraph;
int parent[NMAX];
int rrank[NMAX];

void make_sets(int number_of_elements)
{
    int i;
    for(int i=0; i<number_of_elements; i++)
    {
        parent[i]=i;
        rrank[i]=1;
    }
}

int find_set(int x)
{
    if(x!=parent[x])
        parent[x]=find_set(parent[x]);
    return parent[x];
}

void set_union(int x, int y)
{
    int rx, ry;
    rx=find_set(x);
    ry=find_set(y);
    if(rx==ry)
        return;
    if(rrank[rx]>rrank[ry])
    {
        rrank[ry]+=rrank[ry];
        parent[ry]=rx;
    }
    else
    {
        rrank[ry]+=rrank[rx];
        parent[rx]=ry;
    }
}

void read_graph()
{
    string str;
    stringstream ss;
    int people, tree, data;

    while(getline(cin, str))
    {
        int flag=0;
        if(str.size()==0)
            return;
        ss<<str;
        while(ss>>data)
        {
            if(!flag)
            {
                people=data;
                flag=1;
            }
            else tree=data;
        }
        ss.clear();
        opinionGraph[people-1].insert(tree-1);
    }
}

int main()
{
    int cases, people, trees;
    string trash;

    scanf("%d", &cases);
    getline(cin, trash);
    getline(cin, trash);
    while(cases--)
    {
        scanf("%d %d", &people, &trees);
        opinionGraph.assign(people, vi());
        getline(cin, trash);
        read_graph();

        make_sets(people);
        for(int i=0; i<opinionGraph.size(); i++)
            for(int j=i+1; j<opinionGraph.size(); j++)
                if(opinionGraph[i]==opinionGraph[j])
                    set_union(parent[i], parent[j]);

        for(int i=0; i<people; i++)
            parent[i]=find_set(i);

        int total=0;
        set<int> answer;
        for(int i=0; i<people; i++)
            answer.insert(parent[i]);

        printf("%d\n", answer.size());
        if(cases)
            printf("\n");
    }
    return 0;
}
