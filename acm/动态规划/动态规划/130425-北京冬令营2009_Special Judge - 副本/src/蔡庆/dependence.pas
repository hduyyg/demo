program dependence;
const
  maxn=1024+1;
  biao2:array[1..10] of longint=(512,256,128,64,32,16,8,4,2,1);
var
  n,m:longint;
  f:array[0..1001,0..maxn] of longint;
  zuo,you:array[0..maxn] of longint;
  ji:array[0..maxn] of longint;
  color:array[0..maxn] of boolean;
procedure init;
begin
  assign(input,'dependence.in');
  assign(output,'dependence.out');
  reset(input);
  rewrite(output);
end;

procedure terminate;
begin
  close(input);
  close(output);
  halt;
end;

procedure readdata;
var
  i,j:longint;
  ss:string;
  j1,j2,wei:longint;
begin
  readln(n,m);
  for i:=1 to m do
  begin
    j1:=0;
    readln(ss);
    for j:=1 to length(ss) do
    begin
      if ss[j]='-' then
      begin
        wei:=j+2;
        break;
      end;
      inc(j1,biao2[ord(ss[j])-64]);
    end;
    j2:=0;
    for j:=wei to length(ss) do
    begin
      if ss[j]=' ' then break;
      inc(j2,biao2[ord(ss[j])-64]);
    end;
    zuo[i]:=j1;you[i]:=j2;
  end;
end;

procedure work;
var
  i,j:longint;
  sum,num,num2,k,change:longint;
  kk:longint;
begin
  sum:=0;
  for i:=1 to n do
    inc(sum,biao2[i]);
  for i:=1<<(10-n) to (1<<10)-1 do
  begin
    kk:=(1024>>n)-1;
    if (i and kk)<>0 then continue;
    f[0,i]:=i;
  //  writeln(i);
  end;

  for j:=1<<(10-n) to (1<<10)-1 do
  begin
    kk:=(1024>>n)-1;
    if (j and kk)<>0 then continue;
    change:=0;
    for i:=1 to m do
    begin
      f[i,j]:=f[i-1,j];
      if (f[i,j]and(zuo[i])=zuo[i])then
      begin
        if f[i,j]<>(f[i,j] or you[i]) then inc(change);
        f[i,j]:=f[i,j] or you[i];
      end;
    //  writeln(i,' ',j,' ',f[i,j]);
    end;
    if change<>0 then
    begin
      for k:=1 to m do
      begin
        if f[m,j]=sum then break;
        for i:=1 to m do
          if (f[m,j])and(zuo[i])=zuo[i] then
          begin
            f[m,j]:=f[m,j] or you[i];
            if f[m,j]=sum then break;
          end;
      end;
    end;
  end;

  num:=0;
  for i:=1 to maxn do
      if (f[m,i]=sum) then
      begin
        inc(num);
        ji[num]:=i;
      end;
  for i:=1 to num do
    for j:=1 to num do
    begin
      if i=j then continue;
      if (ji[i]and ji[j])=ji[i] then color[ji[j]]:=true;
      if (ji[i]and ji[j])=ji[j] then color[ji[i]]:=true;
    end;
  num2:=0;
  for i:=num downto 1 do
    if not color[ji[i]] then
    begin
      inc(num2);
    end;
  writeln(num2);
  for i:=num downto 1 do
    if not color[ji[i]] then
    begin
      if ji[i]>=512 then
      begin
        write('A');
        dec(ji[i],512);
      end;
      if ji[i]>=256 then
      begin
        write('B');
        dec(ji[i],256);
      end;
      if ji[i]>=128 then
      begin
        write('C');
        dec(ji[i],128);
      end;
      if ji[i]>=64 then
      begin
        write('D');
        dec(ji[i],64);
      end;
      if ji[i]>=32 then
      begin
        write('E');
        dec(ji[i],32);
      end;
      if ji[i]>=16 then
      begin
        write('F');
        dec(ji[i],16);
      end;
      if ji[i]>=8 then
      begin
        write('G');
        dec(ji[i],8);
      end;
      if ji[i]>=4 then
      begin
        write('H');
        dec(ji[i],4);
      end;
      if ji[i]>=2 then
      begin
        write('I');
        dec(ji[i],4);
      end;
      if ji[i]>=1 then
      begin
        write('J');
        dec(ji[i],1);
      end;
      writeln;
    end;
end;

begin
  init;
  readdata;
  work;
  terminate;
end.

