program software;
var d,f,w:array[0..100,0..100]of longint;
    r:array[1..100,1..2]of longint;
    n,m,s,t,i,j,k,x,y,p,q,v:longint;
function min(x,y:longint):longint;
begin
  if x<y then min:=x else min:=y;
end;
function max(x,y:longint):longint;
begin
  if x>y then max:=x else max:=y;
end;
begin
  assign(input,'software.in');reset(input);
  assign(output,'software.out');rewrite(output);
  fillchar(d,sizeof(d),$7F);
  d[0,0]:=0;
  readln(n,m);
  s:=0;
  t:=maxlongint;
  for i:=1 to n do
  begin
    readln(r[i,1],r[i,2]);
    if (r[i,1]+r[i,2])*((m div n)+1)>s then s:=(r[i,1]+r[i,2])*((m div n)+1);
  end;
  t:=0;
  for i:=1 to n do
  begin
    f:=d;
    x:=r[i,1];
    y:=r[i,2];
    for j:=0 to min(s div x,m) do
      for k:=max((t-j*x) div y,0) to min((s-j*x) div y,m) do
        w[j,k]:=j*x+k*y;
    for p:=0 to m do
      for q:=0 to m do
        if f[p,q]<1000000 then
          for j:=0 to min(s div x,m-p) do
            for k:=max(0,(t-j*x) div y) to min((s-j*x) div y,m-q) do
            begin
              v:=max(f[p,q],w[j,k]);
              if v<d[p+j,q+k] then d[p+j,q+k]:=v;
            end;
    if d[m,m]<s then s:=d[m,m];
  end;
  writeln(d[m,m]);
  close(input);
  close(output);
end.








