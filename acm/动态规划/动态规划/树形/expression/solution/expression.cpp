#include<cstdio>
#include<memory>

__int64 a[55][55],b[55][55],s,l,ta[55],tb[55],e;
int n,q,i;

__int64 dv(__int64 x,int y)
{
	__int64 z;
	z=x;
	while(z%y)z+=q;
	return z/y;
}

void tr(int i,int m,int r,int c)
{
	int j,k,o;
	__int64 sa[55],sb[55],pa[55],pb[55];
	s=(s+s+1)%q;
	for(j=r;j<=m;j++)
	{
		if(j>m/2)
		{
			if(!i)break;
			j=m;
		}
		c++;
		if(j>r)c=1;
		e=dv(e,c);
		for(k=2;k<=j;k++)e=dv(e,k);
		memcpy(sa,ta,n*8);
		memcpy(sb,tb,n*8);
		memcpy(pa,ta,n*8);
		memcpy(pb,tb,n*8);
		memset(ta,0,n*8);
		memset(tb,0,n*8);
		for(o=0;o<n-j;o++)
			for(k=0;k<j;k++)
			{
				ta[o+k]=(ta[o+k]+pa[o]*a[j][k])%q;
				tb[o+k]=(tb[o+k]+pb[o]*b[j][k])%q;
			}
		if(j<m)tr(i+1,m-j,j,c);
		else
			for(k=0;k<n;k++)
			{
				a[n][k+i]=(a[n][k+i]+tb[k]*e)%q;
				b[n][k]=(b[n][k]+ta[k]*s%q*e)%q;
			}
		memcpy(ta,sa,n*8);
		memcpy(tb,sb,n*8);
		e=e*c%q;
		for(k=2;k<=j;k++)e=e*k%q;
	}
	s=dv(s+q-1,2);
}

int main()
{
    freopen("expression.in","r",stdin);
    freopen("expression.out","w",stdout);
	a[1][0]=1;b[1][0]=1;ta[0]=1;tb[0]=1;
	q=1000000007;e=1;
	for(n=2;n<31;n++)
	{
		e=e*n%q;
		tr(0,n,1,0);
	}
	scanf("%d",&n);
		if(n<2)
			puts("1");
		else {
    		s=0;l=0;
	    	for(i=0;i<n;i++)
      		{
	    		l=(l+l+1)%q;
		    	s=(s+l*(a[n][i]+b[n][i]))%q;
       		}
	     	printf("%I64d\n",s);
        }
	return 0;
}

