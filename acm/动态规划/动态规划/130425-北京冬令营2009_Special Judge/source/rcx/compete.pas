program compete;
const
  small=1e-10;
var
  f:array[0..1048576]of extended;
  a,b:array[1..20]of longint;
  two:array[1..21]of longint;
  map:array[1..20,1..20]of extended;
  n,i,j,max,num,mid,l:longint;
  
begin
  assign(input,'compete.in');reset(input);
  assign(output,'compete.out');rewrite(output);
  read(n);
  two[1]:=1;
  for i:=2 to 21 do two[i]:=two[i-1]*2;
  for i:=1 to n do read(a[i]);
  for i:=1 to n do read(b[i]);
  read(l);
  for i:=1 to n-1 do
    for j:=i+1 to n do if a[i]<a[j] then begin
      mid:=a[i];a[i]:=a[j];a[j]:=mid;
    end;
  for i:=1 to n do
    for j:=1 to n do
      map[i,j]:=1/(1+exp((b[j]-a[i])/400*ln(10)));
  fillchar(f,sizeof(f),0);
  for i:=0 to two[n+1]-2 do if (i=0)or(f[i]>small)then begin
    max:=0;
    num:=n;
    for j:=1 to n do if two[j]and i=0 then begin
      if max=0 then max:=j;
      dec(num);
    end;
    for j:=1 to n do if two[j]and i=0 then begin
      if a[max]-a[j]>l then break;
      if f[i]+map[j,num+1]>f[i+two[j]] then f[i+two[j]]:=f[i]+map[j,num+1];
    end;
  end;
  writeln(f[two[n+1]-1]:0:6);
  close(input);close(output);
end.
      

      
      
  

