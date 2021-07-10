uses graph;
const maxsize=20;
type recordtype=record e,s:byte end;
var i,i1,i2,j,j1,j2,n,w,sizex,sizey,grDriver,grMode,mindoor:integer;
    maze:array [1..maxsize,1..maxsize] of  recordtype;
    d:array[1..maxsize,1..maxsize,1..maxsize,1..3] of shortint;
    door:array[1..maxsize,1..maxsize,1..maxsize] of integer;
    position:array[1..3,1..4] of integer;
    fname:string;
    path:array[1..3] of string;
    f:text;
function min(x,y:integer):integer;
begin if x<y then min:=x else min:=y end;
function max(x,y:integer):integer;
begin if x>y then max:=x else max:=y end;
procedure printresult(x1,y1,z1,x2,y2,z2,col:integer);
begin
     if (col>=position[1,2]) and (col<=position[1,4])
        then for i:=x1 to x2-1 do path[1]:='S'+path[1];
     if (col>=position[2,2]) and (col<=position[2,4])
        then for i:=y1 to y2-1 do path[2]:='S'+path[2];
     if (col>=position[3,2]) and (col<=position[3,4])
        then for i:=z1 to z2-1 do path[3]:='S'+path[3]
end;
procedure nextcol(col:integer);
var i,j,k:integer;
begin
     for i:=position[1,1] to position[1,3] do
         for j:=position[2,1] to position[2,3] do
             for k:=position[3,1] to position[3,3] do
             begin
                  d[i,j,k,1]:=i;
                  d[i,j,k,2]:=j;
                  d[i,j,k,3]:=k;
                  if (col>=position[1,2]) and (col<position[1,4])
                     then door[i,j,k]:=door[i,j,k]+maze[i,col].e;
                  if (col>=position[2,2]) and (col<position[2,4]) and
                     ((j<>i) or (col<position[1,2]) or (col>=position[1,4]))
                     then  door[i,j,k]:=door[i,j,k]+maze[j,col].e;
                  if (col>=position[3,2]) and (col<position[3,4]) and
                     ((k<>i) or (col<position[1,2]) or (col>=position[1,4])) and
                     ((k<>j) or (col<position[2,2]) or (col>=position[2,4]))
                     then door[i,j,k]:=door[i,j,k]+maze[k,col].e
             end;
     for i:=position[1,1] to position[1,3] do
         for j:=position[2,1] to position[2,3] do
             for k:=position[3,1] to position[3,3] do
             begin
                  if (col=position[1,4])and(i<>position[1,3]) then door[i,j,k]:=-1000;
                  if (col=position[2,4])and(j<>position[2,3]) then door[i,j,k]:=-1000;
                  if (col=position[3,4])and(k<>position[3,3]) then door[i,j,k]:=-1000;
             end
end;
procedure calculate(leftcol,rightcol:integer);
var i,i1,j,j1,k,k1,l,col,row,current,p:integer;
begin
     for i:=1 to maxsize do
         for j:=1 to maxsize do
             for k:=1 to maxsize do
             begin
                  d[i,j,k,1]:=i;
                  d[i,j,k,2]:=j;
                  d[i,j,k,3]:=k;
                  door[i,j,k]:=0;
             end;
     for col:=leftcol to rightcol do
     begin
          for i:=position[1,1] to position[1,3] do
              for j:=position[2,1] to position[2,3] do
                  for k:=position[3,1] to position[3,3] do
                  begin
                       if (col=position[1,2])and(i<>position[1,1]) then door[i,j,k]:=1000;
                       if (col=position[2,2])and(j<>position[2,1]) then door[i,j,k]:=1000;
                       if (col=position[3,2])and(k<>position[3,1]) then door[i,j,k]:=1000
                  end;
          for i:=position[1,1] to position[1,3] do
              for j:=position[2,1] to position[2,3] do
                  for k:=position[3,1] to position[3,3] do
                      if (door[i,j,k]<500) and (door[i,j,k]>=0) then
                         for p:=1 to 3 do
                             begin
                                  i1:=i; j1:=j; k1:=k;
                                  if (col>=position[p,2])and(col<=position[p,4]) then
                                  begin
                                  case p of
                                       1:begin i1:=i1+1; row:=i1 end;
                                       2:begin j1:=j1+1; row:=j1 end;
                                       3:begin k1:=k1+1; row:=k1 end
                                  end;
                                  if row<=position[p,3] then
                                  begin
                                  current:=door[i,j,k];
                                  if ((row>i) or (row<=d[i,j,k,1])) and
                                     ((row>j) or (row<=d[i,j,k,2])) and
                                     ((row>k) or (row<=d[i,j,k,3]))
                                     then current:=current+maze[row-1,col].s;
                                  if current<door[i1,j1,k1] then
                                  begin door[i1,j1,k1]:=current;
                                        for l:=1 to 3 do d[i1,j1,k1,l]:=d[i,j,k,l]
                                  end
                                  end
                                  end
                             end;
          if col<rightcol then nextcol(col)
     end;
end;
procedure out;
var x1,x2,y1,y2,z1,z2,col,leftcol,rightcol:integer;
begin
     leftcol:=min(min(position[1,2],position[2,2]),position[3,2]);
     rightcol:=max(max(position[1,4],position[2,4]),position[3,4]);
     calculate(leftcol,rightcol);
     mindoor:=door[position[1,3],position[2,3],position[3,3]];
     x2:=position[1,3];y2:=position[2,3];z2:=position[3,3];
     x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
     printresult(x1,y1,z1,x2,y2,z2,max(max(position[1,4],position[2,4]),position[3,4]));
     for col:=rightcol-1 downto  leftcol do
     begin
          for i:=1 to 3 do
              if (col>=position[i,2]) and (col<position[i,4]) then path[i]:='E'+path[i];
          calculate(leftcol,col);
          x2:=x1;y2:=y1;z2:=z1;
          x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
          printresult(x1,y1,z1,x2,y2,z2,col);
     end
