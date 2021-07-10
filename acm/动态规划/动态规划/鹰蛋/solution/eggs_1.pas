var a:array[0..1000,0..1000] of longint;
    i,m,n,j:longint;
    t:boolean;
procedure inp;
  begin
    assign(input,'eggs.in');
    assign(output,'eggs.out');
    reset(input);
    rewrite(output);
  end;
procedure outp;
  begin
    close(input);
    close(output);
  end;
begin
  inp;
  readln(m,n);
  if m>n then m:=n;
  a[1,1]:=1;
  j:=0;
  t:=true;
  while t do
    begin
      inc(j);
      for i:=1 to m do
        a[i,j]:=a[i-1,j-1]+a[i,j-1]+1;
      if a[m,j]>=n then t:=false;
    end;
  writeln(j);
  outp;
end.
