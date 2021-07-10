/*
Program		:	Network
Algorithm	:	Dynamic Programming in Trees
Author		:	Chen Mingcheng
*/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#define MAXN 100
#define MAXT 3000

struct Link
{
	int data;
	int table[MAXT+1];
	Link *next;

	Link();
};

FILE *fin,*fout;
Link *list[MAXN];
int opt[MAXN][MAXT+1];
int n,t;

Link::Link()
{
	memset(table,255,sizeof table);
}

void clean(int *table)
{
	int i,j;

	for (i=t; i>0; i--)
		if (table[i]!=-1)
			for (j=i-1;j>=0;j--)
				if (table[j]!=-1 && table[j]<table[i])
				{
					table[i]=-1;
					break;
				}
}

void add_link(int a,int b)
{
	Link *temp=new Link;

	temp->data=b; temp->next=list[a];
	list[a]=temp;
}

void init()
{
	fin=fopen("network.in","r");
	fout=fopen("network.out","w");
	fscanf(fin,"%d%d",&n,&t);
	memset(list,0,sizeof list);

	int i,j,a,b,k,d,c;

	for (i=0; i<n-1; i++)
	{
		fscanf(fin,"%d%d%d",&a,&b,&k);
		a--; b--;
		add_link(a,b); add_link(b,a);
		for (j=0; j<k; j++)
		{
			fscanf(fin,"%d%d",&d,&c);
			if (d<=t)
			{
				if (list[a]->table[d]==-1 || list[a]->table[d]>c)
					list[a]->table[d]=c;
				if (list[b]->table[d]==-1 || list[b]->table[d]>c)
					list[b]->table[d]=c;
			}
		}
		clean(list[a]->table);
		clean(list[b]->table);
	}
}

void dfs(int pre,int v)
{
	Link *temp=list[v],*temp2;
	int table[MAXT+1];
	int i,j,tt,flag=1;

	for (; temp!=0; temp=temp->next)
		if (temp->data!=pre)
		{
			flag=0;
			dfs(v,temp->data);

			memset(table,255,sizeof table);
			for (i=0; i<=t; i++)
				if (opt[temp->data][i]!=-1)
					for (j=0; j<=t-i; j++)
						if (temp->table[j]!=-1)
							if (table[i+j]==-1 || table[i+j]>opt[temp->data][i]+temp->table[j])
							{
								table[i+j] = opt[temp->data][i] + temp->table[j];
							}

			clean(table);
			memcpy(opt[temp->data],table,sizeof table);
		}
	if (flag)
	{
		opt[v][0]=0;
		return;
	}

	int sum;

	for (temp=list[v]; temp!=0; temp=temp->next)
		if (temp->data!=pre)
			for (tt=t; tt>=0; tt--)
				if (opt[temp->data][tt]!=-1)
				{
					sum=opt[temp->data][tt];
					for (temp2=list[v]; temp2!=0; temp2=temp2->next)
						if (temp2->data!=pre && temp2!=temp)
						{
							i=(t-tt)<?tt;
							for (; i>=0&&opt[temp2->data][i]==-1; i--);
							if (i==-1) break;
							sum+=opt[temp2->data][i];
						}
					if (i!=-1)
						if (opt[v][tt]==-1 || opt[v][tt]>sum) opt[v][tt]=sum;
				}
	clean(opt[v]);
}

void work()
{
	memset(opt,255,sizeof opt);
	dfs(-1,0);
	int ans=t;
	for (; ans>=0&&opt[0][ans]==-1; ans--);
	if (ans==-1) fprintf(fout,"-1\n");
	else fprintf(fout,"%d\n",opt[0][ans]);
	fclose(fin); fclose(fout);
}

int main()
{
	init();
	work();
	return 0;
}
