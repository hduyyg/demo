Program ex5;
Const
    maxn=1000;
    maxbranch=8;
Var
    g:array[1..maxn,0..8]of longint;
    b:array[1..maxn]of boolean;
    x,y,z:array[1..maxn]of longint;
    i,j,n:longint;
    c:char;
Procedure dfs(i:longint);
var
    j:longint;
procedure sort(x:longint);
var
    i,j,k:longint;
begin
    for i:=1 to g[x,0]-1 do
      for j:=1 to g[x,0]-i do
        if (y[g[x,j]]+2)*z[g[x,j+1]]>(y[g[x,j+1]]+2)*z[g[x,j]] then
          begin
            k:=g[x,j];
            g[x,j]:=g[x,j+1];
            g[x,j+1]:=k;
          end;
end;
begin
    x[i]:=0;
    y[i]:=0;
    z[i]:=0;
    if g[i,0]=0 then
      begin
        z[i]:=1;
        exit;
      end;
    for j:=1 to g[i,0] do
      dfs(g[i,j]);
    sort(i);
    for j:=1 to g[i,0] do
      begin
        x[i]:=x[i]+(y[i]+1)*z[g[i,j]]+x[g[i,j]];
        y[i]:=y[i]+y[g[i,j]]+2;
        z[i]:=z[i]+z[g[i,j]];
      end;
    if b[i] then y[i]:=0;
end;
Begin
    readln(n);
    while n>0 do
      begin
        fillchar(g,sizeof(g),0);
        for i:=1 to n do
          begin
            read(j);
            read(c);
            readln(c);
            if c='Y' then b[i]:=true else b[i]:=false;
            if j>-1 then
              begin
                inc(g[j,0]);
                g[j,g[j,0]]:=i;
              end;
          end;
        dfs(1);
        writeln(x[1]/z[1]:0:4);
        readln(n);
      end;
End.