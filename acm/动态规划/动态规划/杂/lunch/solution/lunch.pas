program lunch;
var d,f:array[0..40000]of longint;
    s:array[1..201,1..2]of longint;
    n,i,j,r,ans:longint;
function max(x,y:longint):longint;
begin
  if x>y then max:=x else max:=y;
end;
procedure as(k,s:longint);
begin
  if s<d[k] then d[k]:=s;
end;
begin
  assign(input,'lunch.in');reset(input);
  assign(output,'lunch.out');rewrite(output);
  fillchar(d,sizeof(d),$7F);
  readln(n);
  for i:=1 to n do
    readln(s[i,1],s[i,2]);
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if s[i,2]<s[j,2] then
      begin
        s[201]:=s[i];
        s[i]:=s[j];
        s[j]:=s[201];
      end;
  r:=0;
  d[0]:=0;
  for i:=1 to n do
  begin
    f:=d;
    fillchar(d,sizeof(d),$7F);
    for j:=0 to r do
      if f[j]<10000000 then
      begin
        as(j+s[i,1],max(f[j],j+s[i,1]+s[i,2]));
        as(j,max(f[j],r-j+s[i,1]+s[i,2]));
      end;
    inc(r,s[i,1]);
  end;
  ans:=maxlongint;
  for i:=0 to r do
    if d[i]<ans then ans:=d[i];
  writeln(ans);
  close(input);
  close(output);
end.







