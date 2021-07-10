program mole;
var d,t,w:array[0..10001]of longint;
    r:array[0..10001,1..3]of longint;
    n,i,j,s:longint;
procedure as(k:longint);
var i,j:longint;
    f:boolean;
begin
  d[k]:=1;
  f:=false;
  for i:=s downto 1 do
  begin
    j:=t[i];
    while j<>0 do
    begin
      if r[j,1]-r[k,1]>=abs(r[j,2]-r[k,2])+abs(r[j,3]-r[k,3]) then
      begin
        d[k]:=i+1;
        f:=true;
        break;
      end;
      j:=w[j];
    end;
    if f then break;
  end;
  if d[k]>s then s:=d[k];
  w[k]:=t[d[k]];
  t[d[k]]:=k;
end;
begin
  assign(input,'mole.in');reset(input);
  assign(output,'mole.out');rewrite(output);
  fillchar(d,sizeof(d),0);
  fillchar(w,sizeof(w),0);
  fillchar(t,sizeof(t),0);
  readln(n,n);
  r[1,1]:=-10000;
  r[1,2]:=1;
  r[1,3]:=1;
  inc(n);
  for i:=2 to n do
  begin
    for j:=1 to 3 do
      read(r[i,j]);
  end;
  s:=1;
  for i:=n downto 1 do
    as(i);
  writeln(d[1]-1);
  close(input);
  close(output);
end.


