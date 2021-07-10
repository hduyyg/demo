const ef:array[1..17] of longint=(1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536);
var a:array[0..65536,1..16] of longint;
    map:array[1..16,1..16] of longint;
    i,j,n,k,min:longint;
begin
  assign(input,'minsum.in');
  assign(output,'minsum.out');
  reset(input);
  rewrite(output);
  readln(n);
  for i:=1 to n do  for j:=1 to n do
      read(map[i,j]);
  for i:=1 to 65536 do for j:=1 to n do a[i,j]:=1000000;
  for i:=1 to n do
    a[ef[i],i]:=0;
  for i:=0 to ef[n+1]-1 do
    for j:=1 to n do
      if (ef[j] and i<>0) then
    for k:=1 to n do
      if (ef[k] and i=0)and(a[i,j]+map[j,k]<a[i or ef[k],k]) then
        a[i or ef[k],k]:=a[i,j]+map[j,k];
  min:=10000000;
  for i:=1 to n do
    if a[ef[n+1]-1,i]<min then min:=a[ef[n+1]-1,i];
  writeln(min);

  close(input);
  close(output);

end.