program tinux;
var d:array[1..1000,1..150]of longint;
    f:array[0..1000]of longint;
    s:array[1..150]of longint;
    n,m,i,j,k,r,v:longint;
begin
  assign(input,'tinux.in');reset(input);
  assign(output,'tinux.out');rewrite(output);
  fillchar(d,sizeof(d),$7F);
  fillchar(f,sizeof(f),$7F);
  readln(n,m);
  for i:=1 to m do
    readln(s[i]);
  for i:=1 to m-1 do
    for j:=i+1 to m do
      if s[i]>s[j] then
      begin
        k:=s[i];
        s[i]:=s[j];
        s[j]:=k;
      end;
  for i:=1 to m do
    d[1,i]:=s[i];
  f[0]:=0;
  f[1]:=s[1];
  for i:=2 to n do
  begin
    v:=i-1;
    for j:=2 to m do
      for k:=v downto 0 do
      begin
        if k=1 then r:=s[j] else r:=s[j]*k*k+f[k];
        if d[i-k,j-1]+r<d[i,j] then
        begin
          d[i,j]:=d[i-k,j-1]+r;
          v:=k;
        end;
      end;
    f[i]:=d[i,m];
    d[i,1]:=s[1]*i*i+f[i];
  end;
  writeln(f[n]);
  close(input);
  close(output);
end.






