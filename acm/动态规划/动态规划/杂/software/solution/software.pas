program software(input,output);
var
  n,m:longint;
  w:array[0..100,1..2] of longint;
  i,j,k:longint;
  a,b,max,out:longint;

  function check(total:longint):boolean;
  var
    f:array[0..100,0..100] of longint;
    i,j,k:longint;
    all:longint;
    begin
      fillchar(f,sizeof(f),0);
      for i:=0 to n do
        for j:=1 to m do
          f[i,j]:=-maxint;
      for i:=1 to n do
        begin
          all:=total div w[i,1];
          for j:=0 to m do
            for k:=0 to all do
              begin
                if k>j then
                  break;
                if f[i,j]<f[i-1,j-k]+(total-k*w[i,1]) div w[i,2] then
                  f[i,j]:=f[i-1,j-k]+(total-k*w[i,1]) div w[i,2];
              end;
        end;
      if f[n,m]>=m
        then
          exit(true)
        else
          exit(false);
    end;

begin
  assign(input,'software.in');
  reset(input);
  assign(output,'software.out');
  rewrite(output);
  a:=0;
  b:=0;
  readln(n,m);
  for i:=1 to n do
    begin
      read(w[i,1],w[i,2]);
      if w[i,1]>a then
        a:=w[i,1];
      if w[i,2]>b then
        b:=w[i,2];
    end;
  close(input);
  out:=1;
  max:=(m*(a+b)) div n+3;
  i:=1;
  j:=max;
  while i<=j do
    begin
      k:=(i+j) div 2;
      if check(k)
        then
          begin
            j:=k-1;
            out:=k;
          end
        else
          i:=k+1;
    end;
  writeln(out);
  close(output);
end.