#include<cstdio>
#include<algorithm>
using namespace std;

int n, m, horse_x, horse_y; 

int dx[] = {0, -1, -2, -2, -1, 1, 2, 2, 1};
int dy[] = {0, -2, -1, 1, 2, 2, 1, -1, -2};

bool ok(int x, int y) {
	if (x < 0 || x > n || y < 0 || y > m) return 0;
	if (x == horse_x && y == horse_y) return 0; 
	if (abs(horse_x - x) == 1 && abs(horse_y - y) == 2) return 0;
	if (abs(horse_x - x) == 2 && abs(horse_y - y) == 1) return 0;
	return 1;
}

long long cal(int m, int n) {
	if(n < 0 || m < 0 || n < m) return 0;
	long long ans = 1;
	for(int i = 1; i <= m; i++) {
		ans *= n - i + 1;
		and /= i;
	}
	return ans;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &horse_x, &horse_y);
	if (!ok(0, 0) || !ok(n, m)) {
		printf("%d\n", 0);
	}
		
	long long ans = cal(m, n + m);
	for(int i = -2; i <= 2; i++) {
		ans -= cal(horse_x + i, horse_y - i);
	}
	
	int x1 = horse_x - 3, y1 = horse_y + 2;
	int x2 = n - (horse_x + 2), y2 = horse_y - 2;
	ans += cal(x1, x1 + x2) * cal(n - x2, n + m - x2 - y2);
	ans += cal(horse_x, )
	
	return 0;
}
