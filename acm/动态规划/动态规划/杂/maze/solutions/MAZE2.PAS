uses graph;
const maxsize=20;  len=20;
type recordtype=record e,s:byte end;
     arraytype=array[1..maxsize,1..maxsize] of integer;
var i,i1,i2,j,j1,j2,n,sizex,sizey:integer;
    d1,d2,d3:arraytype;
    maze:array [1..maxsize,1..maxsize] of  recordtype;
    pos:array[1..3,1..4] of integer;
    fname:string[30];
    f:text;
    grDriver: Integer;
    grMode: Integer;
function min(x,y:integer):integer;
begin if x<y then min:=x else min:=y end;
function max(x,y:integer):integer;
begin if x>y then max:=x else max:=y end;
procedure printmaze;
var i,j,s:integer;
begin
     grDriver := Detect;
     InitGraph(grDriver, grMode,' ');
     for i:=1 to maxsize do
     begin
          for j:=1 to maxsize do
              if maze[i,j].e=1 then line((j+1)*len,(i)*len,(j+1)*len,(i+1)*len);
          for j:=1 to maxsize do
              if maze[i,j].s=1 then line((j)*len,(i+1)*len,(j+1)*len,(i+1)*len);
     end;
end;
function opendoor(x1,y1,x2,y2:integer;var door:arraytype):integer;
var i,j:integer;
begin
     door[x1,y1]:=0;
     for i:=x1+1 to x2 do door[i,y1]:=door[i-1,y1]+maze[i-1,y1].s;
     for j:=y1+1 to y2 do door[x1,j]:=door[x1,j-1]+maze[x1,j-1].e;
     for i:=x1+1 to x2 do
         for j:=y1+1 to y2 do
             if door[i-1,j]+maze[i-1,j].s<door[i,j-1]+maze[i,j-1].e
                then door[i,j]:=door[i-1,j]+maze[i-1,j].s
                else door[i,j]:=door[i,j-1]+maze[i,j-1].e;
     opendoor:=door[x2,y2]
end;
procedure out1(x1,y1,x2,y2:integer);
var i:integer;
begin
     if (x1<x2) and (y1<y2)
        then if opendoor(x1,y1,x2-1,y2,d1)+maze[x2-1,y2].s<
                opendoor(x1,y1,x2,y2-1,d1)+maze[x2,y2-1].e
                then begin out1(x1,y1,x2-1,y2);circle(y2*len+len div 2,x2*len+len div 2,len div 3){write('S')} end
                else begin out1(x1,y1,x2,y2-1);circle(y2*len+len div 2,x2*len+len div 2,len div 3){write('E')} end
        else if x1=x2
                then for i:=y1 to y2 do circle(i*len+len div 2,x1*len+len div 2,len div 3){write('E')}
                else for i:=x1 to x2 do circle(y1*len+len div 2,i*len+len div 2,len div 3){write('S')}
end;
procedure out2;
var x1,y1,x2,y2,i,mindoor,current,cx1,cx2,cy1,cy2:integer;
begin
     mindoor:=opendoor(pos[1,1],pos[1,2],pos[1,3],pos[1,4],d1)+
          opendoor(pos[2,1],pos[2,2],pos[2,3],pos[2,4],d2);
     cx1:=-1;
     for x1:=max(pos[1,1],pos[2,1]) to min(pos[1,3],pos[2,3]) do
         for y1:=max(pos[1,2],pos[2,2]) to min(pos[1,4],pos[2,4]) do
             for x2:=x1 to min(pos[1,3],pos[2,3]) do
                 for y2:=y1 to min(pos[1,4],pos[2,4]) do
                 begin
                      current:=opendoor(pos[1,1],pos[1,2],x1,y1,d3)
                               +opendoor(pos[2,1],pos[2,2],x1,y1,d3)
                               +opendoor(x2,y2,pos[1,3],pos[1,4],d3)
                               +opendoor(x2,y2,pos[2,3],pos[2,4],d3)
                               +opendoor(x1,y1,x2,y2,d3);
                      if current<mindoor then
                         begin
                              mindoor:=current;
                              cx1:=x1; cx2:=x2;cy1:=y1; cy2:=y2
                         end
                 end;
     writeln;
     writeln(mindoor);
     if cx1=-1 then begin out1(pos[1,1],pos[1,2],pos[1,3],pos[1,4]);
                         out1(pos[2,1],pos[2,2],pos[2,3],pos[2,4]) end
              else begin out1(pos[1,1],pos[1,2],cx1,cy1);
                         out1(pos[2,1],pos[2,2],cx1,cy1);
                         out1(cx1,cy1,cx2,cy2);
                         out1(cx2,cy2,pos[1,3],pos[1,4]);
                         out1(cx2,cy2,pos[2,3],pos[2,4]) end
end;


begin
     write('Input the name of datafile:'); readln(fname);
     assign(f,fname); reset(f);
     for i:=1 to maxsize do
         for j:=1 to maxsize do
             begin maze[i,j].e:=1;maze[i,j].s:=1 end;
     readln(f,sizex,sizey); readln(f,n);
     for i:=1 to n do
     begin
          readln(f,i1,j1,i2,j2);
          if i1=i2 then maze[i1,j1].e:=0 else maze[i1,j1].s:=0
     end;
     readln(f,n);
     for i:=1 to n do
     begin for j:=1 to 4 do read(f,pos[i,j]); readln(f) end;
     close(f);
     printmaze;
     case n of
     1:out1(pos[1,1],pos[1,2],pos[1,3],pos[1,4]);
     2:out2;
     3:
     end;
     readln;
     closegraph
end.




