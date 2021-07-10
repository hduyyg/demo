program dependence;
type
  ty=set of 'A'..'N';
var
  n,m,i,j,tot,k:longint;
  ok:array[0..1000] of boolean;
  s:array[0..1000] of ansistring;
  p:array[0..1000] of longint;
  ans:array[0..1000] of ty;
//===============================
procedure ans_get(t:ty);
var
  k:ty;
  i,j:longint;
  can_p:boolean;
  can:boolean;
begin
  can:=true; k:=t;
  while can do
  begin
    can:=false;
    for i:=1 to m do
    begin
      can_p:=true;
      for j:=1 to p[i]-1 do
      if not(s[i][j] in k) then
      begin
        can_p:=false;
        break;
      end;
      if not can_p then continue;
      for j:=p[i]+2 to length(s[i]) do
      if not(s[i][j] in k) then
      begin
        can:=true;
        k:=k+[s[i][j]];
      end;
    end;
  end;
  for i:=1 to n do
  if not(chr(i+64) in k) then exit;
  inc(tot); ans[tot]:=t;
end;
//===============================
procedure find(x:longint; t:ty);
begin
  if x=n+1 then
  begin
    ans_get(t);
    exit;
  end;
  find(x+1,t);
  find(x+1,t+[chr(x+64)]);
end;
//===============================
begin
  assign(input,'dependence.in'); reset(input);
  assign(output,'dependence.out'); rewrite(output);
  readln(n,m);
  for i:=1 to m do
  begin
    readln(s[i]);
    while pos(' ',s[i])>0 do delete(s[i],pos(' ',s[i]),1);
    p[i]:=pos('-',s[i]);
  end;
  find(1,[]);
  fillchar(ok,sizeof(ok),true);
  for i:=tot downto 1 do
  if ok[i] then
  for j:=i-1 downto 1 do
  if ans[j]+ans[i]=ans[i] then ok[i]:=false;
  k:=0;
  for i:=tot downto 1 do
  if ok[i] then inc(k);
  writeln(k);
  for i:=tot downto 1 do
  if ok[i] then
  begin
    for j:=1 to n do
    if chr(j+64) in ans[i] then write(chr(j+64));
    writeln;
  end;
  if k=0 then writeln('No candidate key');
  close(input); close(output);
end.

