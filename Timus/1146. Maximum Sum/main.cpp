#include <iostream>

using namespace std;
int m[100][100], s[100][100], dp[100];
int max(int a, int b)
{
    if(a>=b)
        return a;
    return b;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>m[i][j];

    for(int i=0; i<n; i++)
        s[i][0]=0;

    for(int i=0; i<n; i++)
        for(int j=1; j<=n; j++)
            s[i][j]=s[i][j-1]+m[i][j-1];

    int ans=m[0][0];

    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
        {
            dp[0]=s[0][j+1]-s[0][i];
            ans=max(ans, dp[0]);

            for(int k=1; k<n; k++)
            {
                int aux=s[k][j+1]-s[k][i];
                dp[k]=aux+max(0, dp[k-1]);
                ans=max(ans, dp[k]);
            }
        }

    cout<<ans;
    return 0;
}
