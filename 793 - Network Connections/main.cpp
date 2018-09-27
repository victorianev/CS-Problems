#include <iostream>
#include <cstdio>
int parent[1005];
int find_parent(int x)
{
    if(x==parent[x])
        return x;
    return find_parent(parent[x]);
}

int isUnion(int a, int b)
{
    return find_parent(a)==find_parent(b);
}

void makeUnion(int a, int b)
{
    parent[find_parent(a)]=find_parent(b);
}
int main()
{
    int c, c1, c2, nr;
    int i, success, fail;
    char o, buffer[100];
    scanf("%d", &c);
    while(c--)
    {
        success=fail=0;
        scanf("%d", &nr);
        getchar();
        for(int i=1; i<=nr; i++)
            parent[i]=i;
        o=getchar();
        while(o!='\n' && o!=EOF)
        {
            gets(buffer);
            sscanf(buffer, "%d %d", &c1, &c2);
            if(o=='q')
            {
                if(isUnion(c1, c2))
                    success++;
                else fail++;
            }
            else makeUnion(c1, c2);
            o=getchar();
        }
        printf("%d,%d\n", success, fail);
        if(c)
            putchar('\n');
    }
    return 0;
}
