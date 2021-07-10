Program Incsq(input,output);
Const
  maxn=81;

Var
  min,max,now:array[0..maxn] of longint;{这次正着存...}
  f:array[0..maxn,0..maxn] of longint;{f[i,j]表示到第i位为止，可行最小数}
  ok,a,b,c:array[0..maxn] of longint;{ok数组配合f使用表示第i位是否可能取到，a,b数组则为比大小时的临时数组}
  i,j:longint;
  start,lim,sum:longint;
  str:array[0..maxn] of longint;{input}
  ch:char;

  Function small:boolean;{判断两数大小}
  var
    i:longint;
    x,y:longint;
    begin
      if a[0]=0 then
        a[0]:=1;
      if b[0]=0 then
        b[0]:=1;
      x:=1;
      while (a[x]=0) and (x<=a[0]) do
        inc(x);
      y:=1;
      while (b[y]=0) and (y<=b[0]) do
        inc(y);
      if a[0]-x>b[0]-y then
        exit(false);
      if a[0]-x<b[0]-y then
        exit(true);
      for i:=0 to a[0]-x do
        begin
          if a[x+i]>b[y+i] then
            exit(false);
          if a[x+i]<b[y+i] then
            exit(true);
        end;
      exit(true);
    end;

  Procedure work(l,r:longint);{DP}
  var
    i,j,k:longint;
    begin
      fillchar(ok,sizeof(ok),0);
      ok[l-1]:=1;
      f[l-1]:=min;
      for i:=l to r do
        for j:=1 to i-l+1 do
          if ok[i-j]=1 then
            begin
              a[0]:=j;
              for k:=i-j+1 to i do
                a[k+j-i]:=str[k];
              b:=f[i-j];
              if small then{a<=b}
                continue;
              c:=a;
              a:=max;
              b:=c;
              if small then
                continue;

              ok[i]:=1;
              f[i]:=b;

              break;
            end;
    end;

Begin

  Assign(input,'incsq.in');
  Reset(input);
  Assign(output,'incsq.out');
  Rewrite(output);

  sum:=0;
  fillchar(str,sizeof(str),0);
  while not eoln do
    begin
      read(ch);
      inc(str[0]);
      str[str[0]]:=ord(ch)-48;
      inc(sum,str[str[0]]);
    end;

  Close(input);

  if sum=0 then
    begin
      for i:=1 to str[0] do
        write(0);
      writeln;
      Close(output);
      Halt;
    end;

  fillchar(min,sizeof(min),0);
  for i:=1 to maxn do
    max[i]:=9;
  max[0]:=maxn;

  work(1,str[0]);
  max:=f[str[0]];
  fillchar(min,sizeof(min),0);
  min[0]:=1;

  start:=1;
  while start<=str[0]-max[0] do
    begin
      lim:=str[0]-max[0];
      for i:=lim downto start do
        begin
          a[0]:=i-start+1;
          for j:=start to i do
            a[j-start+1]:=str[j];
          b:=min;
          if small then
            continue;
          c:=a;
          a:=max;
          b:=c;
          if small then
            continue;

          if i=lim then
            break;

          now:=min;
          min:=b;
          work(i+1,lim);

          j:=lim;
          while (str[j]=0) and (ok[j]=0) do
            dec(j);

          if ok[j]=1
            then
              break
            else
              min:=now;
        end;

      for j:=start to i do
        write(str[j]);
      write(',');

      start:=i+1;
    end;

  for i:=1 to max[0] do
    write(max[i]);
  writeln;

  Close(output);

End.