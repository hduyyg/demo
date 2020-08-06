#include<cstdio>
#include<cmath>
using namespace std;

const int maxn = 1e6;
int s1[maxn + 10], s2[maxn + 10];

int main() {
	int n, m, sum_time = 0;
	scanf("%d%d", &n, &m);
	for(int i = 0, j = 0; i < n; i++) {
		int s, t;
		scanf("%d%d", &s, &t), sum_time += t;
		
		while(t--) {
			s1[j + 1] = s1[j] + s;
			j++;
		}
	}
	
	for(int i = 0, j = 0; i < m; i++) {
		int s,t;
		scanf("%d%d", &s, &t);
		
		while(t--) {
			s2[j + 1] = s2[j] + s;
			j++;
		}
	}
	
	int ans = 0;
	bool dayu = s1[1] > s2[1];
	for(int i = 2; i <= sum_time; i++) {
		if(dayu ^ (s1[i] > s2[i])) {
			ans++;
		}
		dayu = s1[i] > s2[i];
	}
	printf("%d\n", ans);
	return 0;
} 
