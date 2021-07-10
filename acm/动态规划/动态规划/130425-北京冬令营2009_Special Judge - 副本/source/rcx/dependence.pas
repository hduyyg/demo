program dependence;
var
  two:array[1..11]of longint;
  map:array[1..2048,1..2048]of boolean;
  a:array[1..2048]of string;
  ok,can:array[1..2048]of boolean;
  n,m,i,j,x,y,tot:longint;
  z:char;
  mid:string;
  
begin
  assign(input,'dependence.in');reset(input);
  assign(output,'dependence.out');rewrite(output);
  readln(n,m);
  two[1]:=1;
  for i:=2 to 11 do two[i]:=two[i-1]*2;
  fillchar(map,sizeof(map),false);
  for i:=1 to m do begin
    read(z);
    x:=0;
    while z in['A'..'Z'] do begin
      x:=x or two[ord(z)-64];
      read(z);
    end;
    read(z);
    y:=0;
    while not eoln do begin
      read(z);
      y:=y or two[ord(z)-64];
    end;
    readln;
    for j:=1 to two[n+1]-1 do if j and x=x then map[j,j or y]:=true;
  end;
  fillchar(ok,sizeof(ok),false);
  fillchar(can,sizeof(can),false);
  ok[two[n+1]-1]:=true;can[two[n+1]-1]:=true;
  for i:=two[n+1]-2 downto 1 do begin
    for j:=i+1 to two[n+1]-1 do if (map[i,j])and(ok[j])then begin
      ok[i]:=true;can[i]:=true;
      break;
    end;
    if ok[i] then for j:=i+1 to two[n+1]-1 do if j and i=i then can[j]:=false;
  end;
  tot:=0;
  for i:=1 to two[n+1]-1 do if ok[i] and can[i] then begin
    inc(tot);
    a[tot]:='';
    for j:=1 to n do if two[j]and i<>0 then a[tot]:=a[tot]+chr(j+64);
  end;
  for i:=1 to tot-1 do
    for j:=i+1 to tot do
      if a[i]>a[j] then begin
        mid:=a[i];a[i]:=a[j];a[j]:=mid;
      end;
  writeln(tot);
  for i:=1 to tot do writeln(a[i]);
  close(input);close(output);
end.
      
  
  

