Program ex8;
Const
    maxn=100000;
    maxm=18;
Type
    link=^node;
    node=record
           x,y:longint;
           next:link;
         end;
Var
    f,d:array[1..maxn,0..maxm]of longint;
    depth:array[1..maxn]of longint;
    v:array[1..maxn]of boolean;
    g:array[1..maxn]of link;
    m,n,k,i,j,x,y,z,s,l,t:longint;
    p:link;
Procedure dfs(x,father,dist,s:longint);
var
    p:link;
begin
    f[x,0]:=father;
    v[x]:=true;
    d[x,0]:=dist;
    depth[x]:=s;
    p:=g[x];
    while p<>nil do
      begin
        if not v[p^.x] then
          dfs(p^.x,x,p^.y,s+1);
        p:=p^.next;
      end;
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
    fillchar(v,sizeof(v),false);
    fillchar(f,sizeof(f),0);
    fillchar(d,sizeof(d),0);
    dfs(1,0,0,1);
    k:=n;
    m:=0;
    while k>0 do
      begin
        inc(m);
        k:=k shr 1;
      end;
    for j:=1 to m do
      for i:=1 to n do
        if f[i,j-1]>0 then
          begin
            f[i,j]:=f[f[i,j-1],j-1];
            if f[i,j]>0 then
              d[i,j]:=d[i,j-1]+d[f[i,j-1],j-1];
          end;
    readln(k);
    for i:=1 to k do
      begin
        readln(x,y);
        s:=0;
        if depth[x]<depth[y] then
          begin
            z:=x;
            x:=y;
            y:=z;
          end;
        z:=depth[x]-depth[y];
        l:=1 shl m;
        t:=m;
        while z>0 do
          begin
            if z>=l then
              begin
                s:=s+d[x,t];
                x:=f[x,t];
                z:=z-l;
              end;
            dec(t);
            l:=l shr 1;
          end;
        if x=y then
          begin
            writeln(s);
            continue;
          end;
        l:=1 shl m;
        t:=m;
        while l>0 do
          begin
            if (depth[x]>l)and(f[x,t]<>f[y,t]) then
              begin
                s:=s+d[x,t]+d[y,t];
                x:=f[x,t];
                y:=f[y,t];
              end;
            l:=l shr 1;
            dec(t);
          end;
        inc(s,d[x,0]);
        inc(s,d[y,0]);
        writeln(s);
      end;
End.
