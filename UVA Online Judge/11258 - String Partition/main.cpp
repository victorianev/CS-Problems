#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
using namespace std;
char line[205];
int n;
long long memo[205];
long long f(long long i)
{
    if(memo[i]!=-1)
        return memo[i];
    if(i==n)
        return memo[i]=0;
    if(line[i]=='0')
        return memo[i]=f(i+1);

    int k=1, j;
    long long ans=0, pref;
    while(true)
    {
        pref=0;
        for(j=i; j<(k+i); j++)
        {
            pref=pref*10+line[j]-'0';
        }
        if(pref>INT_MAX)
            break;
        ans=max(ans, (int)pref+f(i+k));
        k++;
        if(k+i>n)
            break;
    }
    return memo[i]=ans;
}
int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int tests;
    cin>>tests;
    while(tests--)
    {
        cin>>line;
        n=strlen(line);
        memset(memo, -1, sizeof(memo));
        long long ans=f(0);
        cout<<ans<<'\n';
    }
    return 0;
}
