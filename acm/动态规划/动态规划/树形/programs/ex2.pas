Program ex2;
Const
    maxn=1000;
    base=9901;
Var
    c:array[0..maxn,0..maxn]of longint;
    a,l,r,leaf,opt:array[0..maxn]of longint;
    i,j,p,q,n:longint;
Procedure dfs(x:longint);
var
    t:longint;
begin
    t:=1;
    if l[x]>0 then
      begin
        dfs(l[x]);
        t:=t*opt[l[x]];
      end;
    if r[x]>0 then
      begin
        dfs(r[x]);
        t:=t*opt[r[x]];
      end;
    t:=t mod base;
    t:=t*c[(leaf[x]-1),leaf[l[x]]] mod base;
    opt[x]:=t;
end;
Begin
    fillchar(c,sizeof(c),0);
    for i:=0 to maxn do
      for j:=0 to i do
        if (j=0)or(j=i) then
          c[i,j]:=1
        else
          c[i,j]:=(c[i-1,j-1]+c[i-1,j])mod base;
    readln(n);
    while n>0 do
      begin
        for i:=1 to n do
          read(a[i]);
        readln;
        fillchar(l,sizeof(l),0);
        fillchar(r,sizeof(r),0);
        fillchar(leaf,sizeof(leaf),0);
        leaf[1]:=1;
        for i:=2 to n do
          begin
            p:=1;
            q:=0;
            while p<>0 do
              begin
                inc(leaf[p]);
                q:=p;
                if (a[p]<a[i]) then
                  p:=r[p]
                else
                  p:=l[p];
              end;
            if a[q]<a[i] then
              r[q]:=i
            else
              l[q]:=i;
            leaf[i]:=1;
          end;
        dfs(1);
        writeln(opt[1]);
        readln(n);
      end;
End.