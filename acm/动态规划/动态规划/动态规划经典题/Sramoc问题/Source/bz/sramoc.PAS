var
  min:array[0..30,0..9,0..1000] of byte;
  modn:array[0..100,0..9] of integer;
  a,b,c,d,n,m,k:integer;
  find:boolean;
begin
  fillchar(min,sizeof(min),10);
  assign(input,'sramoc.in');
  reset(input);
  assign(output,'sramoc.out');
  rewrite(output);
  readln(k,m);
  n:=1;
  find:=false;
  for a:=0 to k-1 do begin
    modn[n][a]:=a mod m;
    min[n][a][a mod m]:=0;
    if (a mod m=0) and (a>0) then begin
      find:=true;
      d:=a;
      c:=0;
      break;
    end;
  end;
  while not find do begin
    inc(n);
    for a:=0 to k-1 do begin
      modn[n][a]:=(modn[n-1][a]*10) mod m;
      for b:=0 to m-1 do begin
        d:=(b-modn[n][a]+m) mod m;
        for c:=0 to k-1 do
          if min[n-1][c][d]<10 then begin
            min[n][a][b]:=c;
            break;
          end;
        if (b=0) and (a>0) then
          if min[n][a][0]<10 then begin
            d:=a;
            c:=0;
            find:=true;
            break;
          end;
      end;
      if find then break;
    end;
  end;
  for a:=n downto 1 do begin
    write(d);
    b:=m-modn[a][d];
    d:=min[a][d][c];
    c:=(b+c) mod m;
  end;
  writeln;
  close(input);
  close(output);
end.
