#include <iostream>
#include <cstring>
using namespace std;
long long memo[16][2];
int n, k;
long long count(int n, int zeros)
{
    if(zeros==2)
        return 0;
    if(n==1)
        return (zeros==1? k-1:k);
    long long ret=memo[n][zeros];
    if(ret==-1)
    {
        ret=(zeros==1? 0:count(n-1, 1));
        ret+=(k-1)*count(n-1, 0);
    }
    return ret;
}
int main()
{
    cin>>n>>k;
    memset(memo, -1, sizeof(memo));
    long long ans=(k-1)*count(n-1, 0);
    cout<<ans<<'\n';
    return 0;
}
