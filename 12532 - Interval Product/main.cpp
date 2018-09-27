#include <iostream>
#include <fstream>
using namespace std;
const int NMAX=1000000, NMAX2=100000;
char s[5];
int n, k, x[NMAX], arbint[4*NMAX2+100], i, elem, val, st, en;
void build(int nod,int l,int r)
{
    if(l==r)
    {
        arbint[nod]=x[l];
        return;
    }
    int mid=(l+r)/2;
    build(2*nod,l,mid);
    build(2*nod+1,mid+1,r);
    arbint[nod]=arbint[2*nod]*arbint[2*nod+1];
}
void update(int nod,int elem,int val,int l,int r)
{
    if(elem<l||elem>r) return;
    if(l==r)
    {
        arbint[nod]=val;
        return;
    }
    int mid=(l+r)/2;
    update(2*nod,elem,val,l,mid);
    update(2*nod+1,elem,val,mid+1,r);
    arbint[nod]=arbint[2*nod]*arbint[2*nod+1];
}
int query(int nod,int l,int r,int st,int en)
{
    if(st>r||en<l)return 1;
    if(l>=st&&r<=en)return arbint[nod];
    int mid=(l+r)/2;
    return query(2*nod,l,mid,st,en)*query(2*nod+1,mid+1,r,st,en);

}
int main()
{
    //ifstream cin("date.in");
    while(cin>>n>>k)
    {
        for(i=1; i<=n; i++)
        {
            cin>>x[i];
            if(x[i]>1)x[i]=1;
            if(x[i]<-1)x[i]=-1;
        }
        build(1,1,n);
        while(k--)
        {
            cin>>s;
            if(s[0]=='C')
            {
                cin>>elem>>val;
                if(val>1)val=1;
                if(val<-1)val=-1;
                update(1,elem,val,1,n);
                x[elem]=val;
            }
            else
            {
                cin>>st>>en;
                //st--;en--;
                int sol=query(1,1,n,st,en);

                if(sol==-1)cout<<'-';
                else if(sol==1)cout<<'+';
                else cout<<0;
            }

        }
        cout<<'\n';
    }
    return 0;
}
