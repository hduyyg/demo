program guard;
var
  a:array[0..20]of string;
  b:array[0..20]of char;
  map:array[0..20,0..20]of boolean;
  f:array[0..20,0..20]of longint;
  sx,sy,tx,ty,n,g:longint;
  du:array[0..200,1..2]of longint;
procedure  init ;
begin
  assign(input,'guard.in');
  assign(output,'guard.out');
  reset(input);
  rewrite(output);
end;
procedure outit;
begin
  close(input) ;
  close(output);
end;

procedure north(i,j:longint);
begin
  while (a[i-1][j]<>'X')and(i-1>0) do
    begin
      i:=i-1;
      map[i,j]:=false;
    end;
end;
procedure south(i,j:longint);
begin
  while (a[i+1][j]<>'X')and(i+1<n) do
    begin
      i:=i+1;
      map[i,j]:=false;
    end;
end;
procedure west(i,j:longint);
begin
  while (a[i][j-1]<>'X')and(j-1>0) do
    begin
      j:=j-1;
      map[i,j]:=false;
    end;
end;
procedure east(i,j:longint);
begin
  while (a[i][j+1]<>'X')and(j+1<n) do
    begin
      j:=j+1;;
      map[i,j]:=false;
    end;
end;


procedure prepare;
var
  i,j,x:longint;
  s:string;
  c:char;
begin
  readln(n,g);
  for i:=1 to  n do
    begin
      readln(a[i]);
    end;
  for i:=1 to g do
    begin
      read(x);
      readln(s);
      j:=1;
      while j<=length(s) do
        begin
         if s[j]=' '  then delete(s,j,1);
         j:=j+1;
       end;
     b[x]:=s[1];
    end;
//读入
//————————
  for i:=1 to  n do
    for j:=1 to n do
      begin
        case a[i][j] of
          '.':map[i,j]:=true;
          'E':begin
                map[i,j]:=true; sx:=i; sy:=j;
              end;
          'C':begin
                map[i,j]:=true; tx:=i; ty:=j;
              end;
          'X':map[i,j]:=false;
          else map[i,j]:=false;
         end;
      end;
  for i:=1 to n do
    for j:=1 to n do
      begin
        x:=ord(a[i][j])-48;
        if (x>0)and(x<10)
          then begin
            map[i,j]:=false;
            case b[x] of
              'N':north(i,j);
              'S':south(i,j);
              'W':west(i,j);
              'E':east(i,j);
            end;
          end;
      end;
  {for i:=1 to n do
    begin
      for j:=1 to n do
        begin
          if map[i,j] then write(1)
                      else write(0);
        end;
      writeln;
    end;}
//预处理，建图
  if (map[sx,sy]=false) or (map[tx,ty]=false)
    then begin
      writeln(-1);
      outit;
      halt;
    end;
//最特殊情况
end;


procedure main;
var
  i,j,l,r:longint;
begin
  l:=0;
  r:=1;
  du[r,1]:=tx;
  du[r,2]:=ty;
  f[tx,ty]:=1;
  repeat
    l:=l+1;
    i:=du[l,1];
    j:=du[l,2];
    if (map[i-1,j])and(f[i-1,j]=0)                //上
      then begin
        f[i-1,j]:=f[i,j]+1;
        r:=r+1;
        du[r,1]:=i-1;
        du[r,2]:=j;
      end;
    if (map[i+1,j])and(f[i+1,j]=0)               //下
      then begin
        f[i+1,j]:=f[i,j]+1;
        r:=r+1;
        du[r,1]:=i+1;
        du[r,2]:=j;
      end;
    if (map[i,j-1])and(f[i,j-1]=0)               //左
      then begin
        f[i,j-1]:=f[i,j]+1;
        r:=r+1;
        du[r,1]:=i;
        du[r,2]:=j-1;
      end;
    if (map[i,j+1])and(f[i,j+1]=0)               //右
      then begin
        f[i,j+1]:=f[i,j]+1;
        r:=r+1;
        du[r,1]:=i;
        du[r,2]:=j+1;
      end;
  until (l>=r)or(f[sx,sy]<>0);

//求方案
    if f[sx,sy]=0
    then begin
      writeln(-1);
      outit;
      halt;
    end;

  i:=sx;
  j:=sy;
  repeat
    if f[i-1,j]=f[i,j]-1
      then  begin writeln('N'); i:=i-1; continue; end;
    if f[i+1,j]=f[i,j]-1
      then  begin writeln('S'); i:=i+1; continue; end;
    if f[i,j-1]=f[i,j]-1
      then  begin writeln('W'); j:=j-1; continue; end;
    if f[i,j+1]=f[i,j]-1
      then  begin writeln('E'); j:=j+1; continue; end;
      
  until (i=tx)and(j=ty);

    
end;

begin
  init;
  prepare;
  main;
  outit;
end.
