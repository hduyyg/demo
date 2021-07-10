program  tower;
var  a,f:array [1..10,1..10] of integer;
     i,j,n,max:integer;
begin
  assign(input,'tower.in');reset(input);
  assign(output,'tower.out');rewrite(output);
  readln(n);
  for i:=1 to n do
  for j:=1 to i do
  read(a[i,j]);
  f[1,1]:=a[1,1]; 
  for i:=2 to n do 
    begin 
      f[i,1]:=f[i-1,1]+a[i,1]; // 第一行 
      f[i,i]:=f[i-1,i-1]+a[i,i]; // 斜边 
      for j:=2 to i-1 do // 中间部分 
        if f[i-1,j-1]>f[i-1,j] then 
             f[i,j]:=f[i-1,j-1]+a[i,j] 
        else f[i,j]:=f[i-1,j]+a[i,j]; 
    end; 
  max:=0;
  for i:=1 to n do
    if f[n,i]>max then max:=f[n,i];
  writeln('max=',max);
  close(input);close(output);
end.
