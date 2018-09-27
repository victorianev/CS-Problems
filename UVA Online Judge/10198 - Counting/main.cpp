#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
const int MAX_DIGITS=10000;
const int BASE=10;
const int MAX_INT=(1LL<<31)-1;
char s[MAX_DIGITS+5];
class HugeN
{
private:
    int x[MAX_DIGITS+5];
public:
    HugeN()
    {
        x[0]=1;
        for(int i=1; i<=MAX_DIGITS; i++)
            x[i]=0;
    }

    HugeN(int nr)
    {
        for(int i=0; i<=MAX_DIGITS; i++)
            x[i]=0;
        do
        {
            x[++x[0]]=nr%10;
            nr/=BASE;
        }
        while(nr);
    }

    HugeN(const HugeN &other)
    {
        for(int i=1; i<=MAX_DIGITS; i++)
            x[i]=0;
        memcpy(x, other.x, sizeof(other.x));
        x[0]=other.x[0];
    }

    HugeN(char *s)
    {
        x[0]=strlen(s);
        for(int i=1; i<=x[0]; i++)
            x[i]=s[x[0]-i]-'0';
    }

    void print()
    {
        int i;
        for(int i=x[0]; i>=1; i--)
            cout<<x[i];
        cout<<"\n";
    }

    HugeN operator + (const HugeN &other);
    HugeN operator * (int k);

};

HugeN HugeN::operator + (const HugeN &other)
{
    HugeN temp;
    temp.x[0]=x[0]>other.x[0] ? x[0] : other.x[0];
    int tr=0, aux;
    for(int i=1; i<=temp.x[0]; i++)
    {
        aux=x[i]+other.x[i]+tr;
        temp.x[i]=aux%BASE;
        tr=aux/BASE;
    }
    if(tr)
        temp.x[++temp.x[0]]=tr;
    return temp;
}

HugeN HugeN::operator * (int k)
{
    HugeN temp;
    int tr=0, tr2=0, sth, aux, len=0, ad=1, ok=0;
    while(k)
    {

        len=ad;
        for(int i=1; i<=x[0]; i++)
        {
            aux=x[i]*(k%BASE)+tr;
            tr=aux/BASE;
            sth=temp.x[len]+aux%BASE+tr2;
            tr2=sth/BASE;
            temp.x[len]=sth%BASE;
            len++;
        }
        if(tr)
        {
            temp.x[len]=tr;
            ok=1;
        }
        tr=0;
        ad++;
        k/=BASE;
    }
    if(tr2)
    {
        temp.x[len]+=tr2;
        ok=1;
    }
    if(!ok)
        len--;
    temp.x[0]=len;
    return temp;
}

int main()
{
    //ifstream cin("input.in");
    //ofstream cout("output.out");
    vector< HugeN > dp(1001, HugeN(0));

    dp[1]=2;
    dp[2]=5;
    dp[3]=13;

    for(int i=4; i<=1000; i++)
        dp[i]=dp[i-1]*2+dp[i-2]+dp[i-3];

    int n;
    while(cin>>n)
        dp[n].print();
    return 0;
}
