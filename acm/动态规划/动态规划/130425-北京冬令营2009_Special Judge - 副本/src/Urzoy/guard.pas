program guard;
type ptype=record
     x,y:longint;
           end;
const
 dx:array[1..4]of longint=(1,-1,0,0);
 dy:array[1..4]of longint=(0,0,1,-1);
var n,g,i,j:longint;
  map:array[0..11,0..11]of char;
   pos:array[1..10]of ptype;
   q:array[1..100]of ptype;
   pre:array[1..10,1..10]of ptype;
   p:longint;
  x0,y0,x1,y1:longint;
  toward:array[1..10]of char;
procedure init;
begin
assign(input,'guard.in');reset(input);
assign(output,'guard.out');rewrite(output);
end;
procedure predo;
var i,j:longint;
begin
for i:=1 to g do
   begin
if  toward[i]='E' then
  for j:=pos[i].y to n do
    if map[pos[i].x,j]='.'then
       map[pos[i].x,j]:='X'
    else break;
if  toward[i]='W' then
  for j:=pos[i].y downto 1 do
    if map[pos[i].x,j]='.'then
       map[pos[i].x,j]:='X'
    else break;
if  toward[i]='S' then
  for j:=pos[i].x to n do
    if map[j,pos[i].y]='.'then
       map[j,pos[i].y]:='X'
    else break;
if  toward[i]='N' then
  for j:=pos[i].x downto 1 do
    if map[j,pos[i].y]='.'then
       map[j,pos[i].y]:='X'
    else break;
   end;
end;
procedure bfs;
var x,y,i,j,fst,rer,v:longint;
begin
fst:=1;rer:=1;
q[1].x:=x0;q[1].y:=y0;
while fst<=rer do
  begin
i:=q[fst].x;j:=q[fst].y;
for v:=1 to 4 do
     begin
  x:=i+dx[v];y:=j+dy[v];
if map[x,y]='.' then begin
      pre[x,y].x:=i;pre[x,y].y:=j;
     inc(rer);q[rer].x:=x;q[rer].y:=y;
      map[x,y]:='X';
                     end;
if map[x,y]='C' then begin
      pre[x,y].x:=i;pre[x,y].y:=j;
      map[x,y]:='X';
      x1:=x;y1:=y;
      exit;
                     end;
     end;//for
    inc(fst);
  end;//while
end;
procedure print(x,y:longint);
var i,j:longint;
begin
if (x=x0)and(y=y0)then exit;
if pre[x,y].x-x=1 then begin
  print(pre[x,y].x,pre[x,y].y);
  writeln('N');
                       end
else if pre[x,y].x-x=-1 then begin
  print(pre[x,y].x,pre[x,y].y);
  writeln('S');
                       end
else if pre[x,y].y-y=1 then begin
  print(pre[x,y].x,pre[x,y].y);
  writeln('W');
                       end
else if pre[x,y].y-y=-1 then begin
  print(pre[x,y].x,pre[x,y].y);
   writeln('E');
                       end
                       
end;
begin
init;
fillchar(map,sizeof(map),'X');
readln(n,g);
for i:=1 to n do
  begin
  for j:=1 to n do  begin
  read(map[i,j]);
 if map[i,j]='E' then  begin
          x0:=i;y0:=j;
                       end
else if map[i,j]in ['1'..'9'] then begin
       val(map[i,j],p);
    pos[p].x:=i;pos[p].y:=j;
    map[i,j]:='.';
                            end;
                    end;
  readln;
  end;
for i:=1 to g do
  begin
 read(p);read(toward[p]);read(toward[p]);readln;
  end;
predo;
{for i:=1 to n do
  begin
  for j:=1 to n do write(map[i,j]);writeln;
  end;}
bfs;
print(x1,y1);
close(input);close(output);
end.

