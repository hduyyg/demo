program guard;

type
h=record
pri,x,y:longint;
s:char;
end;
hh=record
x,y:longint;
end;

const
zx:array[1..4] of longint=(1,-1,0,0);
zy:array[1..4] of longint=(0,0,1,-1);
num:array[1..4] of char=('S','N','E','W');


var
i,j,k,l,m,n,g,a,b,c,r,bx,by,ex,ey:longint;
s:char;
que:array[0..100000] of h;
map:array[0..50,0..50] of longint;
used:array[0..50,0..50] of boolean;
stu:array[0..100] of hh;

procedure ter;
begin
 close(input);close(output);
 halt;
end;

procedure doing(x:longint;s:char);
var
i,j,k:longint;
begin
 i:=stu[x].x;
 j:=stu[x].y;
 case s of
  'N':
     for k:=i downto 1 do
      begin
       if map[k,j]=100 then break;
       map[k,j]:=x;
      end;
   'S':
     for k:=i to n do
      begin
       if map[k,j]=100 then break;
       map[k,j]:=x;
      end;
   'E':
     for k:=j to n do
      begin
       if map[i,k]=100 then break;
       map[i,k]:=x;
      end;
    'W':
     for k:=j downto 1 do
      begin
       if map[i,k]=100 then break;
       map[i,k]:=x;
      end;
 end;
end;

procedure ins(x,y,pri:longint;s:char);  inline;
begin
 inc(r);
 que[r].x:=x;
 que[r].y:=y;
 que[r].pri:=pri;
 que[r].s:=s;
 used[x,y]:=true;
end;

procedure print(x:longint);
begin
 if (x<=0) or (que[x].pri<=0) then exit;
 print(que[x].pri);
 writeln(que[x].s);
end;

function can(i,j:longint):boolean; inline;
begin
 can:=true;
 if (i<1) or (i>n) or (j<1) or (j>n) or (map[i,j]>=0) or (used[i,j]) then exit(false);
end;

procedure bfs;
var
i:Longint;
tem:h;
begin
 while l<r do
  begin
   inc(l);
   tem:=que[l];
   for i:=1 to 4 do
    if can(tem.x+zx[i],tem.y+zy[i]) then
     begin
      ins(tem.x+zx[i],tem.y+zy[i],l,num[i]);
      if (tem.x+zx[i]=ex) and (tem.y+zy[i]=ey) then
       begin
        print(r);
        ter;
       end;
     end;
  end;
end;

begin
assign(input,'guard.in');
assign(output,'guard.out');
reset(input);rewrite(output);
readln(n,g);
for i:=1 to n do
 begin
  for j:=1 to n do
   begin
    read(s);
    case s of
     '.':map[i,j]:=-1;
     'X':map[i,j]:=100;
     'E':begin
          map[i,j]:=-1;
          bx:=i;by:=j;
         end;
     'C':begin
          map[i,j]:=-2;
          ex:=i;ey:=j;
         end;
     '0'..'9':
         begin
          k:=ord(s)-ord('0');
          map[i,j]:=k;
          stu[k].x:=i;
          stu[k].y:=j;
         end;
    end;
   end;
  readln;
 end;
for i:=1 to g do
 begin
  read(k);
  read(s);
  read(s);
  readln;
  doing(k,s);
 end;
if (map[bx,by]>=0) or (map[ex,ey]>=0) then
 begin
  writeln(-1);
  ter;
 end;
if (bx=ex) and (by=ey) then ter;

l:=0;r:=0;
fillchar(used,sizeof(used),0);
ins(bx,by,0,'0');
bfs;
writeln(-1);
ter;
end.

