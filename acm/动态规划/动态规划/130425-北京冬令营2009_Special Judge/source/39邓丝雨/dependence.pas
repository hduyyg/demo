program dependence;


procedure  init ;
begin
  assign(input,'dependence.in');
  assign(output,'dependence.out');
  reset(input);
  rewrite(output);
end;
procedure outit;
begin
  close(input) ;
  close(output);
end;

procedure prepare;
var
  i,j:longint;
begin
  writeln('No candidate key');
end;



begin
  init;
  prepare;
  outit;
end.


