#include <stdio.h>

typedef struct tagroom {
	int l;
	int r;
	int time;
	int vals;
	int val[361];
	int done;
} troom;

FILE* inf;
FILE* outf;

troom room[210];
int ttime; //total time
int size;
int first;

int readtree()
{
	int time,val,cur;
	if (first) {
		fscanf(inf,"%d %d",&time,&val);
		first=0;
	}
	else
		fscanf(inf," %d %d",&time,&val);
	size++; cur=size;
	room[size].time=time;
	room[size].vals=val;
	room[size].done=0;
	if (room[size].vals==0) {
		room[cur].l=readtree(); //for left
		room[cur].r=readtree(); //for right
		return cur;
	}
	else return cur;
}

int main()
{
	inf=fopen("gallery.in","r");
	outf=fopen("gallery.out","w");
	int i,j,k,ref,r,time2;

	fscanf(inf,"%d\n",&ttime);
	ttime--;

	size=0; first=1;
	readtree();
	fclose(inf);

	for (i=1; i<=size; i++) {
		if (room[i].l==0 && room[i].r==0) {
			room[i].done=1;
			for (j=1; j<=room[i].vals; j++) {
				for (k=2*room[i].time+j*5; k<=ttime; k++)
					room[i].val[k]=j;
			}
		}
	}

	do {
		ref=0;
		for (i=1; i<=size; i++) if (room[i].done==0 && room[room[i].l].done==1 && room[room[i].r].done==1) {
			ref=1;
			time2=room[i].time*2;
			for (j=0; j<=ttime; j++) { //total assigned
				room[i].val[j]=0;
				for (k=0; k<=j-time2; k++) { //left assigned
					if (room[room[i].l].val[k]+room[room[i].r].val[j-k-time2]>room[i].val[j])
						room[i].val[j]=room[room[i].l].val[k]+room[room[i].r].val[j-k-time2];
				}
			}
			room[i].done=1;
		}
	} while (ref==1);

	fprintf(outf,"%d",room[1].val[ttime]);
	fclose(outf);
	return 0;
}

