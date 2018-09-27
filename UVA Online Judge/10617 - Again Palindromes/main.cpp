#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    //ifstream cin("input.txt");
    int tests;
    cin>>tests;
    cin.get();
    while(tests--)
    {
        string line;
        getline(cin, line);
        int n=line.size();
        vector< vector<long long> > dp(n, vector<long long>(n, 1));
        for(int i=0; i<n-1; i++)
            if(line[i]==line[i+1])
                dp[i][i+1]=3;
            else
                dp[i][i+1]=2;

        for(int k=2; k<n; k++)
            for(int i=0; k+i<n; i++)
            {
                int j=i+k;
                if(line[i]==line[j])
                    dp[i][j]=dp[i][j-1]+dp[i+1][j]+1;
                else
                    dp[i][j]=dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1];

            }
        cout<<dp[0][n-1]<<'\n';
    }
    return 0;
}