end;
procedure showmaze(x0,y0:integer);
var i,j,s:integer;
begin
     for i:=1 to sizex do
         for j:=1 to sizey do
         begin
              if maze[i,j].e=1 then line(x0+(j+1)*w,y0+i*w,x0+(j+1)*w,y0+(i+1)*w);
              if maze[i,j].s=1 then line(x0+j*w,y0+(i+1)*w,x0+(j+1)*w,y0+(i+1)*w);
         end;
end;
procedure showpath(x0,y0:integer);
var x,y:integer;
begin
     for i:=1 to n do
     begin
          y:=position[i,1];x:=position[i,2];
          for j:=1 to length(path[i])+1 do
          begin
               case i of
               1:circle(x0+x*w+w div 2,y0+y*w+w div 2,w div 3);
               2:line(x0+x*w+w div 2,y0+y*w+w div 6,x0+x*w+w div 2,y0+y*w+w-w div 6);
               3:line(x0+x*w+w div 6,y0+y*w+w div 2,x0+x*w+w-w div 6,y0+y*w+w div 2);
               end;
               setcolor(0);
               if j<=length(path[i]) then
                  if path[i,j]='E'
                     then line(x0+x*w+w,y0+y*w+w div 4,x0+x*w+w,y0+y*w+3*w div 4)
                     else line(x0+x*w+w div 4,y0+y*w+w,x0+x*w+3*w div 4,y0+y*w+w);
               setcolor(white);
               if path[i,j]='E' then x:=x+1 else y:=y+1
          end
     end
end;
procedure showtext(x0,y0,mindoor:integer);
var i:integer;
    temp:string;
begin
     temp:='';
     while mindoor<>0 do
     begin temp:=chr(48+mindoor mod 10)+temp;mindoor:=mindoor div 10 end;
     outtextxy(x0,y0,temp);
     for i:=1 to n do outtextxy(x0,y0+20*i,path[i]);
end;
procedure showexplain(x0,y0,w:integer);
begin
     circle(x0+w div 2,y0+w div 2,w div 6);
     line(x0+w div 2,y0+20+w div 3,x0+w div 2,y0+20+w-w div 3);
     line(x0+w div 3,y0+40+w div 2,x0+w-w div 3,y0+40+w div 2);
     line(x0+w div 2,y0+60+w div 4,x0+w div 2,y0+60+3*w div 4);
     line(x0+3*w div 4,y0+60+w div 2,x0+5*w div 4,y0+60+w div 2);
     setcolor(0);
     line(x0+w div 2,y0+60+3*w div 8,x0+w div 2,y0+60+5*w div 8);
     line(x0+7*w div 8,y0+60+w div 2,x0+9*w div 8,y0+60+w div 2);
     setcolor(white);
     outtextxy(x0+w,y0+2*w div 5,'Path of the first man.');
     outtextxy(x0+w,y0+2*w div 5+20,'Path of the second man.');
     outtextxy(x0+w,y0+2*w div 5+40,'Path of the third man.');
     outtextxy(x0+3*w div 2,y0+2*w div 5+60,'Open a door on the wall.');
end;
procedure showresult;
var i,answerdoor:integer;
    answerfilename:string;
begin
     grDriver:=Detect;
     InitGraph(grDriver, grMode,' ');
     setcolor(white);
     w:=min(getmaxx div 2 div sizey,3*getmaxy div 4 div sizex)-1;
     showmaze(getmaxx div 2-w*sizey-w-10,3*getmaxy div 4-w*sizex-w);
     showpath(getmaxx div 2-w*sizey-w-10,3*getmaxy div 4-w*sizex-w);
     outtextxy(w,3*getmaxy div 4+10,'Result after run!');
     showtext(w,3*getmaxy div 4+30,mindoor);
     showmaze(getmaxx div 2-w+10,3*getmaxy div 4-w*sizex-w);
     answerfilename:='sample';
     for i:=1 to length(answerfilename) do fname[i]:=answerfilename[i];
     assign(f,fname); reset(f); readln(f); readln(f,answerdoor);
     for i:=1 to n do readln(f,path[i]); close(f);
     showpath(getmaxx div 2-w+10,3*getmaxy div 4-w*sizex-w);
     outtextxy(getmaxx div 2+w+150,3*getmaxy div 4+10,'Answer!');
     showtext(getmaxx div 2+w+150,3*getmaxy div 4+30,answerdoor);
     showexplain(getmaxx div 2-100,3*getmaxy div 4+10,20);
     readln;
     closegraph
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
     begin for j:=1 to 4 do read(f,position[i,j]); readln(f) end;
     for i:=n+1 to 3 do
         for j:=1 to 2 do
         begin position[i,j]:=position[1,j];position[i,j+2]:=position[i,j] end;
     for i:=1 to 3 do path[i]:=''; close(f);
     for i:=length(fname) downto 1 do fname[i+1]:=fname[i];
     fname[0]:=succ(fname[0]); fname[1]:='o'; fname[2]:='u'; fname[3]:='t';
     assign(f,fname); rewrite(f);
     out;
     writeln(f,mindoor);
     for i:=1 to n do writeln(f,path[i]); close(f);
     showresult;
end.
