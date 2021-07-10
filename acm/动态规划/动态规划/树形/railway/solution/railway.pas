
const inf = 1000000;

var
  i, a, b, N : integer;
  w        : longint;
  count      : array[1..2000] of integer;
  adj      : array[1..2000, 1..2000] of integer;
  dulj      : array[1..2000, 1..2000] of longint;
  memo      : array[1..2000, 0..1] of longint;

function rek(x, dad, spojen : integer) : longint;
var i, ret, sum, max, max2, r0, r1 : longint;
begin
  if ( memo[x, spojen] > 0 ) then begin
    rek := memo[x, spojen];
    exit;
  end;

  ret := -inf;
  sum := 0;
  max := -inf; max2 := -inf;

  for i:=1 to count[x] do begin
    if ( adj[x, i] = dad ) then continue;
    r0 := rek( adj[x, i], x, 0 );
    r1 := rek( adj[x, i], x, 1 ) + dulj[x, i];
    sum := sum + r0;
    if ( r1-r0 > max ) then begin
      max2 := max;
      max  := r1-r0;
    end else if ( r1-r0 > max2 ) then begin
      max2 := r1-r0;
    end;
  end;

  if ( sum+max > ret ) then
    ret := sum+max;
  if ( spojen = 0 ) then begin
    if ( sum+max+max2 > ret ) then
      ret := sum+max+ max2;
  end else if ( sum > ret ) then
    ret := sum;

  memo[x, spojen] := ret;
  rek := ret;
end;

begin
  assign(input,'railway.in');
  reset(input);
  assign(output,'railway.out');
  rewrite(output);
  read( N );
  for i:=1 to N-1 do begin
    read( a, b, w );
    count[a] := count[a] + 1;
    count[b] := count[b] + 1;
    adj[a, count[a]] := b;
    adj[b, count[b]] := a;
    dulj[a, count[a]] := w;
    dulj[b, count[b]] := w;
  end;

  writeln( rek( 1, 0, 0 ) );
  close(input);
  close(output)
end.
