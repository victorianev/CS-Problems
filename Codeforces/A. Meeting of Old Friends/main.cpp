#include <iostream>

using namespace std;

int main()
{
    long long l1, l2, r1, r2, k, sol;
    cin>>l1>>r1>>l2>>r2>>k;
    if(r1<l2 || r2<l1)
    {
        cout<<0<<'\n';
        return 0;
    }
    else if(l2<=r1 && r1<=r2 || l1<=r2 && r2<=r1)
    {
        sol=min(r1, r2)-max(l1, l2)+1;
        if(max(l1, l2)<=k && k<=min(r1, r2))
            sol--;
    }
    cout<<sol<<'\n';
    return 0;

}

