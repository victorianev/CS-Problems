#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char s[20], c;
    cin>>s;
    int n=strlen(s);
    long long sol, nr=0;
    for(int i=0; i<n-1; i++)
        nr=nr*10+s[i]-'0';
    c=s[n-1];

    if(nr%4==3 || nr%4==0)
        nr-=2;

    nr--;
    sol=nr/4*12;
    if(nr%4==1 || nr%4==2)
        sol+=6;
    sol+=nr;

    if(c=='a')
        sol+=4;
    else if(c=='b')
        sol+=5;
    else if(c=='c')
        sol+=6;
    else if(c=='d')
        sol+=3;
    else if(c=='e')
        sol+=2;
    else if(c=='f')
        sol+=1;

    cout<<sol<<'\n';
    return 0;
}
