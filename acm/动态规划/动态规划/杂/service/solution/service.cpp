#include <cstdio>
#include <cstring>
#include <cstdlib>

const long maxn = 501;
const long maxlongint = 2147483647;

long n, m;
long i, j, k;
long data[maxn][3];//村庄位置，人口数，建站费用 
long min[maxn][maxn], f[maxn][maxn], tot[maxn];//min: 在区间i~j设一个站，最少要多少钱；f：在前i个村设j个站，最少需要多少钱 
long pos, best, cur, next, help, ans = maxlongint;//pos: 当前站的位置；best: 最少花费；cur: 目前花费变更值 

int main()
{
    freopen("service.in", "r", stdin);
    freopen("service.out", "w", stdout);
    
    memset(tot, 0, sizeof tot);
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i ++)
    {
        scanf("%d %d %d", &data[i][0], &data[i][1], &data[i][2]);
        tot[i] = tot[i - 1] + data[i][1];
    }
    
    for (i = 1; i <= n; i ++)
    {
        min[i][i] = data[i][2];
        pos = i;
        best = data[i][2];
        for (j = i + 1; j <= n; j ++)
        {
            best += data[j][1] * (data[j][0] - data[pos][0]);
            next = maxlongint;
            cur = 0;
            for (k = pos + 1; k <= j; k ++)
            {
                cur += ((tot[k - 1] << 1) - tot[i - 1] - tot[j]) * (data[k][0] - data[k - 1][0]) - data[k - 1][2] + data[k][2];
                if (cur < next)
                {
                   next = cur;
                   help = k;
                }
            }
            if (next < 0)
            {
               best += next;
               pos = help;
            }
            min[i][j] = best;
        }
    }
    
    memset(f, 0, sizeof f);
    for (i = 1; i <= n; i ++)
    {
        f[i][1] = min[1][i];
        for (j = 2; j <= (m <? i); j ++)
        {
            f[i][j] = f[i - 1][j - 1] + min[i][i];
            for (k = i - 2; k >= j - 1; k --)
                if (f[i][j] > f[k][j - 1] + min[k + 1][i])
                   f[i][j] = f[k][j - 1] + min[k + 1][i];
        }
    }
        
    for (i = 1; i <= m; i ++)
        if (f[n][i] < ans)
           ans = f[n][i];
           
    printf("%d\n", ans);
    
    return 0;
}
