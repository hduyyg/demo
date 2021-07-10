const
  dx:array[1..4]of longint=(1,0,-1,0);
  dy:array[1..4]of longint=(0,1,0,-1);
var
  a,come:array[0..20,0..20]of char;
  g:array[0..20,1..2]of longint;
  ch:char;
  front,rear,sx,sy,ex,ey,n,gg,i,j,k,t,x,y,xx,yy:longint;
  pre:array[0..20,0..20,1..2]of longint;
  q:array[0..200,1..2]of longint;

procedure terminate;
begin
  close(input);
  close(output);
end;

procedure readdata;
begin
  readln(n,gg);
  k:=0;
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(a[i,j]);
      if a[i,j] in['0'..'9'] then
      begin
        inc(k);
        g[k,1]:=i; g[k,2]:=j;
      end;
      if a[i,j]='E' then begin sx:=i; sy:=j; end;
      if a[i,j]='C' then begin ex:=i; ey:=j; end;
    end;
    readln;
  end;
  for i:=1 to gg do
  begin
    read(k,ch); readln(ch);
    x:=g[k,1]; y:=g[k,2];
    case ch of
      'N':t:=3;
      'S':t:=1;
      'E':t:=2;
      'W':t:=4;
    end;
    while (x>0)and(x<=n)and(y>0)and(y<=n)and(a[x,y]<>'X') do
    begin
      a[x,y]:='X';
      x:=x+dx[t]; y:=y+dy[t];
    end;
  end;
end;

procedure search(x,y:longint);
begin
  if (x=sx)and(y=sy) then exit;
  search(pre[x,y,1],pre[x,y,2]);
  writeln(come[x,y]);
end;

procedure print;
begin
  search(ex,ey);
  terminate;
  halt;
end;

procedure bfs;
begin
  front:=0; rear:=1;
  q[1,1]:=sx; q[1,2]:=sy;
  a[sx,sy]:='X';
  fillchar(pre,sizeof(pre),$ff);
  while front<rear do
  begin
    inc(front);
    x:=q[front,1]; y:=q[front,2];
    for i:=1 to 4 do
    begin
      xx:=x+dx[i]; yy:=y+dy[i];
      if (xx>0)and(xx<=n)and(yy>0)and(yy<=n)and(a[xx,yy]<>'X') then
      begin
        inc(rear);
        q[rear,1]:=xx; q[rear,2]:=yy;
        pre[xx,yy,1]:=x;
        pre[xx,yy,2]:=y;
        case i of
          1:come[xx,yy]:='S';
          2:come[xx,yy]:='E';
          3:come[xx,yy]:='N';
          4:come[xx,yy]:='W';
        end;
        if a[xx,yy]='C' then print else a[xx,yy]:='X';
      end;
    end;
  end;
end;

procedure main;
begin
  if a[sx,sy]='X' then begin writeln(-1); terminate; halt; end;
  bfs;
  writeln(-1);
end;

begin
  assign(input,'guard.in');
  assign(output,'guard.out');
  reset(input);
  rewrite(output);
  
  readdata;
  main;
  terminate;
end.

