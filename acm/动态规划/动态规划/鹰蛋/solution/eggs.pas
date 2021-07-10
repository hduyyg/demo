var f:array[1..20,1..1000]of longint;
    i,j,k,m,n:longint;

function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;

begin
  assign(input,'eggs.in');
  reset(input);
  assign(output,'eggs.out');
  rewrite(output);
  readln(m,n);
  if m>20 then m:=20;
  for i:=1 to m do f[i,1]:=1;
  for i:=1 to n do f[1,i]:=i;
  for i:=2 to m do
    for j:=2 to n do
      begin
        f[i,j]:=f[i-1,j];
        for k:=1 to j-2 do
          if max(f[i-1,k]+1,f[i,j-k-1]+1)<f[i,j] then
            f[i,j]:=max(f[i-1,k]+1,f[i,j-k-1]+1);
       end;
  writeln(f[m,n]);
  close(input);
  close(output);
end.
