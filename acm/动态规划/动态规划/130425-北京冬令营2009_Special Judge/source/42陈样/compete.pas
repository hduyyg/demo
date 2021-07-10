program compete;
uses math;
const
  zero=1e-6;
var
  n,l,i,j,k:longint;
  getx,gety:array[0..20] of boolean;
  link,vx,vy:array[0..20] of longint;
  fx,fy:array[0..20] of extended;
  g:array[0..20,0..20] of extended;
  ans,d:extended;
//==================================
procedure check;
var
  i,j,t:longint;
begin
  for j:=1 to n do
  if link[j]>0 then
  for i:=j+1 to n do
  if link[i]>0 then
  if vx[link[i]]>vx[link[j]]+l then
  begin
    t:=link[i];
    link[i]:=link[j];
    link[j]:=t;
  end;
end;
//==================================
function find(x:longint):boolean;
var
  y:longint;
begin
  getx[x]:=true;
  for y:=1 to n do
  if (not gety[y])and(fx[x]+fy[y]-g[x,y]<=zero) then
  begin
    gety[y]:=true;
    if (link[y]=0) or find(link[y]) then
    begin
      link[y]:=x;
      exit(true);
    end;
  end;
  exit(false);
end;
//==================================
begin
  assign(input,'compete.in'); reset(input);
  assign(output,'compete.out'); rewrite(output);
  read(n);
  for i:=1 to n do read(vx[i]);
  for i:=1 to n do read(vy[i]);
  read(l);
  for i:=1 to n do
  for j:=1 to n do
  begin
    g[i,j]:=1/(1+10**((vy[j]-vx[i])/400));
    if fx[i]<g[i,j] then fx[i]:=g[i,j];
  end;
  for i:=1 to n do
  while true do
  begin
    fillchar(getx,sizeof(getx),false);
    fillchar(gety,sizeof(gety),false);
    if find(i) then break;
    d:=-maxlongint;
    for k:=1 to n do
    if getx[k] then
    for j:=1 to n do
    if not gety[j] and (d<fx[k]+fy[j]-g[k,j]) then d:=fx[k]+fy[j]-g[k,j];
    for k:=1 to n do
    begin
      if getx[k] then fx[k]:=fx[k]-d;
      if gety[k] then fy[k]:=fy[k]+d;
    end;
  end;
  check;
  for i:=1 to n do ans:=ans+g[link[i],i];
  //for i:=1 to n do writeln(link[i]);
  writeln(ans:0:6);
  close(input); close(output);
end.

