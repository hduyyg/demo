program dependence;

type
g=record
len1,len2:longint;
l,r:array[0..11]of longint;
end;

const
num:array[1..10] of char=('A','B','C','D','E','F','G','H','I','J');
ex:array['A'..'J'] of longint=(1,2,3,4,5,6,7,8,9,10);

var
i,j,k,n,m,tot,top,ans,t:longint;
link:array[0..1005] of g;
s:ansistring;
que:array[0..15] of longint;
re:array[0..2000,0..10] of longint;
used:array[0..15] of boolean;
color:array[0..1500] of boolean;

procedure ter;
begin
 close(input);close(output);
 halt;
end;

procedure jilu;
var
i:longint;
begin
 inc(tot);
 re[tot][0]:=top;
 for i:=1 to top do
  re[tot][i]:=que[i];
end;

procedure find;
var
i,j,k:Longint;
can:boolean;
begin
fillchar(used,sizeof(used),0);
fillchar(color,sizeof(color),0);
 for i:=1 to top do
  used[que[i]]:=true;
t:=top;
k:=1;
while (k>0) and (t<n) do
begin
k:=0;
 for i:=1 to m do
 if not color[i] then
  begin
   can:=true;
   for j:=1 to link[i].len1 do
    if not used[link[i].l[j]] then
     begin
      can:=false;
      break;
     end;
   if can then
    begin
     color[i]:=true;
     for j:=1 to link[i].len2 do
      if not used[link[i].r[j]] then
       begin
       inc(k);
       used[link[i].r[j]]:=true;
       inc(t);
       end;
    end;
  end;
end;
end;


procedure dfs;
var
i:longint;
begin
 for i:=que[top]+1 to n do
  begin
   inc(top);
   que[top]:=i;
   find;
   if t=n then
    jilu
    else
    dfs;
   dec(top);
  end;
end;


function same(a,b:longint):boolean;
var
i,j,k:Longint;
begin
if (color[a]) or (color[b]) then exit(false);
fillchar(used,sizeof(used),0);
if re[a][0]<re[b][0] then
 begin
  k:=a;a:=b;b:=k;
 end;
 for i:=1 to re[a][0] do
  used[re[a][i]]:=true;
 for j:=1 to re[b][0] do
  if not used[re[b][j]] then
   exit(false);
exit(true);
end;


procedure doing;
var
i,j:longint;
begin
 ans:=tot;
 fillchar(color,sizeof(color),0);
 for i:=1 to tot do
 if not color[i] then
  begin
   for j:=i+1 to tot do
    if not color[j] then
    begin
     if color[i] then break;
     if same(i,j) then
      begin
       dec(ans);
       if re[i][0]>re[j][0] then color[i]:=true
        else color[j]:=true;
      end;
    end;
  end;
end;



begin
assign(input,'dependence.in');
assign(output,'dependence.out');
reset(input);rewrite(output);
readln(n,m);
for i:=1 to m do
 begin
  readln(s);
  k:=pos(' ',s);
  while k>0 do
   begin
    delete(s,k,1);
    k:=pos(' ',s);
   end;
  k:=pos('-',s);
  link[i].len1:=k-1;
  link[i].len2:=length(s)-(k+1);
  for  j:=1 to k-1 do
   link[i].l[j]:=ex[s[j]];
  for j:=k+2 to length(s) do
   link[i].r[j-(k+1)]:=ex[s[j]];
 end;

if n=1 then
 begin
  writeln(1);
  writeln('A');
  ter;
 end;

tot:=0;
for i:=1 to n do
 begin
  top:=1;
  que[1]:=i;
  find;
  if t=n then
   jilu
   else
   dfs;
 end;
if tot=0 then
 writeln('No candidate key');
doing;
writeln(ans);
for i:=1 to tot do
 if not color[i] then
  begin
   for j:=1 to re[i][0] do
    write(num[re[i][j]]);
   writeln;
  end;
ter;
end.

