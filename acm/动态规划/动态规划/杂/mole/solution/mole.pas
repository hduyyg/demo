Program Mole(input,output);
Const
  maxn=10001;

Var
  first:array[0..maxn] of longint;{first[i]表示总长为i的串最早出现的位置}
  pre:array[0..maxn] of longint;{时间先于当前田鼠但最晚出现的那只的编号}
  max:array[1..maxn] of longint;{max[i]表示在打第i只田鼠的情况下，前i只田鼠中最多能打掉的只数}
  i,j:longint;
  data:array[1..maxn,1..3] of longint;
  ans:longint;
  n,m:longint;

Begin

  Assign(input,'mole.in');
  Reset(input);
  Assign(output,'mole.out');
  Rewrite(output);

  {input}
  readln(m,n);
  for i:=1 to n do
    readln(data[i,3],data[i,1],data[i,2]);

  Close(input);

  pre[1]:=0;
  for i:=2 to n do
    if data[i,3]=data[i-1,3]
      then
        pre[i]:=pre[i-1]
      else
        pre[i]:=i-1;

  {main}
  fillchar(first,sizeof(first),0);
  for i:=1 to n do
    begin
      max[i]:=1;
      for j:=pre[i]{i-1} downto 1 do{将pre[i]换成i-1就能处理有重复田鼠的情况，但在所有田鼠在同一时刻出现的情况，算法复杂度就会变成O(n^2)}
        begin
          if (max[j]>=max[i]) and (abs(data[i,1]-data[j,1])+abs(data[i,2]-data[j,2])<=data[i,3]-data[j,3]) then
            max[i]:=max[j]+1;
          if j<first[max[i]-1] then{不再可能有更优答案}
            break;
        end;
      if first[max[i]]=0 then
        first[max[i]]:=i;
    end;

  {output}
  ans:=0;
  while first[ans+1]>0 do
    inc(ans);
  writeln(ans);

  Close(output);

End.
