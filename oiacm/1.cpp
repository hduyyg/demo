#include<cstdio>
#include<algorithm>
using namespace std;

long long f[20+5][20+5];
int n, m, horse_x, horse_y; 

bool ok(int x, int y) {
	if (x > n || y > m) return 0;
	if (x == horse_x && y == horse_y) return 0; 
	if (abs(horse_x - x) == 1 && abs(horse_y - y) == 2) return 0;
	if (abs(horse_x - x) == 2 && abs(horse_y - y) == 1) return 0;
	return 1;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &horse_x, &horse_y);
	f[0][0] = 1;
	for(int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			if (ok(i, j)) {
				if (j > 0) f[i][j] += f[i][j - 1];
				if (i > 0) f[i][j] += f[i - 1][j];
			}
		}
	printf("%I64d\n",f[n][m]);   
	return 0;
}
