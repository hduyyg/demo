#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int c[30][30];
int num[10];
double value[1000000];

inline int change(int* list) {
	int i,s,t;

	s=t=0;
	for (i=8;i>=1;i--) {
		t+=c[16-s+i][i]-c[16-s-list[i]+i][i];
		s+=list[i];
	}
	return t;
}

void calc(int t,int s,int sum) {
	int i,j;
	int v;
	double p,q;

	if (t==0) {
		num[0]=s;
		v=change(num);
		value[v]=0;
		if (sum==0) {
			return;
		}
		for (i=1;i<=8;i++) {
			if (!num[i]) continue;
			p=num[i]*i*1.0/sum;
			num[i]--;
			num[i-1]++;
			if ((i&1)==0) {
				for (j=1;j<=8;j++) {
					if (!num[j]) continue;
					q=num[j]*j*p/(sum-1);
					num[j]--;
					num[j-1]++;
					if ((j&1)==0) {
						value[v]+=(value[change(num)]+1)*q;
					} else {
						if (j==i-1) {
							value[v]+=(value[change(num)]+2-1.0/(num[j]+1))*q;
						} else {
							value[v]+=(value[change(num)]+2)*q;
						}
					}
					num[j-1]--;
					num[j]++;
				}
			} else {
				value[v]+=(value[change(num)]+1)*p;
			}
			num[i-1]--;
			num[i]++;
		}
		return;
	}
	for (num[t]=0;num[t]<=s;num[t]++) {
		calc(t-1,s-num[t],sum+num[t]*t);
	}
}

void main() {
	freopen("shinkei.in", "r", stdin);
	freopen("shinkei.out", "w", stdout);
		
	int i,j;
	int list[10];
	int n,m;

	for (i=0;i<=26;i++) {
		c[i][0]=c[i][i]=1;
		for (j=1;j<i;j++) {
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}
	calc(8,16,0);
	scanf("%d%d",&n,&m);
	memset(list,0,sizeof(list));
	list[m*2]=n;
	list[0]=16-n;
	printf("%.6lf\n",value[change(list)]);
}