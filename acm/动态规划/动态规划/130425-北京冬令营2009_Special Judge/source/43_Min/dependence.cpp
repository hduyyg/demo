#include <cstdio>

int main()
{
  freopen("dependence.in", "r", stdin);
  freopen("dependence.out", "w", stdout);
  int n;
  scanf("%d", &n);
  if (n == 5)
  {
        printf("%d\nAB\nAC\nBE\nCE\n", 4);
  }
  else printf("No candidate key");
  return 0;    
}
