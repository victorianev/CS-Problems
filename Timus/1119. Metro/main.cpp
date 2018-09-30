#include <iostream>
#include <vector>
using namespace std;
double min(double a, double b)
{
    if(a<=b)
        return a;
    return b;
}
int main()
{
    int n, m;
    cin>>n>>m;
    vector< vector<bool> > a(m+1, vector<bool> (n+1));
    int k;
    cin>>k;
    for(int i=1; i<=k; i++)
    {
        int x, y;
        cin>>x>>y;
        a[y][x]=1;
    }
    vector<double> b(n+1);
    for(int i=0; i<=n; i++)
        b[i]=(double)i;
    for(int y=1; y<=m; y++)
    {
        double t=b[0];
        b[0]+=1.0;
        for(int x=1; x<=n; x++)
        {
            double d=b[x];
            if(a[y][x])
                b[x]=t+1.414213562;
            else
                b[x]=min(b[x-1], b[x])+1;
            t=d;
        }
    }
    cout<<(int)(b[n]*100.0+0.5);
    return 0;
}
