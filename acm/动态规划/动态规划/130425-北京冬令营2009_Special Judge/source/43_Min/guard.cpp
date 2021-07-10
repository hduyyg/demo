#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define L 2001
#define M 20001
int head,tail=1;
int n;
int dx[5] = {21, 1, -1, 0, 0};
bool hash[L][L],ailen[L][L];
int dy[5] = {21, 0, 0, -1, 1};
int m;
char Map[12][12];const int step[5][3]={{1,0},{0,1},{-1,0},{0,-1}};
int sI;
int sJ;
int eI;
int eJ;
struct guard
{
       int I;
       int J;
       char D;
}Guard[11];

struct Ailen{
       int x,y,d;
              int father;
       }q[M];


guard queue[100866];

void init_file()
{
     freopen("guard.in", "r", stdin);
     freopen("guard.out", "w", stdout);
}

void read_data()
{
     for(int i = 0; i <= n + 1; i++)
     for(int j = 0; j <= n + 1; j++)
     {
        if (i <= n && i >= 1 && j <= n && j >= 1)
        Map[i][j] = '.';
        else Map[i][j] = 'X';
     }
     
     scanf("%d%d", &n, &m);
     for(int i = 1; i <= n; i++)
             for(int j = 1; j <= n; j++)
             {
                char ch;
K:                ch = getchar();
                if (ch == '\n' || ch == ' ')
                {
                   goto K;       
                }
  //              printf("%c", ch);
                Map[i][j] = ch;
                if (ch == 'E')
                {
                    sI = i;
                    sJ = j;
                }
                if (ch == 'C')
                {
                    eI = i;
                    eJ = j;   
                }
                if (ch >= '1' && ch <= '9')
                {
                    Guard[ch - '0'].I = i;
                    Guard[ch - '0'].J = j;
                }
             }
/*             for(int i = 1; i <= n; i++)
             {
               for(int j = 1; j <= n; j++)
               printf("%c", Map[i][j]);
               printf("\n")        ;
             }*/
     for(int i = 1; i <= m; i++)
     {
         int x;
         char ch;
         scanf("%d", &x);
k:         ch = getchar();
         if (ch == 'S' || ch == 'N' || ch == 'E' || ch == 'W')
         Guard[x].D = ch;
         else goto k;
     }
}



void pre()
{
     for(int i = 1; i <= m; i++)
     {
         if(Guard[i].D == 'N')
         {
            for(int j = Guard[i].I; j >= 1; j--)
            {
                if (Map[j][Guard[i].J] == 'X') break;
                Map[j][Guard[i].J] = 'K';
            }
         }
         if (Guard[i].D == 'S')
         {
            for(int j = Guard[i].I; j <= n; j++)
            {
                if (Map[j][Guard[i].J] == 'X') break;
                Map[j][Guard[i].J] = 'K';
            }
         }
         if (Guard[i].D == 'W')
         {
            for(int j = Guard[i].J; j >= 1; j--)
            {
                if (Map[Guard[i].I][j] == 'X') break;
                Map[Guard[i].I][j] = 'K';
            }
         }
         if (Guard[i].D == 'E')
         {
            for(int j = Guard[i].J; j <= n; j++)
            {
                if (Map[Guard[i].I][j] == 'X') break;
                Map[Guard[i].I][j] = 'K';
            }
         }
     }
     for(int i = 0; i <= n + 1; i++)
             for(int j = 0; j <= n + 1; j++)
             {if (Map[i][j] == '.') ailen[i][j] = 0;else ailen[i][j] = 1;}
             ailen[sI][sJ] = ailen[eI][eJ] = 0;
}
int stx;
int sty;
int stf;
Ailen REC;

void print(int x)
{
     if (x == 0) return;
     print(q[x].father);
     Ailen d, D;
     d = q[q[x].father];
     D = q[x];
/*     printf("x = %d  y = %d\n", d.x, d.y);
     printf("X = %d  Y = %d\n", D.x, D.y);*/
     if (D.x > d.x && D.y == d.y) printf("S\n");
     if (D.x < d.x && D.y == d.y) printf("N\n");
     if (D.y > d.y && D.x == d.x) printf("E\n");
     if (D.y < d.y && D.x == d.x) printf("W\n");
     REC = D;
}


void Bfs(){
     q[0].x = sI;
     q[0].y = sJ;
     q[0].d = 0;
     hash[sI][sJ]=true;
     while(head<tail){
         for(int i=0;i<4;i++){
             stx=q[head].x+step[i][0];
             sty=q[head].y+step[i][1];
             stf=head;
             if(stx>=1&&stx<=n&&sty>=1&&sty<=m&&!ailen[stx][sty]&&!hash[stx][sty]){
               if(stx==eI && sty==eJ){
                  //printf("%d\n",q[head].d+1);
                  print(head);
                  return;
                  }
               q[tail].x=stx;
               q[tail].y=sty;
               q[tail].d=q[head].d+1;
               q[tail].father = stf;
               hash[stx][sty]=true;
               tail++;
               }
             }
         head++;
         }
     printf ("%d", -1);
}     
     

void work()
{
/*     for(int i = 1; i <= n; i++){
     for(int j = 1; j <= n; j++){
     printf("%d", ailen[i][j]);}
     printf("\n");
     }*/
  Bfs();   
//  printf("REC.x = %d  REC.y = %d\n", REC.x, REC.y);
     if (REC.x > eI && REC.y == eJ) printf("N\n");
     if (REC.x < eI && REC.y == eJ) printf("S\n");
     if (REC.y > eJ && REC.x == eI) printf("W\n");
     if (REC.y < eJ && REC.x == eI) printf("E\n");
}

int main()
{
    init_file();
    read_data();
    pre();
//    printf("%c", Guard[1].D);
    work();
//    printf("%d", 2);

    return 0;
}
