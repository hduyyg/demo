#include<cstdio>
#include<algorithm>
using namespace std;

const int maxt = 1000;
int f[maxt + 10];

int main() {
	int t, m;
	scanf("%d%d", &t, &m);
	for(int i = 1; i <= m; i++) {
		int ti, vi;
		scanf("%d%d", &ti, &vi);
		for(int j = t; j >= ti; j--) 
			f[j] = max(f[j], f[j - ti] + vi);
	}
	printf("%d\n", f[t]);
	return 0;
}
