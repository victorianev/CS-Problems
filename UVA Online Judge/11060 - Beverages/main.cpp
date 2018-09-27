#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <map>
#include <string>
#include <iostream>
FILE *f;
using namespace std;
int main()
{
    //freopen("input.in", "r", stdin);
    int n;
    int cc=1;
    while(cin>>n)
    {
        bool G[n][n];
        bool mark[n];
        int in[n];
        for(int i =0; i<n; i++)
        {
            in[i]=mark[i]=0;
            for(int j = 0; j<n; j++)
                G[i][j]=0;
        }
        map<string,int> ind;
        string word[n];
        for(int i = 0; i<n; i++)
        {
            string s;
            cin>>s;
            ind[s]=i;
            word[i]=s;
        }
        int m;
        cin>>m;
        for(int i = 0; i<m; i++)
        {
            string s1,s2;
            cin>>s1>>s2;
            if(!G[ind[s1]][ind[s2]])
            {
                G[ind[s1]][ind[s2]]=true;
                in[ind[s2]]++;
            }
        }
        printf("Case #%d: Dilbert should drink beverages in this order:",cc++);
        bool done = false;
        while(!done)
        {
            done = true;
            for(int i  = 0; i<n; i++)
                if(!mark[i]&&in[i]==0)
                {
                    done=0;
                    mark[i]=1;
                    cout<<" "<<word[i];
                    for(int j =0; j<n; j++)
                        if(G[i][j])
                            in[j]--;
                    i = -1;
                }
        }
        putchar('.');
        putchar('\n');
        putchar('\n');
    }
}
