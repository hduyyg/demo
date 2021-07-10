program park;
var d:array[0..100,0..6,0..2186]of longint;
    w:array[0..5,0..2186,1..2,1..2]of longint;
    t:array[0..5,0..2186]of longint;
    s:array[1..100,1..6]of longint;
    n,m,e,i,j,k,r,ans:longint;
procedure as(m:longint);
var r,v:array[1..7]of longint;
    i,j:longint;
  function ar(s:longint):boolean;
  var f:array[1..7]of longint;
      i,j:longint;
  begin
    j:=0;
    for i:=m+1 downto 1 do
    begin
      r[i]:=s mod 3;
      s:=s div 3;
    end;
    for i:=1 to m+1 do
      if r[i]=1 then
      begin
        inc(j);
        f[j]:=i;
      end
      else if r[i]=2 then
      begin
        if j=0 then exit(false);
        v[i]:=f[j];
        v[f[j]]:=i;
        dec(j);
      end;
    if j<>0 then exit(false);
    ar:=true;
  end;
  function at(k,x,y:longint):longint;
  var v:array[1..7]of longint;
      i,s:longint;
  begin
    v:=r;
    v[k]:=x;
    v[k+1]:=y;
    s:=0;
    for i:=1 to m+1 do
      s:=s*3+v[i];
    at:=s;
  end;
begin
  for i:=0 to m-1 do
    for j:=0 to e do
    begin
      if not(ar(j)) then continue;
      if (r[i+1]=0) and (r[i+2]=0) then
      begin
        t[i,j]:=2;
        w[i,j,1,1]:=at(i+1,0,0);
        w[i,j,1,2]:=0;
        w[i,j,2,1]:=at(i+1,1,2);
        w[i,j,2,2]:=1;
      end
      else if (r[i+1]=0) or (r[i+2]=0) then
      begin
        t[i,j]:=2;
        w[i,j,1,1]:=at(i+1,r[i+1]+r[i+2],0);
        w[i,j,1,2]:=1;
        w[i,j,2,1]:=at(i+1,0,r[i+1]+r[i+2]);
        w[i,j,2,2]:=1;
      end
      else if (r[i+1]=1) and (r[i+2]=1) then
      begin
        t[i,j]:=1;
        r[v[i+2]]:=1;
        w[i,j,1,1]:=at(i+1,0,0);
        w[i,j,1,2]:=1;
      end
      else if (r[i+1]=2) and (r[i+2]=2) then
      begin
        t[i,j]:=1;
        r[v[i+1]]:=2;
        w[i,j,1,1]:=at(i+1,0,0);
        w[i,j,1,2]:=1;
      end
      else if (r[i+1]=2) and (r[i+2]=1) then
      begin
        t[i,j]:=1;
        w[i,j,1,1]:=at(i+1,0,0);
        w[i,j,1,2]:=1;
      end
      else if at(i+1,0,0)=0 then
      begin
        t[i,j]:=1;
        w[i,j,1,1]:=0;
        w[i,j,1,2]:=1;
      end;
    end;
end;
begin
  assign(input,'park.in');reset(input);
  assign(output,'park.out');rewrite(output);
  fillchar(d,sizeof(d),$F7);
  fillchar(t,sizeof(t),0);
  readln(n,m);
  e:=1;
  for i:=1 to m+1 do
    e:=e*3;
  e:=e-1;
  as(m);
  ans:=-maxlongint;
  for i:=1 to n do
    for j:=1 to m do
      read(s[i,j]);
  for i:=1 to n do
  begin
    for j:=1 to e do
      if j mod 3=0 then d[i,0,j div 3]:=d[i-1,m,j];
    k:=15;
    for j:=m-1 downto 1 do
    begin
      d[i,j,k]:=s[i,j];
      k:=k*3;
    end;
    for j:=0 to m-1 do
    begin
      for k:=1 to e do
        if d[i,j,k]>-100000000 then
          for r:=1 to t[j,k] do
            if d[i,j,k]+s[i,j+1]*w[j,k,r,2]>d[i,j+1,w[j,k,r,1]] then d[i,j+1,w[j,k,r,1]]:=d[i,j,k]+s[i,j+1]*w[j,k,r,2];
      if d[i,j+1,0]>ans then ans:=d[i,j+1,0];
    end;
  end;
  writeln(ans);
  close(input);
  close(output);
end.

