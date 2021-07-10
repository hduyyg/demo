Program ex3;
Const
    maxn=100000;
Type
    link=^node;
    node=record
           next:link;
           w:longint;
         end;
Var
    g:array[1..maxn]of link;
    f:array[1..maxn,1..2]of longint;
    w:array[1..maxn]of longint;
    v:array[1..maxn]of boolean;
    n,i,x,y:longint;
    p:link;
Function max(x,y:longint):longint;
begin
    if x>y then max:=x else max:=y;
end;
Procedure dfs(x:longint);
var
    p:link;
begin
    v[x]:=true;
    p:=g[x];
    f[x,1]:=w[x];
    f[x,2]:=0;
    while p<>nil do
      begin
        if not v[p^.w] then
          begin
            dfs(p^.w);
            f[x,1]:=f[x,1]+f[p^.w,2];
            f[x,2]:=f[x,2]+max(f[p^.w,1],f[p^.w,2]);
          end;
        p:=p^.next;
      end;
end;
Begin
    readln(n);
    for i:=1 to n do
      begin
        readln(w[i]);
        g[i]:=nil;
      end;
    fillchar(v,sizeof(v),false);
    for i:=1 to n-1 do
      begin
        readln(x,y);
        new(p);
        p^.w:=y;
        p^.next:=g[x];
        g[x]:=p;
        new(p);
        p^.w:=x;
        p^.next:=g[y];
        g[y]:=p;
      end;
    dfs(1);
    writeln(max(f[1,1],f[1,2]));
End.