/*
Prob: network
Author: heatdragon
*/

#include <cstdio>
#include <cstring>

const long maxn = 101;

struct link
{
       long data;
       link *next;
       long val[maxn][2];
};

long n, m, time;
long i, j;
long f[maxn][maxn * maxn][2], s[maxn], ok[maxn];
long a, b, root, big = 0;
link *p, *q, *way[maxn];

void getcon(long a, long b, link *now)
{
     long i, j, k, tot, flag;
     long help[maxn * maxn][2], cur[maxn* maxn][2], ans[maxn* maxn][2];
     
/*     if (s[a] == 0)
     {
        s[b] = 0;
        return;
     }
     
/*     printf("a %d %d\n", a, b);
     for (i = 1; i <= s[a]; i++)
         printf("%d %d ", f[a][i][0], f[a][i][1]);
     printf("\n\n");
     for (i = 1; i <= now->val[0][0]; i++)
         printf("%d %d ", now->val[i][0], now->val[i][1]);*/
     
     for (i = 1; i <= s[a]; i++)
     {
         cur[i][0] = f[a][i][0] + now->val[1][0];
         cur[i][1] = f[a][i][1] + now->val[1][1];
     }
     cur[0][0] = s[a];
     for (i = 2; i <= now->val[0][0]; i++)
     {
         for (j = 1; j <= s[a]; j++)
         {
             help[j][0] = f[a][j][0] + now->val[i][0];
             help[j][1] = f[a][j][1] + now->val[i][1];
         }
         tot = 0;
         j = 1;
         k = 1;
         while (j <= cur[0][0] || k <= s[a])
         {
               flag = 0;
               tot++;
               if ((k > s[a]) || (j <= cur[0][0] && cur[j][0] >= help[k][0]))
               {
                  ans[tot][0] = cur[j][0];
                  ans[tot][1] = cur[j][1];
                  j++;
                  flag = 1;
               }
               if (((j > cur[0][0]) || (k <= s[a] && help[k][0] > cur[j][0])) && flag == 0)
               {
                  ans[tot][0] = help[k][0];
                  ans[tot][1] = help[k][1];
                  k++;
               }
               
               while (tot > 1 && ans[tot][1] <= ans[tot-1][1])
               {
                     ans[tot-1][0] = ans[tot][0];
                     ans[tot-1][1] = ans[tot][1];
                     tot--;
               }
               if (tot > 1 && ans[tot][0] == ans[tot-1][0])
                  tot--;
         }
         
         cur[0][0] = tot;
         for (j = 1; j <= tot; j++)
         {
             cur[j][0] = ans[j][0];
             cur[j][1] = ans[j][1];
         }
     }
     
     s[b] = 0;
     for (i = 1; i <= cur[0][0]; i++)
         if (cur[i][0] <= time)
         {
            s[b]++;
            f[b][s[b]][0] = cur[i][0];
            f[b][s[b]][1] = cur[i][1];
         }
/*     printf("\n\n");
     for (i = 1; i <= s[b]; i++)
         printf("%d %d ", f[b][i][0], f[b][i][1]);
     printf("\n\n\n");*/
}

