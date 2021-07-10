var
  max,temp:array[0..200,0..200] of integer;
  up,down:array[0..200] of integer;
  a,b,c,d,e,m,n:integer;
begin
  fillchar(max,sizeof(max),0);
  fillchar(temp,sizeof(temp),0);
  fillchar(up,sizeof(up),0);
  fillchar(down,sizeof(down),0);
  assign(input,'cross.dat');
  reset(input);
  assign(output,'cross.out');
  rewrite(output);
  readln(n,m);
  for a:=1 to n do read(up[a]);
  for a:=1 to m do read(down[a]);
  for a:=1 to n do
    for b:=1 to m do
      if up[a]=down[b] then temp[a][b]:=b else temp[a][b]:=temp[a][b-1];
  for a:=2 to n do
    for b:=2 to m do begin
      if up[a]<>down[b] then
        for c:=a-1 downto 1 do
          if (up[c]=down[b]) and (temp[a][b-1]>0) then
            if up[a]=down[temp[a][b-1]] then
              if max[a][b]<max[c-1][temp[a][b-1]-1]+2 then max[a][b]:=max[c-1][temp[a][b-1]-1]+2;
      if max[a][b]<max[a-1][b] then max[a][b]:=max[a-1][b];
      if max[a][b]<max[a][b-1] then max[a][b]:=max[a][b-1];
    end;
  writeln(max[n][m]);
  close(input);
  close(output);
end.
