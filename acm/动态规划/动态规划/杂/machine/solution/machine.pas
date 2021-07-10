program machine(input,output);
const
  maxn=80;

var
  a,b:array[1..3,1..maxn,1..maxn] of string[maxn];
  f:array[0..maxn,1..2] of string;
  out:array[0..100] of shortint;
  i,j,k,l:longint;
  n:longint;
  now:string;

begin
  assign(input,'machine.in');
  reset(input);
  assign(output,'machine.out');
  rewrite(output);

  for i:=1 to 3 do
    for j:=1 to maxn do
      for k:=1 to maxn do
        begin
          a[i,j,k]:='';
          b[i,j,k]:='';
        end;
  readln(n);
  for i:=1 to 3 do
    begin
      readln(a[i,1,n]);
      for j:=1 to n do
        for k:=j to n do
          begin
            a[i,j,k]:=copy(a[i,1,n],j,k-j+1);
            for l:=1 to k-j+1 do
              b[i,j,k]:=a[i,j,k][l]+b[i,j,k];
          end;
    end;

  close(input);

  for i:=0 to n do
    begin
      f[i,1]:='';
      f[i,2]:='';
    end;
  for i:=1 to n do
    begin
      f[i,1]:=f[i-1,2]+a[3,i,i]+b[2,i,i]+a[1,i,i];
      for j:=1 to i-1 do
        begin
          now:=f[j-1,2]+a[3,j,i]+b[2,j,i]+a[1,j,i];
          if now>f[i,1] then
            f[i,1]:=now;
        end;
      f[i,2]:=f[i-1,1]+a[1,i,i]+b[2,i,i]+a[3,i,i];
      for j:=1 to i-1 do
        begin
          now:=f[j-1,1]+a[1,j,i]+b[2,j,i]+a[3,j,i];
          if now>f[i,2] then
            f[i,2]:=now;
        end;
    end;

  if f[n,1]<f[n,2] then
    f[n,1]:=f[n,2];

  fillchar(out,sizeof(out),0);
  out[0]:=1;
  out[1]:=ord(f[n,1][1])-48;
  for i:=2 to n+n+n do
    begin
      for j:=1 to out[0] do
        inc(out[j],out[j]);
      for j:=1 to out[0] do
        if out[j]>=10 then
          begin
            dec(out[j],10);
            inc(out[j+1]);
          end;
      if out[out[0]+1]>0 then
        inc(out[0]);
      if f[n,1][i]='1' then
        inc(out[1]);
    end;

  for i:=out[0] downto 1 do
    write(out[i]);
  writeln;

  close(output);
end.
