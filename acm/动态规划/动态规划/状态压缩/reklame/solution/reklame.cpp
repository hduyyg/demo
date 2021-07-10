
/*
DMIH 2004 - Prvi dan natjecanja
Srednjoskolska skupina - II. podskupina
Zadatak REKLAME
*/

#include <cstdio>
#include <map>

using namespace std;

int n, k, m, x;
int k7;
int a[100][7];

int hash( int *t ) {
  int ret = 0;
  for( int i = 0; i < 7; ++i ) ret = ret * k + t[i];
  return ret;
}
void dehash( int *t, int h ) {
  for( int i = 6; i >= 0; --i ) { t[i] = h%k; h /= k; }
}

void input() {
  scanf( "%d%d", &n, &k ); k++;
  k7 = k*k*k*k*k*k*k;
  for( int i = 0; i < n; ++i ) {
    a[i][0] = 1;
    scanf( "%d", &m ); m--;
    for( int j = 0; j < m; ++j ) {
      scanf( "%d", &x );
      a[i][x-1] = 1;
    }
  }
}

map<pair<int,int>,int> memo;

int rec( int x, int h ) {
  pair<int,int> stanje( x, h );
  if( memo.count( stanje ) ) return memo[stanje];

  if( x == n ) {
    if( !h ) return 0;
    return 1 + rec( x, (h*k)%k7 );
  }

  int i, t[7];
  dehash( t, h );

  for( i = 0; i < 7; ++i ) if( t[i] + a[x][i] == k ) break;

  int ret = 1000000;
  if( h )      ret <?= 1 + rec( x, (h*k)%k7 );
  if( i == 7 ) ret <?= rec( x+1, h+hash( a[x] ) );
  return memo[stanje] = ret;
}

int main( void ) {
  freopen("reklame.in", "r", stdin);
  freopen("reklame.out", "w", stdout);
  input();
  printf( "%d\n", rec( 0, 0 ) );
  fclose(stdin);
  fclose(stdout);
  return 0;
}
