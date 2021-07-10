program nule;

const MAXN = 1000;
      NEMA = -1;

type  mat8 = array[1..MAXN, 1..MAXN] of integer;

var   t2, t5 : mat8;
      koliko : array[0..MAXN, 0..MAXN] of longint;
      n, najbolji2, najbolji5 : longint;

procedure ucitaj;
var i, j, tmp : longint;
begin
    readln(n);
    for i:=1 to n do
    begin
        for j:=1 to n do
        begin
          if j<n then read(tmp) else readln(tmp);
          if tmp=0 then
          begin
            t2[i, j]:=NEMA;
            t5[i, j]:=NEMA;
          end else
          begin
            t2[i, j]:=0;
            t5[i, j]:=0;
            while tmp mod 2=0 do
            begin
               tmp:=tmp div 2;
               t2[i, j]:=t2[i, j]+1;
            end;
            while tmp mod 5=0 do
            begin
               tmp:=tmp div 5;
               t5[i, j]:=t5[i, j]+1;
            end;
          end;
        end;
    end;
end;

function nadji(var a : mat8) : longint;
var i, j, odozgo, slijeva : longint;
begin
   for i:=0 to n do
      for j:=0 to n do koliko[i, j]:=NEMA;
   koliko[1, 0]:=0;
   koliko[0, 1]:=0;
   for i:=1 to n do
      for j:=1 to n do if a[i, j]<>NEMA then
      begin
         odozgo:=NEMA;
         slijeva:=NEMA;
         if koliko[i, j-1]<>NEMA then odozgo:=koliko[i, j-1]+a[i, j];
         if koliko[i-1, j]<>NEMA then slijeva:=koliko[i-1, j]+a[i, j];
         if (odozgo<>NEMA)and((odozgo<slijeva)or(slijeva=NEMA)) then
            koliko[i, j]:=odozgo else koliko[i, j]:=slijeva;
      end;
   nadji:=koliko[n, n];
end;

begin
    assign(input,'nule.in');
    reset(input);
    assign(output,'nule.out');
    rewrite(output);
    ucitaj;
    najbolji2:=nadji(t2);
    najbolji5:=nadji(t5);
    if najbolji2<najbolji5 then writeln(najbolji2) else writeln(najbolji5);
    close(input);
    close(output)
end.