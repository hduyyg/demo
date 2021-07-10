#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 10002;
const long maxval = 10;
const long maxlongint = 2147483647;

long n, m;
long i, j;
long edge[maxn << 1][2], pos[maxn];
long min[maxn][maxval], ok[maxn];
long ans = maxlongint;

void sort(long l, long r)
{
     long i, j;
     long x, t;
     
     i = l;
     j = r;
     x = edge[(i + j) >> 1][0];
     while (i < j)
     {
           while (edge[i][0] < x)
                 i ++;
           while (edge[j][0] > x)
                 j --;
           if (i <= j)
           {
                 t = edge[i][0];
                 edge[i][0] = edge[j][0];
                 edge[j][0] = t;
                 t = edge[i][1];
                 edge[i][1] = edge[j][1];
                 edge[j][1] = t;
                 i ++;
                 j --;
           }
     }
     if (i < r)
        sort(i, r);
     if (l < j)
        sort(l, j);
}

void dfs(long root)
{
     long i, j, k;
     long next, cur;
     
     ok[root] = 1;
     for (i = 1; i < maxval; i ++)
         min[root][i] = i;
     for (i = pos[root]; i < pos[root + 1]; i ++)
         if (ok[edge[i][1]] == 0)
         {
            next = edge[i][1];
            dfs(next);
            for (j = 1; j < maxval; j ++)
            {
                cur = maxlongint;
                for (k = 1; k < maxval; k ++)
                    if (j != k && cur > min[next][k])
                       cur = min[next][k];
                min[root][j] += cur;
            }
         }
}

int main()
{
    freopen("gems.in", "r", stdin);
    freopen("gems.out", "w", stdout);
    
    scanf("%d", &n);
    m = 0;
    for (i = 1; i < n; i ++)
    {
        m ++;
        scanf("%d %d", &edge[m][0], &edge[m][1]);
        m ++;
        edge[m][0] = edge[m - 1][1];
        edge[m][1] = edge[m - 1][0];
    }
    sort(1, m);
    pos[1] = 1;
    for (i = 2; i <= m; i ++)
        if (edge[i][0] > edge[i - 1][0])
           pos[edge[i][0]] = i;
    pos[n + 1] = m + 1;
/*    for (i = m; i > 0; i --)
        if (pos[i] == 0)
           pos[i] = pos[i + 1];*/
           
    memset(ok, 0, sizeof ok);
    dfs(1);
    
    for (i = 1; i < maxval; i ++)
        if (ans > min[1][i])
           ans = min[1][i];
           
    printf("%d\n", ans);
    
    return 0;
}
