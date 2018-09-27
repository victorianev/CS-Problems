#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
int main()
{
    //ifstream cin("input.in");
    int n, m, c;
    cin>>n;
    while(n--)
    {
        cin>>m>>c;
        vector< vector<int> > a(c);
        for(int i=0; i<c; i++)
        {
            int k;
            cin>>k;
            a[i].assign(k, 0);
            for(int j=0; j<k; j++)
                cin>>a[i][j];
        }
        vector< vector<int> > dp(m+1, vector<int> (c+1, -2));
        for(int i=0; i<=m; i++)
        {
            dp[i][0]=0;
            for(int j=1; j<=c; j++)
                for(auto& sp: a[j-1])
                    if(i>=sp && dp[i-sp][j-1]!=-2)
                        dp[i][j]=max(dp[i][j], dp[i-sp][j-1]+sp);
        }


        if(dp[m][c]==-2)
            cout<<"no solution\n";
        else
            cout<<dp[m][c]<<"\n";
    }
    return 0;
}
