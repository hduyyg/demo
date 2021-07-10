program nule(input,output);
const
  maxn=1000;

var
  n:longint;
  i,j:longint;
  map,f:array[0..maxn,0..maxn,1..2] of longint;
  now,out:longint;

  procedure work(x,y:longint);
  var
    i,j:longint;
    a,b,t:longint;
    begin
      f:=map;
      for i:=1 to n do
        for j:=1 to n do
          if (f[i,j,1]>=0) and ((i<>1) or (j<>1)) then
            begin
              a:=i-1;
              b:=j;
              if (f[i,j-1,1]>=0) and ((f[a,b,1]=-1) or (f[a,b,x]>f[i,j-1,x]) or (f[a,b,x]=f[i,j-1,x]) and (f[a,b,y]>f[i,j-1,y])) then
                begin
                  a:=i;
                  b:=j-1;
                end;
              inc(f[i,j,1],f[a,b,1]);
              inc(f[i,j,2],f[a,b,2]);
            end;
      t:=f[n,n,1];
      if t>f[n,n,2] then
        t:=f[n,n,2];
      if t<out then
        out:=t;
    end;

begin
  assign(input,'nule.in');
  reset(input);
  assign(output,'nule.out');
  rewrite(output);
  fillchar(map,sizeof(map),0);
  readln(n);
  for i:=1 to n do
    begin
      map[i,0,1]:=-1;
      map[0,i,1]:=-1;
    end;
  for i:=1 to n do
    begin
      for j:=1 to n do
        begin
          read(now);
          if now=0
            then
              map[i,j,1]:=-1
            else
              begin
                while not(odd(now)) do
                  begin
                    inc(map[i,j,1]);
                    now:=now div 2;
                  end;
                while now mod 5=0 do
                  begin
                    inc(map[i,j,2]);
                    now:=now div 5;
                  end;
              end;
          if ((i<>1) or (j<>1)) and (map[i,j-1,1]=-1) and (map[i-1,j,1]=-1) then
            map[i,j,1]:=-1;
        end;
      readln;
    end;
  close(input);
  out:=maxlongint;
  work(1,2);
  work(2,1);
  if map[n,n,1]>=0
    then
      writeln(out)
    else
      writeln(0);
  close(output);
end.