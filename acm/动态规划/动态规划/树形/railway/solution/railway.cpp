
/*
  Croatia 2005 / National Competition #2 / Seniors
  Problem NAGIBNI

  Za svaki cvor A racunamo optimalno rjesenje tog podstabla i to u 2 slucaja:
  1) cvor A je spojen sa svojim ocem
  2) cvor A nije spojen sa svojim ocem

  U 1. slucaju linija koja dolazi iz oca cvora A moze zavrsiti u tom cvoru ili
  prolaziti kroz njega.
  Ako odaberemo da linija zavrsava u cvoru A, onda sva djeca cvora A nisu
  spojena sa svojim ocem (cvorom A).
  Ako odaberemo da linija prolazi kroz cvor A, onda moramo neko podstablo koje
  ce biti spojeno sa svojim ocem. Najbolje je odabrati cvor kod kojeg je razlika
  u optimalnim rjesenjima 1) i 2) maksimalna.

  U 2. slucaju linija moze pocinjati u cvoru I i ici prema nekom od njegove
  djece ili pocinjati u nekom njegovom podstablu, prolaziti kroz njega, te
  zavrsiti u nekom drugom podstablu.
  Ako linija pocinje u cvoru I, onda moramo odabrati podstablo koje ce bit
  spojeno s ocem i opet je to cvor kod kojeg je razlika u optimalnim rjesenjima
  maksimalna.
  Ako linija prolazi kroz cvor I, onda moramo odabrati dva podstabla koja ce
  biti spojena s ocem, a to su dakako dva cvora s najvecom razlikom u
  rjesenjima.
*/

#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

typedef pair<int,int> par;

int N;
map< par, int > memo;
multimap< int, par > E;

const int inf = 1000000;

int rec( int x, int dad, int line ) {
   par state = make_pair( x, line );
   if( memo.count( state ) ) return memo[state];

   int ret = -inf;
   int sum = 0;
   vector<int> a( 2, -inf );

   pair< typeof(E.begin()), typeof(E.begin()) > range = E.equal_range( x );

   for( typeof(E.begin()) it = range.first; it != range.second; ++it ) {
      if( it->second.first == dad ) continue;
      int r0 = rec( it->second.first, x, 0 );
      int r1 = rec( it->second.first, x, 1 ) + it->second.second;
      sum += r0;
      a.push_back( r1-r0 );
   }

   partial_sort( a.begin(), a.begin()+2, a.end(), greater<int>() );

   ret >?= sum + a[0];
   if( line == 0 ) ret >?= sum + a[0] + a[1];
   else ret >?= sum;

   return memo[state] = ret;
}

int main( void ) {
   scanf( "%d", &N );
   for( int i = 1; i < N; ++i ) {
      int a, b, c;
      scanf( "%d%d%d", &a, &b, &c );
      E.insert( make_pair( a, make_pair( b, c ) ) );
      E.insert( make_pair( b, make_pair( a, c ) ) );
   }

   printf( "%d", rec( 1, 0, 0 ) );

   return 0;
}
