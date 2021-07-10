#include <cstdio>
#include <cstdlib>
#include <cmath>
#include<ctime>
#include <algorithm>
#define max(a, b) (a < b ? b : a)
using namespace std;

int n;
int L;
int a[10086];
int b[10086];

//next_permutation
//pow
//sort
//check
//calc

bool check(int n)
{
 for(int i = 0; i < n; i++)
         for(int j = i + 1; j < n; j++)
         {
           if (a[i] + 100 < a[j])         return 0;
         }
         return 1;
 }

double calc(int x, int y)
{
   double t = ((y - x) / 400.0000000);
   double k = pow(10, t);
   double e = 1.0 + k;
   return (1.0 / e);
}

void init_file()
{
     freopen("compete.in", "r", stdin);
     freopen("compete.out", "w", stdout);
}

void read_data()
{
     scanf("%d", &n);
     for(int i = 0; i < n; i++)
       scanf("%d", a + i);
     for(int i = 0; i < n; i++)
       scanf("%d", b + i);
     std::sort(a, a + n);
     scanf("%d", &L);
}

void work()
{
     double minn = -4654999.0;
     while(1)
     {
       if (check(n))
       {
                    double sum = 1e-9;
        for(int i = 0; i < n; i++)
        {
           sum += calc(a[i], b[i]);
        }             
      //  printf("%.6lf\n", sum);
        minn = max(minn, sum);
       }
//       if (!check(n)) goto k;
if((double)clock()/CLOCKS_PER_SEC > 1.7) goto k;
       if(!next_permutation(a, a + n)) break;       
      // for(int i = 0; i < n; i++)printf("now a[] : %d \n", a[i]);
     }
k:     printf("%.6lf\n", minn);
//printf("%d", check(n));


}

int main()
{
    init_file();
    read_data();
    work();
    return 0;    
}
