Program ex6;
Const
    maxn=1000;
    maxk=25;
Var
    a,s,f,w,c,width,height,d:array[1..maxn]of longint;
    g:array[1..maxn,1..maxn]of longint;
    opt:array[1..maxn,0..maxk]of longint;
    b:array[0..maxk]of longint;
    t,i,n,k,p,q,root:longint;
Procedure dfs(x:longint);
var
    i,m,j,l,y:longint;
begin
    for i:=1 to d[x] do
      begin
        dfs(g[x,i]);
        width[x]:=width[x]+width[g[x,i]];
      end;
    fillchar(b,sizeof(b),0);
    for i:=1 to d[x] do
      begin
        y:=g[x,i];
        for j:=k downto 0 do
          begin
            m:=maxlongint;
            for l:=0 to j do
              if m>opt[y,l]+b[j-l] then m:=opt[y,l]+b[j-l];
            b[j]:=m;
          end;
      end;
    for i:=0 to k do
      opt[x,i]:=b[i];
    j:=opt[x,0];
    opt[x,0]:=opt[x,0]+width[x]*height[x];
    if opt[x,1]>j then opt[x,1]:=j;
end;
Begin
    readln(n,k);
    for i:=1 to n do
      readln(a[i]);
    t:=0;
    p:=0;
    fillchar(f,sizeof(f),0);
    fillchar(w,sizeof(w),0);
    for i:=1 to n do
      begin
        while (t>0)and(a[i]<s[t]) do
          begin
            height[c[t]]:=s[t];
            width[c[t]]:=w[t];
            if (t>1)and(a[i]<=s[t-1]) then
              begin
                f[c[t]]:=c[t-1];
                height[c[t]]:=height[c[t]]-s[t-1];
              end
            else
              begin
                f[c[t]]:=p+1;
                height[c[t]]:=height[c[t]]-a[i];
              end;
            dec(t);
          end;
        if (t>0)and(s[t]=a[i]) then
          inc(w[t])
        else
          begin
            inc(t);
            inc(p);
            c[t]:=p;
            s[t]:=a[i];
            w[t]:=1;
          end;
      end;
    while t>0 do
      begin
        height[c[t]]:=s[t];
        width[c[t]]:=w[t];
        if t>1 then
          begin
            height[c[t]]:=height[c[t]]-s[t-1];
            f[c[t]]:=c[t-1];
          end
        else
          begin
            f[c[t]]:=0;
            root:=c[t];
          end;
        dec(t);
      end;
    fillchar(d,sizeof(d),0);
    for i:=1 to p do
      if f[i]>0 then
        begin
          inc(d[f[i]]);
          g[f[i],d[f[i]]]:=i;
        end;
    fillchar(opt,sizeof(opt),0);
    dfs(root);
    t:=maxlongint;
    for i:=0 to k do
      if opt[root,i]<t then t:=opt[root,i];
    writeln(t);
End.
