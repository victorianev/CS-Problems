#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
bool is;
long long tests, i, r1, r2, r3, r4, da, db, dc, dd;
struct sth
{
    long x;
    long y;
} a, b, c, d, v1, v2, v3, v4;
long long crossed_prod(sth a,sth b)
{
    return a.x*b.y-a.y*b.x;
}
long long points_prod(sth a,sth b)
{
    return a.x*b.x+a.y*b.y;
}
long long dist(sth a)
{
    return a.x*a.x+a.y*a.y;
}
int main()
{
   // ifstream cin("date.in");
   // ofstream cout("date.out");
    cin>>tests;
    for(i=1; i<=tests; i++)
    {   is=0;vector <sth> points;
        cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>d.x>>d.y;
        int v[]= {1,2,3};
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);
        do
        {
            v1.x=points[v[0]].x-a.x;
            v1.y=points[v[0]].y-a.y;

            v2.x=points[v[1]].x-points[v[0]].x;
            v2.y=points[v[1]].y-points[v[0]].y;

            v3.x=points[v[2]].x-points[v[1]].x;
            v3.y=points[v[2]].y-points[v[1]].y;

            v4.x=a.x-points[v[2]].x;
            v4.y=a.y-points[v[2]].y;

            r1=crossed_prod(v1,v2);
            r2=crossed_prod(v2,v3);
            r3=crossed_prod(v3,v4);
            r4=crossed_prod(v4,v1);

            if((r1>0&&r2>0&&r3>0&&r4>0)||(r1<0&&r2<0&&r3<0&&r4<0))
                is=1;
            else is=0;
        }
        while(!is&&next_permutation(v,v+3));
        da=dist(v1);
        db=dist(v2);
        dc=dist(v3);
        dd=dist(v4);
        if(points_prod(v1,v2)==0&&points_prod(v2,v3)==0&&points_prod(v3,v4)==0&&points_prod(v4,v1)==0)
        {
            if(da==db&&db==dc&&dc==dd)
                cout<<"Case "<<i<<": Square\n";
            else
                cout<<"Case "<<i<<": Rectangle\n";
        }
        else
        {
            if(da==db&&db==dc&&dc==dd)
                cout<<"Case "<<i<<": Rhombus\n";
            else
            {
                if(da==dc&&db==dd)
                    cout<<"Case "<<i<<": Parallelogram\n";
                else
                {
                    if(crossed_prod(v1,v3)==0||crossed_prod(v2,v4)==0)
                        cout<<"Case "<<i<<": Trapezium\n";
                    else
                        cout<<"Case "<<i<<": Ordinary Quadrilateral\n";
                }
            }
        }
    }
    return 0;
}
