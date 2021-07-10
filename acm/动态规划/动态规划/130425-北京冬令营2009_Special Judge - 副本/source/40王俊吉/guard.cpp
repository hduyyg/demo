#include <cstdio>
#include <cstdlib>
#include <algorithm>

const char fi[] = "guard.in";
const char fo[] = "guard.out";
const int maxN = 20;

char tmp[maxN][maxN];
int mp[maxN][maxN];
int x[maxN], y[maxN];
int n, m, Sx, Sy, Tx, Ty;

void init_file()
{
    freopen(fi, "r", stdin);
    freopen(fo, "w", stdout);
    return;
}

void readdata()
{
    scanf("%d%d\n", &n, &m);
    for (int i = 1; i < n + 1; ++i)
    {
        gets(tmp[i] + 1);
        for (int j = 1; j < n + 1; ++j)
        switch (tmp[i][j])
        {
        case '.': mp[i][j] = 1; break;
        case 'E':
            mp[i][j] = 1;
            Sx = i; Sy = j;
            break;
        case 'C':
            mp[i][j] = 1;
            Tx = i; Ty = j;
            break;
        case 'X': mp[i][j] = 0; break;
        default:
            mp[i][j] = 1;
            x[tmp[i][j] - '0'] = i;
            y[tmp[i][j] - '0'] = j;
            break;
        }
    }
    for (; m; --m)
    {
        int ID; char dir;
        scanf("%d %c", &ID, &dir);
        int i = x[ID], j = y[ID];
        switch (dir)
        {
        case 'E':
            for (; mp[i][j]; ++j)
                mp[i][j] = -1;
            break;
        case 'W':
            for (; mp[i][j]; --j)
                mp[i][j] = -1;
            break;
        case 'N':
            for (; mp[i][j]; --i)
                mp[i][j] = -1;
            break;
        case 'S':
            for (; mp[i][j]; ++i)
                mp[i][j] = -1;
            break;
        }
    }
    return;
}

void print(int tot)
{
    for (int i = 1; i < tot; ++i)
    {
        if (x[i] + 1 == x[i + 1]
            && y[i] == y[i + 1])
            printf("S\n");
        else if (x[i] - 1 == x[i + 1]
                 && y[i] == y[i + 1])
            printf("N\n");
        else if (x[i] == x[i + 1]
                 && y[i] + 1 == y[i + 1])
            printf("E\n");
        else if (x[i] == x[i + 1]
                 && y[i] - 1 == y[i + 1])
            printf("W\n");
    }
    exit(0);
}

void Dfs(int i, int _x, int _y)
{
    x[i] = _x; y[i] = _y;
    if (_x == Tx && _y == Ty)
    {print(i); return;}
    mp[_x][_y] = 0;
    if (mp[_x][_y + 1] > 0)
        Dfs(i + 1, _x, _y + 1);
    if (mp[_x][_y - 1] > 0)
        Dfs(i + 1, _x, _y - 1);
    if (mp[_x + 1][_y] > 0)
        Dfs(i + 1, _x + 1, _y);
    if (mp[_x - 1][_y] > 0)
        Dfs(i + 1, _x - 1, _y);
    x[i] = y[i] = 0;
    mp[_x][_y] = 1;
    return;
}

void work()
{

#ifdef Debug
    for (int i = 0; i < n + 2; ++i)
    {
        for (int j = 0; j < n + 2; ++j)
            printf("%2d ", mp[i][j]);
        printf("\n");
    }
#endif

    if (mp[Sx][Sy] > 0 && mp[Tx][Ty] > 0)
        Dfs(1, Sx, Sy);
    printf("-1\n");
    return;
}

int main()
{
    init_file();
    readdata();
    work();
    return 0;
}