void combine(long a, long b)
{
     long i, j, k, tot, flag, all;
     long help[maxn * maxn][2], cur[maxn* maxn][2], ans[maxn * maxn][2];

     if (s[a] == 0 || s[b] == 0)
     {
        s[a] = 0;
//        printf("hahahoho %d %d\n", a, b);
        return;
     }    
     
/*     printf("b %d %d\n", a, b);
     for (i = 1; i <= s[a]; i++)
         printf("%d %d ", f[a][i][0], f[a][i][1]);
     printf("\n\n");
     for (i = 1; i <= s[b]; i++)
         printf("%d %d ", f[b][i][0], f[b][i][1]);*/
         
     cur[0][0] = 0;     
     for (i = 1; i <= s[a]; i++)
         if (f[a][i][0] + f[b][1][0] <= time)
         {
            cur[0][0]++;
            cur[cur[0][0]][0] = f[a][i][0];
            if (f[a][i][0] < f[b][1][0])
               cur[cur[0][0]][0] = f[b][1][0];
            cur[cur[0][0]][1] = f[a][i][1] + f[b][1][1];
         }             
     
     for (i = 2; i <= s[b]; i++)
     {
         all = 0;
         for (j = 1; j <= s[a]; j++)
             if (f[a][j][0] + f[b][i][0] <= time)
             {
                all++;
                help[all][0] = f[a][j][0];
                if (f[a][j][0] < f[b][i][0])
                   help[all][0] = f[b][i][0];
                help[all][1] = f[a][j][1] + f[b][i][1];
             }
         tot = 0;
         j = 1;
         k = 1;
         while (j <= cur[0][0] || k <= all)
         {
               flag = 0;
               tot++;
               if ((k > all) || (j <= cur[0][0] && cur[j][0] >= help[k][0]))
               {
                  ans[tot][0] = cur[j][0];
                  ans[tot][1] = cur[j][1];
                  j++;
                  flag = 1;
               }
               if (((j > cur[0][0]) || (k <= s[a] && help[k][0] > cur[j][0])) && flag == 0)
               {
                  ans[tot][0] = help[k][0];
                  ans[tot][1] = help[k][1];
                  k++;
               }
               
               while (tot > 1 && ans[tot][1] <= ans[tot-1][1])
               {
                     ans[tot-1][0] = ans[tot][0];
                     ans[tot-1][1] = ans[tot][1];
                     tot--;
               }
               while (tot > 1 && ans[tot][0] == ans[tot-1][0])
                  tot--;
         }
         
         cur[0][0] = tot;
         for (j = 1; j <= tot; j++)
         {
             cur[j][0] = ans[j][0];
             cur[j][1] = ans[j][1];
         }
     }
     s[a] = 0;
     for (i = 1; i <= cur[0][0]; i++)
         if (cur[i][0] <= time && (i == 1 || cur[i][0] != cur[i-1][0]))
         {
            s[a]++;
            f[a][s[a]][0] = cur[i][0];
            f[a][s[a]][1] = cur[i][1];
         }
/*     printf("\n\n");
     for (i = 1; i <= s[a]; i++)
         printf("%d %d ", f[a][i][0], f[a][i][1]);
     printf("\n\n\n");*/
}

void work(link *node)
{
     long i, j;
     long root, sum = 0;
     link *p, *q;
     
     root = node->data;
     ok[root] = 1;
     
     p = way[0];
     if (way[root]->next != NULL && ok[way[root]->data] == 0)
     {
        sum++;
        p = way[root];
        work(p);
     }
     
     q = way[0];
     if (node->next->next != NULL && ok[node->next->data] == 0)
     {
        sum++;
        q = node->next;
        work(q);
     }
     
     if (sum == 0 || p->data == 0)
     {
        s[root] = node->val[0][0];
        for (i = 1; i <= s[root]; i++)
        {
            f[root][i][0] = node->val[i][0];
            f[root][i][1] = node->val[i][1];
        }
        if (sum == 0)
           return;
     }
     
     if (p->data > 0)
        getcon(p->data, root, node);
        
     if (q->data > 0)
        combine(root, q->data);
}

int main()
{
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    
    scanf("%d %d\n", &n, &time);
    for (i = 0; i <= n; i++)
    {
        way[i] = new link;
        way[i]->data = 0;
        way[i]->next = NULL;
    }
    for (i = 1; i < n; i++)
    {
        scanf("%d %d %d", &a, &b, &m);
        
        p = new link;
        p->data = b;
        p->val[0][0] = m;
        for (j = 1; j <= m; j++)
            scanf("%d %d", &p->val[j][0], &p->val[j][1]);
        p->next = way[a];
        way[a] = p;
        
        q = new link;
        q->data = a;
        q->val[0][0] = m;
        for (j = 1; j <= m; j++)
        {
            q->val[j][0] = p->val[j][0];
            q->val[j][1] = p->val[j][1];
        }
        q->next = way[b];
        way[b] = q;
    }
    
    fclose(stdin);
    
    memset(ok, 0, sizeof ok);
    ok[1] = 1;
    memset(s, 0, sizeof s);
    work(way[1]);
     
/*    for (i = 1; i <= n; i++)
    {
        printf("%d\n", i);
        p = way[i];
        while (p->next != NULL)
        {
              printf("%d ", p->data);
              p = p->next;
        }
        printf("\n");
    }
        
    for (i = 1; i <= n; i++)
    {
        printf("%d %d\n", i, s[i]);
        for (j = 1; j <= s[i]; j++)
            printf("%d %d ", f[i][j][0], f[i][j][1]);
        printf("\n");
    }*/
    
    root = way[1]->data;
//    printf("%d\n", root);
    if (s[root] == 0 || f[root][s[root]][0] > time)
    {
       printf("-1");
       fclose(stdout);
       return 0;
    }
    i = s[root];
    while (i > 1 && f[root][i-1][0] <= time)
          i--;
    printf("%d\n", f[root][i][1]);
    
    fclose(stdout);
    return 0;
}
