Program ex7;
Const
    maxn=200;
    maxk=200;
Var
    opt:array[1..maxn,0..maxk+2,0..1]of longint;
    g:array[1..maxn,0..maxn]of longint;
    a:array[1..maxn]of longint;
    v:array[1..maxn]of boolean;
    b,s:array[0..maxn+1,0..maxk+2]of longint;
    temp:array[0..maxk+2]of longint;
    i,n,k,x,y:longint;
Procedure dfs(x:longint);
var
    i,j,l,f:longint;
function max(x,y:longint):longint;
var
    z:longint;
begin
    z:=x;
    if z<y then z:=y;
    max:=z;
end;
begin
    v[x]:=true;
    f:=0;
    for i:=1 to g[x,0] do
      if not v[g[x,i]] then
        begin
          dfs(g[x,i]);
          f:=1;
        end;
    if f=0 then
      begin
        for i:=1 to (k+2) shr 1 do
          opt[x,i shl 1,0]:=a[x];
        for i:=1 to k+1 do
          opt[x,i,1]:=a[x];
        exit;
      end;
    fillchar(b,sizeof(b),0);
    fillchar(s,sizeof(s),0);
    for i:=1 to g[x,0] do
      for j:=0 to k shr 1 do
        for l:=k shr 1 downto j do
          if b[i-1,(l-j)shl 1]+opt[g[x,i],j shl 1,0]>b[i,l shl 1] then
            b[i,l shl 1]:=b[i-1,(l-j)shl 1]+opt[g[x,i],j shl 1,0];
    for i:=1 to (k+2)shr 1 do
      opt[x,i shl 1,0]:=max(b[g[x,0],(i-1)shl 1],opt[x,(i-1)shl 1,0]);
    for i:=1 to (k+2)shr 1 do
      opt[x,i shl 1,0]:=opt[x,i shl 1,0]+a[x];
    for i:=g[x,0] downto 1 do
      for j:=0 to k shr 1 do
        for l:=k shr 1 downto j do
          if s[i+1,(l-j)shl 1]+opt[g[x,i],j shl 1,0]>s[i,l shl 1] then
            s[i,l shl 1]:=s[i+1,(l-j)shl 1]+opt[g[x,i],j shl 1,0];
    for i:=1 to g[x,0] do
      begin
        fillchar(temp,sizeof(temp),0);
        for j:=0 to (k+2)shr 1 do
          for l:=0 to j do
            if s[i+1,(j-l)shl 1]<>-1 then
              if temp[j shl 1]<b[i-1,l shl 1]+s[i+1,(j-l)shl 1] then temp[j shl 1]:=b[i-1,l shl 1]+s[i+1,(j-l)shl 1];
        for j:=1 to k+2 do
          for l:=0 to (j-1)shr 1 do
            if opt[x,j,1]<temp[l shl 1]+opt[g[x,i],j-l shl 1,1] then
              opt[x,j,1]:=temp[l shl 1]+opt[g[x,i],j-l shl 1,1];
      end;
    for i:=k+2 downto 1 do
      opt[x,i,1]:=opt[x,i-1,1];
    for i:=1 to k+2 do
      opt[x,i,1]:=max(opt[x,i,1],opt[x,i-1,1]);
    for i:=1 to k+2 do
      opt[x,i,1]:=opt[x,i,1]+a[x];
end;
Begin
    while not seekeof do
      begin
        readln(n,k);
        fillchar(g,sizeof(g),0);
        fillchar(v,sizeof(v),false);
        for i:=1 to n do
          read(a[i]);
        for i:=1 to n-1 do
          begin
            readln(x,y);
            inc(g[x,0]);
            g[x,g[x,0]]:=y;
            inc(g[y,0]);
            g[y,g[y,0]]:=x;
          end;
        fillchar(opt,sizeof(opt),0);
        dfs(1);
        writeln(opt[1,k+1,1]);
      end;
End.
