#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int dp[1001][1001];
int main()
{
    //ifstream cin("input.txt");
    //fstream cout("output.txt");
    string s1, s2;
    int cases=0;
    while(getline(cin, s1))
    {
        getline(cin, s2);
        int n=s1.length();
        int m=s2.length();
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(s1[i-1]==s2[j-1])
                    dp[i][j]=dp[i-1][j-1]+1;
                else if(dp[i-1][j]>=dp[i][j-1])
                    dp[i][j]=dp[i-1][j];
                else
                    dp[i][j]=dp[i][j-1];
        ++cases;
        cout<<dp[n][m]<<'\n';
    }
    return 0;
}
