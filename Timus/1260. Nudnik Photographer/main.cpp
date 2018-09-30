#include <iostream>

using namespace std;
int dp[60];
int main()
{
    int n;
    cin>>n;
    dp[1]=dp[2]=1;
    dp[3]=2;
    for(int i=4; i<=n; i++)
        dp[i]=dp[i-1]+dp[i-3]+1;
    cout<<dp[n]<<'\n';
    return 0;
}
