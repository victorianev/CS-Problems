#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
const int NMAX=1000000;
int a, b;
vector <int> primes;
bool v[NMAX];
void sieve()
{
    memset(v,1,sizeof(v));
    v[0]=v[1]=0;
    for(int i=4; i<NMAX; i+=2)
        v[i]=0;
    for(int i=3; i*i<=NMAX; i++)
        if(v[i])
            for(int j=i*i; j<NMAX; j+=2*i)
                v[j]=0;
    primes.clear();
    primes.push_back(2);
    for(int i=3; i<NMAX; i+=2)
        if(v[i])
            primes.push_back(i);

}
bool prime(int n)
{
    if(n<NMAX)
        return v[n];
    int i=0;
    while(primes[i]*primes[i]<=n){
        if(n%primes[i]==0)
            return 0;
     i++;}
    return 1;
}
int main()
{
    int i=0;
    //ifstream cin("date.in");
    sieve();
    bool x[10010];
    memset(x,0,sizeof(x));
    for(i=0; i<=10000; i++)
    {
        int nr=i*(i+1)+41;
        if(prime(nr))
            x[i]=1;
    }

    while(cin>>a>>b)
    {
        int cnt=0;
        for(i=a; i<=b; i++)
        {
            if(x[i])
                cnt++;
        }
        printf("%.2lf\n",(cnt*100.0)/(double)(b-a+1)+1e-9);
    }
    return 0;
}
