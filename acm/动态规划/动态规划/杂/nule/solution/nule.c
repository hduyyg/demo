
/*
  Croatia 2005 / Regional Competition / Seniors
  Problem NULE

  Opis algoritma:
  Uocimo da je broj nula na nekom putu jednak min(fak2, fak5), gdje su
  fak2 i fak5 broj faktora 2 i faktora 5 u rastavu cijene tog puta na
  faktore. Ovo nam omogucava da nadjemo rjesenje bez eksplicitnog
  racunanja cijene puta.
  Iz ovoga slijedi (a jednostavno je dokazati) da optimalan put ima
  ili najmanji moguci broj faktora 2 ili najmanji moguci broj faktora
  5 u rastavu cijene na faktore.
  A to cemo iskoristiti tako sto cemo naci dva puta, jedan s najmanjim
  mogucim brojem faktora 2, a jedan s najmanjim mogucim brojem faktora
  5 i tada je ukupno rjesenje (broj nula na kraju optimalnog puta)
  minimum faktora 2 na prvom putu i faktora 5 na drugom putu.
  Puteve nalazimo jednostavnim dinamickim programiranjem:
  faktora[x][y] =
     na_trenutnom_polju + min( faktora[x-1][y], faktora[x][y-1] )

  Vremenska slozenost: O(N^2)
*/

#include <stdio.h>

#define MAX_N 1000
#define VELIKI_BROJ 1000000

int manji(int a,int b)
{
  if (a < b)
    return a;
  return b;
}

int rastavi(int a,int b)
{
  int brojac;

  brojac = 0;
  while (1)
  {
    if (a % b)
      return brojac;
    a /= b;
    ++brojac;
  }
}

int main(void)
{
  int i,j,k;
  int n;
  int prethodni_redak[2][MAX_N + 1],trenutni_redak[2][MAX_N + 1];
  int broj;

  //

  scanf("%d",&n);

  for (i = 0;i < 2;++i)
  {
    prethodni_redak[i][1] = 0;
    for (j = 2;j <= n;++j)
      prethodni_redak[i][j] = VELIKI_BROJ;
    trenutni_redak[i][0] = VELIKI_BROJ;
  }

  for (i = 1;i <= n;++i)
  {
    for (j = 1;j <= n;++j)
    {
      scanf("%d",&broj);

      for (k = 0;k < 2;++k)
        if (!broj)
          trenutni_redak[k][j] = VELIKI_BROJ;
        else
          trenutni_redak[k][j] = rastavi(broj,!k ? 2 : 5) +
                                 manji(trenutni_redak[k][j - 1],
                                       prethodni_redak[k][j]);
    }

    for (j = 0;j < 2;++j)
      for (k = 1;k <= n;++k)
        prethodni_redak[j][k] = trenutni_redak[j][k];
  }

  printf("%d\n",manji(trenutni_redak[0][n],trenutni_redak[1][n]));

  return 0;
}
