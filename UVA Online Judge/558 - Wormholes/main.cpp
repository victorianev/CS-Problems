#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int NMAX = 1001, INF = 1 << 20;

typedef vector<int> vec;
typedef vector<vec> matr;

matr g, w;
int nrn, nrm, s, q, tests;
vec d;

void init() {
    d = vec(nrn, INF);
    d[s] = 0;
}

void relax (const int &u, const int&v) {
    if (d[v] > d[u] + w[u][v])
        d[v] = d[u] + w[u][v];
}

bool bellmanford() {
    init();
    for (int cnt = 0; cnt < nrn - 1; cnt++) {
        for (int i = 0; i < nrn; i++) {
            for (int j = 0, u, v; j < g[i].size(); j++) {
                u = i, v = g[i][j];
                relax(u, v);
            }
        }
    }
    for (int i = 0; i < nrn; i++) {
        for (int j = 0, u, v; j < g[i].size(); j++) {
            u = i, v = g[i][j];
            if (d[v] > d[u] + w[u][v])
                return false;
        }
    }
    return true;
}

int main() {
    //ifstream cin("dat.in");
    //ofstream cout("dat.out");
    cin>>tests;
    for (q=1; q<=tests; q++){
    cin >> nrn >> nrm;
    s=0;
    g = matr(nrn, vec());
    w = matr(nrn, vec(nrn, -1));
    for (int i = 0; i < nrm; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(b);
        w[a][b] = c;
    }
    if (!bellmanford())
        cout << "possible"<<'\n';
    else
            cout << "not possible"<< '\n';
    }
    return 0;
}


