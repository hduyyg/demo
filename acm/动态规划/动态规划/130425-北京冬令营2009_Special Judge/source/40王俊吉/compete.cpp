#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

const char fi[] = "compete.in";
const char fo[] = "compete.out";
const int maxN = 30;

int a[maxN], b[maxN], c[maxN];
bool tag[maxN];
int n, L;
double ans = 0;

void init_file()
{
    freopen(fi, "r", stdin);
    freopen(fo, "w", stdout);
    return;
}

void readdata()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < n; ++i)
        scanf("%d", b + i);
    scanf("%d", &L);
    return;
}

void print()
{
    double tmp = 0;
    for (int i = 0; i < n; ++i)
        tmp += 1. / (1 + pow(10., (b[i] - c[i]) / 400.));
    if (tmp > ans) ans = tmp;

#ifdef Debug
    for (int i = 0; i < n; ++i)
        printf("%d ", c[i]);
    printf("\n");
#endif

    return;
}

void Dfs(int i)
{
    if (i >= n) {print(); return;}
    for (int j = 0; j < n; ++j)
    {
        if (tag[j]) continue;
        if (a[j] - L > c[i - 1]) break;
        c[i] = a[j]; tag[j] = 1;
        Dfs(i + 1); tag[j] = 0;
    }
    return;
}

inline bool cmp(const int &a, const int &b)
{return a > b;}

void work()
{
    std::sort(a, a + n, cmp);
    for (int i = 0; i < n; ++i)
    if (a[0] - a[i] <= L)
    {
        c[0] = a[i];
        tag[i] = 1;
        Dfs(1);
        tag[i] = 0;
    }
    printf("%.6lf\n", ans);
    return;
}

int main()
{
    init_file();
    readdata();
    work();
    return 0;
}
