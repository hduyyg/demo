const
  maxn=100;
var
  a:array[1..maxn] of integer;
  h:array[1..maxn] of integer;
  n,i,j:integer;
begin
  assign(input,'mis.in');reset(input);
  assign(output,'mis.out');rewrite(output);
  read(n);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do
    begin
      h[i]:=1;
      for j:=1 to i-1 do
        if (a[j]>=a[i]) and (h[j]+1>h[i]) then h[i]:=h[j]+1;
    end;
  j:=0;
  for i:=1 to n do
    if h[i]>j then j:=h[i];
  writeln(j);
  for i:=1 to n do
  begin
    h[i]:=1;
    for j:=1 to i-1 do
      if (a[j]<a[i]) and (h[j]+1>h[i]) then h[i]:=h[j]+1;
  end;
  j:=0;
  for i:=1 to n do
    if h[i]>j then j:=h[i];
  writeln(j);
  close(input);
  close(output);
end.