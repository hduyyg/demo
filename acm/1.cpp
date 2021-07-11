#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1e4; 
const int maxm = 1e3;
const int inf = 1e8;
int f[2][maxm + 10], up[maxm + 10];
int x[maxn + 10], y[maxn + 10];
int l[maxn + 10], h[maxn + 10];

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
	for(int i = 0; i < k; i++) {
		int p;
		scanf("%d", &p);
		scanf("%d%d", &l[p], &h[p]);
	}
	
	int sump = 0;
	for(int i = 1; i <= n; i++) {
		int pre = (i - 1) % 2;
		int cur = i % 2;
		
		for(int j = 1; j <= m; j++)f[cur][j] = inf, up[j] = f[pre][j];
		for(int j = 1; j <= m; j++) {
			int target = j + x[i - 1];
			if(target > m) target = m;
			up[target] = min(up[target], up[j] + 1);
			if (h[i] == 0 || (l[i] < target && target < h[i])) {
				f[cur][target] = min(f[cur][target], up[j] + 1);
			}
			
			target = j - y[i - 1];
			if(target <= l[i] || (h[i] > 0 && target >= h[i])) {
				continue;
			}
			f[cur][target] = min(f[cur][target], f[pre][j]);
		}
//		for(int j = 1; j <= m; j++) printf("%d %d\n", j, f[cur][j]);
//		printf("************************\n");
		bool flag = false;
		for(int j = 1; j <= m; j++) 
			if (f[cur][j] != inf) {
				flag = true;
				break;	
			}
		if(!flag) {
			printf("0\n%d", sump);
			return 0;
		}
		sump += (l[i] > 0 || h[i] > 0);
	}
	
	int cur = n % 2;
	int ans = f[cur][1];
	for(int i = 2; i<= m; i++) ans = min(ans, f[cur][i]);
	printf("1\n%d", ans);
	return 0;
}
