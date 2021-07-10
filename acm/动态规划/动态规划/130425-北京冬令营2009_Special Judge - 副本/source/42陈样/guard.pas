program guard;
const
  move:array[1..4,1..2] of longint=((-1,0),(1,0),(0,-1),(0,1));
  remove:array[1..4,1..2] of longint=((1,0),(-1,0),(0,1),(0,-1));
  change:array[1..4] of char=('N','S','W','E');
type
  ty=record
    x,y:longint;
  end;

var
  n,g,i,j,fx1,fx2,fy1,fy2,x:longint;
  p:char;
  toward:array[0..10] of longint;
  f:array[0..10,0..10] of longint;
  map:array[0..10,0..10] of char;
  w,get:array[0..10,0..10] of boolean;
  dui:array[0..1000] of ty;
//===================================
procedure outit;
begin
  close(input); close(output);
  halt;
end;
//===================================
procedure map_new(x,y:longint);
var
  i,j,t:longint;
begin
  t:=toward[ord(map[x,y])-ord('0')];
  i:=x+move[t,1]; j:=y+move[t,2];
  while (i>0)and(j>0)and(i<=n)and(j<=n)and(map[i,j]<>'X') do
  begin
    w[i,j]:=false;
    i:=i+move[t,1]; j:=j+move[t,2];
  end;
end;
//===================================
procedure print(x,y:longint);
begin
  if f[x,y]=0 then exit;
  print(x+remove[f[x,y],1],y+remove[f[x,y],2]);
  writeln(change[f[x,y]]);
end;
//===================================
procedure dfs;
var
  l,r,i,x,y:longint;
begin
  l:=0; r:=1; dui[1].x:=fx1; dui[1].y:=fy1;
  get[fx1,fy1]:=true;
  while l<r do
  begin
    inc(l);
    for i:=1 to 4 do
    begin
      x:=dui[l].x+move[i,1]; y:=dui[l].y+move[i,2];
      if (x<1)or(x>n)or(y<1)or(y>n)or not w[x,y] or get[x,y] then continue;
      get[x,y]:=true;
      f[x,y]:=i;
      inc(r);
      dui[r].x:=x; dui[r].y:=y;
      if (x=fx2)and(y=fy2) then
      begin
        print(x,y);
        outit;
      end;
    end;
  end;
end;
//===================================
begin
  assign(input,'guard.in'); reset(input);
  assign(output,'guard.out'); rewrite(output);
  readln(n,g);
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(map[i,j]);
      if map[i,j]='.' then w[i,j]:=true else
      if map[i,j]='E' then begin fx1:=i; fy1:=j; w[i,j]:=true; end else
      if map[i,j]='C' then begin fx2:=i; fy2:=j; w[i,j]:=true; end;
    end;
    readln;
  end;
  for i:=1 to g do
  begin
    read(x); read(p); readln(p);
    case p of
    'N':toward[x]:=1;
    'S':toward[x]:=2;
    'W':toward[x]:=3;
    'E':toward[x]:=4;
    end;
  end;
  for i:=1 to n do
  for j:=1 to n do
  if map[i,j] in ['0'..'9'] then map_new(i,j);
  if not w[fx1,fy1] or not w[fx2,fy2] then
  begin
    writeln(-1);
    outit;
  end;
  dfs;
  writeln(-1);
  close(input); close(output);
end.

