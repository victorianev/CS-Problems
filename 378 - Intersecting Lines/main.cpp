#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
const double eps=1.e-14;


int main()
{
    //ifstream cin("input.in");
    //ofstream cout("output.out");
    cout<<"INTERSECTING LINES OUTPUT\n";
    int tests;
    cin>>tests;
    while(tests--)
    {
        double x1, y1, x2, y2, x3, y3, x4, y4, x, y;
        cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
        double a1, a2, b1, b2, c1, c2;
        a1=y1-y2;
        b1=x2-x1;
        c1=x1*y2-x2*y1;
        a2=y3-y4;
        b2=x4-x3;
        c2=x3*y4-x4*y3;
        if(fabs(a1*b2-a2*b1)<eps && fabs(a1*c2-a2*c1)<eps && fabs(b1*c2-b2*c1)<eps)
            cout<<"LINE\n";
        else if(fabs(a1*b2-a2*b1)<eps)
            cout<<"NONE\n";
        else
        {
            x=(-c1*b2+c2*b1)/(a1*b2-a2*b1);
            y=(-a1*c2+a2*c1)/(a1*b2-a2*b1);
            cout<<"POINT "<<setprecision(2)<<fixed<<x<<' '<<y<<'\n';
        }

    }
    cout<<"END OF OUTPUT\n";
    return 0;
}
