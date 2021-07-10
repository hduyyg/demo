program incsq;
const v:array['0'..'9']of longint=(0,1,2,3,4,5,6,7,8,9);
var d:array[0..80,0..80,0..80]of boolean;
    s:array[0..80]of longint;
    n,i,j:longint;
    c:string;
function at(x,y,p,q:longint):boolean;
var i:longint;
begin
  while (x<y) and (s[x]=0) do
    inc(x);
  while (p<q) and (s[p]=0) do
    inc(p);
  if y-x<q-p then exit(true) else if y-x>q-p then exit(false);
  for i:=0 to y-x do
    if s[x+i]<s[p+i] then exit(true) else if s[x+i]>s[p+i] then exit(false);
  at:=false;
end;
function as(x,y,k:longint):boolean;
var i:longint;
begin
  if not(d[x,y,k]) then exit(false);
  if y=k-1 then exit(true);
  for i:=k-1 downto y+1 do
    if at(x,y,y+1,i) and at(y+1,i,k,n) then
      if as(y+1,i,k) then
      begin
        insert(',',c,i+1);
        exit(true);
      end;
  d[x,y,k]:=false;
  as:=false;
end;
begin
  assign(input,'incsq.in');reset(input);
  assign(output,'incsq.out');rewrite(output);
  fillchar(d,sizeof(d),true);
  fillchar(s,sizeof(s),0);
  readln(c);
  n:=length(c);
  for i:=1 to n do
    s[i]:=v[c[i]];
  for i:=n downto 1 do
    if as(0,0,i) then break;
  writeln(c);
  close(input);
  close(output);
end.
