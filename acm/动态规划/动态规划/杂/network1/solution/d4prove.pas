var i,min,sum:longint;
    a,b:array [1..10] of longint;
procedure search(dep,r:longint);
var i:longint;
begin
     if dep=10
        then begin
                  a[dep]:=r;
                  sum:=0;
                  for i:=1 to 10 do inc(sum,a[i]*(21-i));
                  if sum>155 then exit;
                  sum:=0;
                  for i:=1 to 10 do inc(sum,a[i]*i);
                  if sum<min then
                     begin
                          min:=sum;
                          for i:=1 to 10 do b[i]:=a[i]
                     end
             end
        else for i:=0 to r do
             begin
                  a[dep]:=i;
                  search(dep+1,r-i)
             end
end;

begin
     min:=maxlongint;
     search(1,9);
     writeln(min);
     for i:=1 to 10 do write(b[i],' ');
     writeln
end.
