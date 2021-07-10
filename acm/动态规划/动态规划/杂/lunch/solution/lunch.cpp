#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 201;
const long maxlongint = 2147483647 >> 1;

long n;
long data[maxn][2], tot[maxn];
long f[maxn][maxn * maxn];
long i, j;
long t, min, ans = maxlongint;

int main()
{
    freopen("lunch.in", "r", stdin);
    freopen("lunch.out", "w", stdout);
    
    scanf("%d", &n);
    for (i = 1; i <= n; i ++)
        scanf("%d %d", &data[i][0], &data[i][1]);
        
    for (i = 1; i < n; i ++)
        for (j = i + 1; j <= n; j ++)
            if (data[i][1] < data[j][1])
            {
               t = data[i][0];
               data[i][0] = data[j][0];
               data[j][0] = t;
               t = data[i][1];
               data[i][1] = data[j][1];
               data[j][1] = t;
            }
    memset(tot, 0, sizeof tot);
    for (i = 1; i <= n; i ++)
        tot[i] = tot[i - 1] + data[i][0];
            
    for (i = 0; i <= n; i ++)
        for (j = 0; j <= tot[n]; j ++)
            f[i][j] = maxlongint;
    f[0][0] = 0;
    for (i = 1; i <= n; i ++)
        for (j = 0; j <= tot[i]; j ++)
        {
            min = maxlongint;
            if (j <= tot[i - 1])
               min = min <? f[i - 1][j] >? (tot[i] - j + data[i][1]);
            if (j >= data[i][0])
               min = min <? (f[i - 1][j - data[i][0]] >? (j + data[i][1]));
            if (i == n && ans > (min >? j))
               ans = min >? j;
            f[i][j] = min;
        }
        
    printf("%d\n", ans);
/*    for (i = 1; i <= n; i ++)
    {
        for (j = 0; j <= tot[i]; j ++)
            printf("%d ", f[i][j]);
        printf("\n");
    }*/
    
    return 0;
} 
