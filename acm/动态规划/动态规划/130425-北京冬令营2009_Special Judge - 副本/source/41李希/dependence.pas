type
  arr=array[0..100]of boolean;
var
  m,n,i,j,k,l,num:longint;
  st:string;
  f:array[0..100,0..100]of boolean;
  str:array[0..10000]of string;
  s:array[0..100]of longint;
  v,ele:arr;
  
procedure terminate;
begin
  close(input);
  close(output);
end;
  
procedure work;
var
  x,y:longint;
begin
  l:=length(st);
  if l<>4 then
  begin
    writeln('No candidate key');
    terminate; halt;
  end;
  x:=ord(st[1])-64;
  y:=ord(st[l])-64;
  f[x,y]:=true;
end;

procedure readdata;
begin
  readln(n,m);
  fillchar(f,sizeof(f),0);
  for i:=1 to n do  f[i,i]:=true;
  for i:=1 to m do
  begin
    readln(st);
    work
  end;
end;

procedure floyed;
begin
  for k:=1 to n do
  for i:=1 to n do
  for j:=1 to n do
  if (f[i,k])and(f[k,j]) then f[i,j]:=true;
end;

procedure zengjia(st:string);
begin
  inc(num);
  str[num]:=st;
end;

procedure dfs(last,sum:longint; ele:arr; st:string);
var
  i,j,ss:longint;
  x:arr;
  strr:string;
begin
  for i:=last+1 to n do
  if v[i] then
  begin
    x:=ele;
    ss:=sum;
    strr:=st;
    for j:=1 to n do
    if (not x[j])and(f[i,j]) then
    begin
      x[j]:=true;
      inc(ss);
    end;
    strr:=strr+chr(i+64);
    if ss=n
      then zengjia(strr)
      else if ss<>sum then dfs(i,ss,x,strr);
  end;
end;

procedure main;
begin
  floyed;
  fillchar(v,sizeof(v),0);
  for i:=1 to n do s[i]:=n;
  for i:=1 to n do
  for j:=1 to n do
  if not f[i,j] then
  begin
    v[i]:=true;
    dec(s[i]);
  end;

  num:=0;
  for i:=1 to n do
  begin
    if not v[i] then
    begin
      inc(num);
      str[num]:=chr(i+64);
    end
    else begin
      ele:=f[i];
      st:=chr(i+64);
      dfs(i,s[i],ele,st);
    end;
  end;
  if num=0
  then writeln('No candidate key')
  else begin
    writeln(num);
    for i:=1 to num do
    writeln(str[i]);
  end;
end;


begin
  assign(input,'dependence.in');
  assign(output,'dependence.out');
  reset(input);
  rewrite(output);
  
  readdata;
  main;
  
  close(input);
  close(output);
end.

