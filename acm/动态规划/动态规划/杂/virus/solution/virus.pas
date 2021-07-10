Program Virus(input,output);
Const
  maxl=1000;
  maxs=500;

Var
  s,ans:longint;
  int:array[1..maxl] of char;
  now:array[1..maxl] of char;
  l,len:longint;
  ok:array[0..maxs,-1..maxs] of longint;{Ô­´®£¬µ±Ç°´®}
  str:ansistring;
  i,j:longint;

  Function check:longint;
  var
    i,j:longint;
    begin
      fillchar(ok,sizeof(ok),0);
      for i:=0 to len do
        ok[0,i]:=1;
      for i:=1 to l do
        begin
          if int[i]='?' then
            for j:=1 to len do
              begin
                ok[i,j]:=0;
                if ok[i-1,j-1]=1 then
                  ok[i,j]:=1;
              end;
          if int[i]='*' then
            for j:=0 to len do
              ok[i,j]:=ok[i-1,j] or (ok[i,j-1]);
          if (int[i]<>'*') and (int[i]<>'?') then
            for j:=1 to len do
              begin
                ok[i,j]:=0;
                if (ok[i-1,j-1]=1) and (int[i]=now[j]) then
                  ok[i,j]:=1;
              end;
        end;
      for i:=0 to len do
        if ok[l,i]=1 then
          exit(0);
      exit(1);
    end;

Begin

  Assign(input,'virus.in');
  Reset(input);
  Assign(output,'virus.out');
  Rewrite(output);

  readln(str);
  l:=length(str);
  for i:=1 to l do
    int[i]:=str[i];

  ans:=0;
  readln(s);
  for i:=1 to s do
    begin
      readln(str);
      len:=length(str);
      for j:=1 to len do
        now[j]:=str[j];
      inc(ans,check);
    end;

  Close(input);

  writeln(ans);

  Close(output);

End.