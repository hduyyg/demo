
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

#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

#define MAXN 1005

int koliko_faktora( int x, int f )
{
   int ret = 0;
   while ( x % f == 0 )
      x /= f, ++ret;
   return ret;
}

int main()
{
   int n;
   scanf( "%d", &n );

   static int c[2][MAXN][MAXN];

   for ( int i=2; i<=n; ++i )
      c[0][i][0] = c[0][0][i] = c[1][i][0] = c[1][0][i] = INT_MAX / 2;

   for ( int i=1; i<=n; ++i )
      for ( int j=1; j<=n; ++j ) {
         int x;
         scanf( "%d", &x );

         if ( x == 0 )
            c[0][i][j] = c[1][i][j] = INT_MAX / 2;
         else {
            c[0][i][j] = koliko_faktora( x, 2 ) + min( c[0][i-1][j], c[0][i][j-1] );
            c[1][i][j] = koliko_faktora( x, 5 ) + min( c[1][i-1][j], c[1][i][j-1] );
         }
      }

   printf( "%d\n", min( c[0][n][n], c[1][n][n] ) );

   return 0;
}
