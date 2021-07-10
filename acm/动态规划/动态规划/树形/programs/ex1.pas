Program ex1;
Const
    maxn=100000;
Type
    link=^node;
    node=record
           x,y:longint;
           next:link;
         end;
Var
    g:array[1..maxn]of link;
    f:array[1..maxn]of longint;
    i,m,n,x,y,z,s:longint;
    p:link;
Procedure dfs(x,father:longint);
var
    p:link;
    m,k,j:longint;
begin
    p:=g[x];
    m:=0;
    k:=0;
    while p<>nil do
      begin
        inc(k);
        if father<>p^.x then
          begin
            dfs(p^.x,x);
            if f[p^.x]+p^.y>m then
              begin
                m:=f[p^.x]+p^.y;
                j:=k;
              end;
          end;
        p:=p^.next;
      end;
    f[x]:=m;
    p:=g[x];
    m:=0;
    k:=0;
    while p<>nil do
      begin
        inc(k);
        if (p^.x<>father)and(m<f[p^.x]+p^.y)and(j<>k) then
          m:=f[p^.x]+p^.y;
        p:=p^.next;
      end;
    if s<f[x]+m then s:=f[x]+m;
end;
Begin
    readln(n,m);
    for i:=1 to n do
      g[i]:=nil;
    for i:=1 to m do
      begin
        readln(x,y,z);
        new(p);
        p^.x:=x;
        p^.y:=z;
        p^.next:=g[y];
        g[y]:=p;
        new(p);
        p^.x:=y;
        p^.y:=z;
        p^.next:=g[x];
        g[x]:=p;
      end;
    s:=0;
    dfs(1,0);
    writeln(s);
End.