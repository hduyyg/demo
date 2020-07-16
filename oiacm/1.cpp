#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
#include<cstring>
using namespace std;

int main() {
	int x, n;
	scanf("%d%d", &x, &n);
	int ans = 0;
	if(x + n - 1 <= 7) {
		if(x <= 5) {
			ans = (x + n - 1 <= 5) ? n : 5 - x + 1;
		}
	} else {
		ans += (x <= 5) ? 5 - x + 1 : 0;
		n -= 7 - x + 1;
		ans += 5 * (n / 7);
		n %= 7;
		ans += (n <= 5) ? n : 5;
	}
	printf("%d\n", ans * 250);
	return 0;
}
