#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    double a0, an1, c[3005];
    cin>>n;
    cin>>a0>>an1;
    for(int i=1; i<=n; i++)
        cin>>c[i];
    int p=0;
    double s=0.0;
    for(int i=n; i>=1; i--)
    {
        p++;
        s=s+c[i]*p;
    }
    cout<<setprecision(2)<<fixed<<(double)(n*a0+an1-2.0*s)/(n+1)<<'\n';
    return 0;
}
