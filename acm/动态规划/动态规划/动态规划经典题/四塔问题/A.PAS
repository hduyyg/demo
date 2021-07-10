Const MaxN              = 50000;

Var N                   : Longint;
    Step                : Array[0..MaxN] of Longint;

Procedure Main;
Var i,j,e               : Longint;
    Temp                : Longint;
Begin
  Step[1] := 1;
  Temp := 1; i := 1; e := 0;
  While i<N do
    Begin
      Temp := Temp*2 Mod 10000; Inc(e);
      For j := 1 to e+1 do
        Begin
          Inc(i); Step[i] := (Step[i-1]+Temp) mod 10000;
          If i=N then Exit;
        End;
    End;
End;

Begin
  Readln(N);
    Main;
  Writeln(Step[N]);
End.