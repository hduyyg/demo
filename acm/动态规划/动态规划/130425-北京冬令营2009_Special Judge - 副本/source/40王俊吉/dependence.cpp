#include <cstdio>
#include <cstdlib>
#include <algorithm>

const char fi[] = "dependence.in";
const char fo[] = "dependence.out";
const int maxN = 20;

char str[maxN << 1];
bool tag[1 << 10];
int a[1 << 10], b[1 << 10], n, m;

void init_file()
{
    freopen(fi, "r", stdin);
    freopen(fo, "w", stdout);
    return;
}

void readdata()
{
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        gets(str); int j;
        for (j = 0; str[j] != '-'; ++j)
            b[i] = a[i] |= 1 << (n - str[j] + 'A' - 1);
        for (++++j; str[j]; ++j)
            b[i] |= 1 << (n - str[j] + 'A' - 1);
    }
    return;
}

inline bool check(int x)
{
    int tmp = x;
    while (tmp < (1 << n) - 1)
    {
        bool flag = 0;
        for (int i = 0; i < m; ++i)
        if (((a[i] | tmp) == tmp)
            && ((b[i] | tmp) > tmp))
        {tmp |= b[i]; flag = 1;}
        //if (tmp != x) tag[tmp] = 0;
        if (!flag) break;
    }
    if (tmp == (1 << n) - 1)
    for (int i = 1; i < 1 << n; ++i)
        tag[x | i] = 0;
    return tmp == (1 << n) - 1;
}

void work()
{
    for (int i = 1; i < 1 << n; ++i)
        tag[i] = 1;
    for (int i = 1; i < 1 << n; ++i)
        if (tag[i]) tag[i] &= check(i);
    int cnt = 0;
    for (int i = 1; i < 1 << n; ++i)
        cnt += tag[i];
    if (!cnt) {printf("No candidate key\n"); return;}
    printf("%d\n", cnt);
    for (int i = 1; i < 1 << n; ++i)
    if (tag[i])
    {
        for (int tmp = i, j = 0; tmp; tmp >>= 1, ++j)
            if (tmp & 1) printf("%c", (n - j + 'A' - 1));
        printf("\n");
    }

#ifdef Debug
    for (int i = 0; i < m; ++i)
        printf("%03X -> %03X\n", a[i], b[i]);
#endif

    return;
}

int main()
{
    init_file();
    readdata();
    work();
    return 0;
}
