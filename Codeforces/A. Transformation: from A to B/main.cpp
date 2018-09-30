#include <iostream>

using namespace std;
long long sol[10000];
int main()
{
    long long a, b, k=0;
    int ok=1;
    cin>>a>>b;
    sol[++k]=b;
    while(b>a)
    {
        if(b%10==1)
        {
            sol[++k]=b/10;
            b/=10;
            continue;
        }
        else if(b%2==0)
        {
            sol[++k]=b/2;
            b/=2;
            continue;
        }
        ok=0;
        break;
    }
    if(b<a || !ok)
        cout<<"NO\n";
    else if(b==a)
    {
        cout<<"YES\n"<<k<<'\n';
        for(int i=k; i>=1; i--)
            cout<<sol[i]<<' ';
    }
    return 0;
}
