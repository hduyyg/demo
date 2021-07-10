
{
DMIH 2004 - Prvi dan natjecanja
Srednjoskolska skupina - II. podskupina
Zadatak REKLAME
}

{
   Ovaj zadatak rjesavamo dinamickim programiranjem.
   Imamo matricu polje[a, b, c, d, e, f, g] koja nam govori koliki je
   minimalni broj dana ako sam u zadnjih sedam dana
   koristio [a, b, c, d, e, f, g] reklama.
   Za svaku reklamu racunamo vrijednosti u polju pomocu
   prijasnjih stanja( To je dinamicko programiranje ).
   Slozenost algoritma je O(100*5^7)
}

var polje: array[0..1, 0..5, 0..5, 0..5, 0..5, 0..5, 0..5, 0..5] of longint;
    rez, j, o, i, n, k, l: longint;
    vrijed: array[0..7] of longint;
    reklama: array[0..100, 0..6] of integer;

procedure napravi(m: integer);
var poz, e: array[1..7] of integer;
    i: integer;
begin
  for i := 1 to 7 do e[i] := reklama[m+1, i-1];
  for poz[1] := 0 to k do
   for poz[2] := 0 to k do
    for poz[3] := 0 to k do
     for poz[4] := 0 to k do
      for poz[5] := 0 to k do
       for poz[6] := 0 to k do
        for poz[7] := 0 to k do
         polje[(m+1) mod 2, poz[1], poz[2], poz[3], poz[4], poz[5], poz[6], poz[7]] := 20000;
  for poz[1] := reklama[m, 0] to k do
   for poz[2] := reklama[m, 1] to k do
    for poz[3] := reklama[m, 2] to k do
     for poz[4] := reklama[m, 3] to k do
      for poz[5] := reklama[m, 4] to k do
       for poz[6] := reklama[m, 5] to k do
        for poz[7] := reklama[m, 6] to k do

            if (polje[m mod 2,poz[1], poz[2], poz[3], poz[4], poz[5], poz[6], poz[7]] > 0 ) then begin
                i := polje[m mod 2,poz[1], poz[2], poz[3], poz[4], poz[5], poz[6], poz[7]];
                if (polje[(m+1) mod 2,e[1], e[2], e[3], e[4], e[5], e[6], e[7]] > i+7) then
                    polje[(m+1) mod 2,e[1], e[2], e[3], e[4], e[5], e[6], e[7]] := i+7;
                if (polje[(m+1) mod 2,poz[7]+e[1], e[2], e[3], e[4], e[5], e[6], e[7]] > i+6) then
                    polje[(m+1) mod 2,poz[7]+e[1], e[2], e[3], e[4], e[5], e[6], e[7]] := i+6;
                if (polje[(m+1) mod 2,poz[6]+e[1], poz[7]+e[2], e[3], e[4], e[5], e[6], e[7]] > i+5) then
                    polje[(m+1) mod 2,poz[6]+e[1], poz[7]+e[2], e[3], e[4], e[5], e[6], e[7]] := i+5;
                if (polje[(m+1) mod 2,poz[5]+e[1], poz[6]+e[2], poz[7]+e[3], e[4], e[5], e[6], e[7]] > i+4) then
                    polje[(m+1) mod 2,poz[5]+e[1], poz[6]+e[2], poz[7]+e[3], e[4], e[5], e[6], e[7]] := i+4;
                if (polje[(m+1) mod 2,poz[4]+e[1], poz[5]+e[2], poz[6]+e[3], poz[7]+e[4], e[5], e[6], e[7]] > i+3) then
                    polje[(m+1) mod 2,poz[4]+e[1], poz[5]+e[2], poz[6]+e[3], poz[7]+e[4], e[5], e[6], e[7]] := i+3;
                if (polje[(m+1) mod 2,poz[3]+e[1], poz[4]+e[2], poz[5]+e[3], poz[6]+e[4], poz[7]+e[5], e[6], e[7]] > i+2) then
                    polje[(m+1) mod 2,poz[3]+e[1], poz[4]+e[2], poz[5]+e[3], poz[6]+e[4], poz[7]+e[5], e[6], e[7]] := i+2;
                if (polje[(m+1) mod 2,poz[2]+e[1], poz[3]+e[2], poz[4]+e[3], poz[5]+e[4], poz[6]+e[5], poz[7]+e[6], e[7]] > i+1) then
                    polje[(m+1) mod 2,poz[2]+e[1], poz[3]+e[2], poz[4]+e[3], poz[5]+e[4], poz[6]+e[5], poz[7]+e[6], e[7]] := i+1;
                if (polje[(m+1) mod 2,poz[1]+e[1], poz[2]+e[2], poz[3]+e[3], poz[4]+e[4], poz[5]+e[5], poz[6]+e[6], poz[7]+e[7]] > i) then
                    polje[(m+1) mod 2,poz[1]+e[1], poz[2]+e[2], poz[3]+e[3], poz[4]+e[4], poz[5]+e[5], poz[6]+e[6], poz[7]+e[7]] := i;
            end;
end;

function izracun: integer;
var poz: array[1..7] of integer;
    i, l, tre : integer;
begin
  tre := 10000;
  for poz[1] := reklama[n, 0] to k do
   for poz[2] := reklama[n, 1] to k do
    for poz[3] := reklama[n, 2] to k do
     for poz[4] := reklama[n, 3] to k do
      for poz[5] := reklama[n, 4] to k do
       for poz[6] := reklama[n, 5] to k do
        for poz[7] := reklama[n, 6] to k do begin

            i := 0; while (poz[7-i] = 0) do i := i+1;
            l := polje[n mod 2,poz[1], poz[2], poz[3], poz[4], poz[5], poz[6], poz[7]];
            if ((l > 0) and (l-i < tre)) then tre := l-i;

        end;
   izracun := tre;
end;

begin
    assign(input,'reklame.in');
    reset(input);
    assign(output,'reklame.out');
    rewrite(output);
    vrijed[0] := 1; for i := 1 to 7 do vrijed[i] := vrijed[i-1] * 5;
    read(n, k);
    for i := 1 to n do begin
        read(l); reklama[i, 0] := 1;
        for j := 1 to l-1 do begin
            read(o); reklama[i, o-1] := reklama[i, o-1] + 1;
        end;
    end;

    polje[0, 0, 0, 0, 0, 0, 0, 0] := 7;
    for i := 0 to n-1 do napravi(i);
    rez := izracun();
    writeln(rez);
    close(input);
    close(output)

end.
