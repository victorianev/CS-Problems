#include <cstdio>
using namespace std;
const int NMAX=21;
FILE *in, *out;
int vis[NMAX][NMAX], n, m, nr;
char a[NMAX][NMAX], land;

int fill(int x, int y)
{
    if(y==m)y=0;
    else if(y==-1)y=m-1;
    if(x<0||x>=n||y<0||y>=m)
        return 0;
    if(vis[x][y])
        return 0;
    if(a[x][y]!=land)return 0;
    vis[x][y]=1;
    nr++;
    fill(x+1, y);
    fill(x-1, y);
    fill(x, y+1);
    fill(x, y-1);
    return nr;
}

int main()
{
    //freopen("input.in", "r",  stdin);
    //freopen("output.out", "w", stdout);
    int i, j, maxim, x, y, ans;
    while(scanf("%d %d", &n, &m)==2)
    {
        getchar();
        for(i=0; i<n; i++)
        {
            for(j=0; j<m; j++)
            {
                a[i][j]=getchar();
                vis[i][j]=0;
            }
            getchar();
        }
        scanf("%d %d", &x, &y);
        land=a[x][y];
        fill(x, y);
        maxim=-1;
        for(i=0; i<n; i++)
            for(j=0; j<m; j++)
                if(a[i][j]==land&&!vis[i][j])
                {nr=0;
                    ans=fill(i, j);
                    if(ans>maxim)
                        maxim=ans;
                }
        if(maxim==-1) printf("0\n");else
        printf("%d\n", maxim);

    }
    return 0;
}
