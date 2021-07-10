program service;
var w,s,t:array[1..500,1..500]of longint;
    d:array[0..250,0..500]of longint;
    a:array[1..500,1..3]of longint;
    n,m,i,j,k,v,r:longint;
begin
  assign(input,'service.in');reset(input);
  assign(output,'service.out');rewrite(output);
  fillchar(w,sizeof(w),$7F);
  fillchar(s,sizeof(s),0);
  fillchar(t,sizeof(t),0);
  fillchar(d,sizeof(d),$7F);
  readln(n,m);
  for i:=1 to n do
    for j:=1 to 3 do
      read(a[i,j]);
  for i:=1 to n do
  begin
    r:=0;
    for j:=i+1 to n do
    begin
      inc(r,a[j-1,2]);
      s[i,j]:=s[i,j-1]+r*(a[j,1]-a[j-1,1]);
    end;
  end;
  for i:=n downto 1 do
  begin
    r:=0;
    for j:=i-1 downto 1 do
    begin
      inc(r,a[j+1,2]);
      t[j,i]:=t[j+1,i]+r*(a[j+1,1]-a[j,1]);
    end;
  end;
  for i:=1 to n do
  begin
    r:=i;
    for j:=i to n do
      for k:=r to j do
        if s[i,k]+t[k,j]+a[k,3]<w[i,j] then
        begin
          w[i,j]:=s[i,k]+t[k,j]+a[k,3];
          r:=k;
        end;
  end;
  d[0,0]:=0;
  v:=maxlongint;
  for i:=1 to m do
  begin
    for j:=i to n do
    begin
      r:=i-1;
      for k:=r to j-1 do
        if (d[i-1,k]<1000000) and (d[i-1,k]+w[k+1,j]<d[i,j]) then
        begin
          d[i,j]:=d[i-1,k]+w[k+1,j];
          r:=k;
        end;
    end;
    if d[i,n]<v then v:=d[i,n];
  end;
  writeln(v);
  close(input);
  close(output);
end.

