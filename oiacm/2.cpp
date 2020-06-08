#include <bits/stdc++.h>
using namespace std;
#define f(q, w) for (int q = 0; q <w; ++q)
int b[2], m[2];//B和马的坐标
long long mem[25][25] = { 1 };//记忆化数组
int e[9][2] = { 0,0, -2,-1, -1,-2, 1,2, 2,1 ,1,-2, -2,1, -1,2, 2,-1 };
//马的控制范围
inline bool check(int x, int y) {//检查是否被控制
    f(i, 9)
        if (x + e[i][0] == m[0] && y + e[i][1] == m[1])
            return false;
    return true;
}
inline long long dp(int x, int y) {//后来才发现写的其实是递归hhh
    if (mem[x][y])return mem[x][y];
	if (x && !mem[x - 1][y]) {
        mem[x - 1][y] = check(x - 1, y) ? dp(x - 1, y) : 0;
	} 
    if (y && !mem[x][y - 1]) {
        mem[x][y - 1] = check(x, y - 1) ? dp(x, y - 1) : 0;
	}
	
	if (x) mem[x][y] += mem[x - 1][y]; 
	if (y) mem[x][y] += mem[x][y - 1];         
    return mem[x][y];
}

int main(void) {
    cin >> b[0] >> b[1] >> m[0] >> m[1];
    if (check(b[0], b[1]) && check(0, 0))
        cout << dp(b[0], b[1]);
    else cout << "0";//判断起点终点是否被控制
//    cout << endl;
//    f(i, 21) {
//        f(in, 21) {
//            printf("%d\t", mem[i][in]);
//        }
//        cout << endl;
//    }
    return 0;
}
