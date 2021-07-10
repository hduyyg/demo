#include <cstdio>
#include <cstring>
using namespace std;

int N;

int elist_head[50000];
int elist_next[200001];
int elist_to[200001];
int elist_n;

int dep[50000];
bool visd[50000];
int next[50000];
int len[50000];
int f[50000];
int ans;

int Q[50000][2]; int head, tail;

void processcircle(int x, int p) {
	int ans2 = 0;
	for (int i = x, l = 1; i != p; i = next[i], l++) {
		ans2 >?= f[i] + (l <? len[x] - l);
		ans >?= f[i] + len[x] / 2;
	}
	ans >?= ans2 + f[p];
	f[p] >?= ans2;
	
	head = tail = 0;
	for (int i = x, j = 0; j < len[x] * 2; j++) {
		int val;
		if (i == p) val = 0;
		else val = f[i];
		
		while (head < tail && j - Q[head][0] > len[x] / 2) head++;
		if (head < tail) ans >?= Q[head][1] + val + j;
		
		while (head < tail && Q[tail - 1][1] <= val - j) tail--;
		Q[tail][0] = j; Q[tail][1] = val - j; tail++;
		
		if (i == p) i = x; else i = next[i];
	}
}

int dfs(int x, int p) {
	visd[x] = true;
	if (p == -1) dep[x] = 0;
	else dep[x] = dep[p] + 1;
	
	int low = dep[x];
	
	for (int i = elist_head[x]; i; i = elist_next[i])
		if (elist_to[i] != p)
			if (visd[elist_to[i]]) {
				if (dep[elist_to[i]] < dep[x]) {
					low = dep[elist_to[i]];
					next[x] = elist_to[i];
					len[x] = 2;
				}
			} else {
				int low2 = dfs(elist_to[i], x);
				if (low2 < low) {
					low = low2;
					next[x] = elist_to[i];
					len[x] = len[elist_to[i]] + 1;
				}
			}
	
	if (low == dep[x] && p != -1) {
		next[x] = p;
		len[x] = 2;
		low--;
	}
	
	if (low == dep[x] - 1)
		processcircle(x, p);
	
	return low;
}


void solve() {
	memset(visd, 0, sizeof visd);
	memset(f, 0, sizeof f);
	
	ans = 0;
	dfs(0, -1);
	
	printf("%d\n", ans);
}

void elist_add(int a, int b) {
	int cur = ++elist_n;
	elist_to[cur] = b;
	elist_next[cur] = elist_head[a]; elist_head[a] = cur;
}

void init() {
	int m; scanf("%d%d", &N, &m);
	
	memset(elist_head, 0, sizeof elist_head);
	elist_n = 0;
	
	for (int i = 0; i < m; i++) {
		int k; scanf("%d", &k);
		int last; scanf("%d", &last); last--;
		for (int j = 1; j < k; j++) {
			int cur; scanf("%d", &cur); cur--;
			elist_add(last, cur); elist_add(cur, last);
			last = cur;
		}
	}
}

int main() {
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	
	init();
	solve();
	
	return 0;
}
