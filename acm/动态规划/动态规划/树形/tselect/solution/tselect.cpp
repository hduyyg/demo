/*
Prob: tselect
Author: heatdragon
*/

#include <cstdio>
#include <cstring>

const long max = 501;
const long bignum = 1000000000;

struct link
{
       long data, tot;
       link *next;
};

long n, m;
long i, j, k;
link *p;
link *way[max];
long father[max], val[max];
long f[max][max][2][2];//本身是否取，父亲是否取 

void work(link *node, long deg, long deep)//当前结点，父亲权值 ，深度 
{
     long root = node->data;
     long bigl0, bigl1, bigr0, bigr1;
     link *p, *q;
     long s = 0;
     long i, j;
     
     p = way[root];
     if (p->next != NULL)
     {
        s++;
        work(p, val[root], deep+1);
     }
     
     if (node->next != NULL)
        q = node->next;
     if (q->next != NULL)
     {
        s++;
        work(q, deg, deep);
     }
     
     if (s == 0)
     {
        f[root][0][0][0] = 0;
        f[root][0][1][0] = val[root];
        if (deep > 0)
        {
           f[root][0][0][1] = deg;
           f[root][1][1][1] = deg + val[root];
           f[root][0][1][1] = deg + val[root];
        }
        return;
     }
     
     node->tot += p->tot + q->tot;
     for (i = 0; i <= node->tot; i++)
         for (j = 0; j <= i; j++)
         {
             bigl0 = f[p->data][j][0][0];
             if (bigl0 < f[p->data][j][1][0])
                bigl0 = f[p->data][j][1][0];
             bigl1 = f[p->data][j][0][1];
             if (bigl1 < f[p->data][j][1][1])
                bigl1 = f[p->data][j][1][1];
             if (p->data == 0 && j == 0)//&& val[root] > bigl1 && j == 0)
                bigl1 = val[root];
                
             bigr0 = f[q->data][i - j][0][0];
             if (bigr0 < f[q->data][i - j][1][0])
                bigr0 = f[q->data][i - j][1][0];
             bigr1 = f[q->data][i - j][0][1];
             if (bigr1 < f[q->data][i - j][1][1])
                bigr1 = f[q->data][i - j][1][1];
             if (q->data == 0 && i - j == 0)//&& deg > bigr1 && i - j == 0)
                bigr1 = deg;
                
             if (f[root][i][0][0] < bigl0 + bigr0)
                f[root][i][0][0] = bigl0 + bigr0;
             if (f[root][i][0][1] < bigl0 + bigr1)
                f[root][i][0][1] = bigl0 + bigr1;
             if (f[root][i][1][0] < bigl1 + bigr0)
                f[root][i][1][0] = bigl1 + bigr0;
             if (i > j && deep > 0)
             {
                bigr1 = f[q->data][i - j - 1][0][1];
                if (bigr1 < f[q->data][i - j - 1][1][1])
                   bigr1 = f[q->data][i - j - 1][1][1];
                if (q->data == 0 && i - j - 1 == 0)//&& deg > bigr1 && i - j - 1 == 0)
                   bigr1 = deg;
                if (f[root][i][1][1] < bigl1 + bigr1)
                   f[root][i][1][1] = bigl1 + bigr1;
             }
         }
}

int main()
{
    freopen("tselect.in", "r", stdin);
    freopen("tselect.out", "w", stdout);
    
    scanf("%d %d\n", &n, &m);
    for (i = 0; i <= n; i++)
    {
        way[i] = new link;
        way[i]->next = NULL;
        way[i]->data = 0;
        way[i]->tot = 0;
    }
    memset(father, 0, sizeof father);
    memset(val, 0, sizeof val);
    for (i = 1; i <= n; i++)
    {
        scanf("%d %d\n", &val[i], &father[i]);
        p = new link;
        p->data = i;
        p->tot = 1;
        p->next = way[father[i]];
        way[father[i]] = p;
    }
    
    fclose(stdin);
    
    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            for (k = 0; k < 2; k++)
            {
                f[i][j][k][0] = -bignum;
                f[i][j][k][1] = -bignum;
            }
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            f[0][0][i][j] = 0;
    work(way[0], 0, 0);
    
/*    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
            printf("%d %d %d %d\n", f[i][j][0][0], f[i][j][0][1], f[i][j][1][0], f[i][j][1][1]);
        printf("\n\n");
    }*/
    
    for (i = n - 1; i >= 0; i--)
        if (f[way[0]->data][i][0][0] >= m || f[way[0]->data][i][1][0] >= m)
        {
           printf("%d\n", i);
           fclose(stdout);
           return 0;
        }
    printf("%d\n", -1);
    
    fclose(stdout);
    return 0;
}
