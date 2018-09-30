#include <iostream>
#include <algorithm>
using namespace std;
long long v[2002],j,S=0,maxi,i,sol[2002],n,p,cate,poz,k,m;
int main()
{
    cin>>n;
    maxi=-1;
    S=0;
    for (i=1; i<=n; i++)
        cin>>v[i];
    sort(v+1,v+n+1);
    m=v[n];
        S=0;
        cate=0;
        for (j=1; j<=n; j++)
            if ((S+v[j])<=m)
            {
                S+=v[j];
                cate++;
            }
            else
            {
                p++;
                cate++;
                break;
            }
    cout<<cate;
    return 0;
}
