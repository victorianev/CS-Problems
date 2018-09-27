#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int d[505][505];
int main()
{
    //ifstream cin("input.txt");
    string line1;
    string line2;
    int cases=0;
    while(getline(cin, line1))
    {
        cout << std::setw(2) << std::setiosflags(std::ios::right) << ++cases<<". ";

        getline(cin, line2);
        if(!line1.length() || !line2.length())
        {
            cout<<"Blank!\n";
            continue;
        }

        for(int i=0; i<line1.size(); i++)
            if(!isdigit(line1[i]) && !isupper(line1[i]) && !islower(line1[i]))
                line1[i]=' ';

        for(int i=0; i<line2.size(); i++)
            if(!isdigit(line2[i]) && !isupper(line2[i]) && !islower(line2[i]))
                line2[i]=' ';

        stringstream scin(line1);
        string word;
        vector<string> data1(1);
        while(scin>>word)
            data1.push_back(word);

        stringstream sscin(line2);
        vector<string> data2(1);
        while(sscin>>word)
            data2.push_back(word);
        int n=data1.size();
        int m=data2.size();
        for(int i=1; i<n; i++)
            for(int j=1; j<m; j++)
                if(data1[i]==data2[j])
                    d[i][j]=d[i-1][j-1]+1;
                else  if(d[i-1][j]>=d[i][j-1])
                    d[i][j]=d[i-1][j];
                else
                    d[i][j]=d[i][j-1];

        cout<<"Length of longest match: "<<d[n - 1][m - 1]<<'\n';
    }
    return 0;
}
