#include <iostream>
#include <fstream>
using namespace std;
struct point
{
    double x, y;
} p1, p2, p3, mid12, mid23, mid13;
double x, y;
int main()
{
    //ifstream cin("input.in");
    //ofstream cout("output.out");
    cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y;
    cout<<3<<'\n';
    mid12.x=(p1.x+p2.x)/2;
    mid12.y=(p1.y+p2.y)/2;
    x=2*mid12.x-p3.x;
    y=2*mid12.y-p3.y;
    cout<<x<<' '<<y<<'\n';

    mid13.x=(p1.x+p3.x)/2;
    mid13.y=(p1.y+p3.y)/2;
    x=2*mid13.x-p2.x;
    y=2*mid13.y-p2.y;
    cout<<x<<' '<<y<<'\n';

    mid23.x=(p2.x+p3.x)/2;
    mid23.y=(p2.y+p3.y)/2;
    x=2*mid23.x-p1.x;
    y=2*mid23.y-p1.y;
    cout<<x<<' '<<y<<'\n';

    return 0;
}
