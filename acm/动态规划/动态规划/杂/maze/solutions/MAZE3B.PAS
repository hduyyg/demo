uses graph;
const maxsize=20;  len=20;
type recordtype=record e,s:byte end;
var i,i1,i2,j,j1,j2,n,sizex,sizey,grDriver,grMode:integer;
    maze:array [1..maxsize,1..maxsize] of  recordtype;
    d:array[1..maxsize,1..maxsize,1..maxsize,1..3] of shortint;
    door:array[1..maxsize,1..maxsize,1..maxsize] of integer;
    pos:array[1..3,1..4] of integer;
    fname:string[30];
    f:text;
function min(x,y:integer):integer;
begin if x<y then min:=x else min:=y end;
function max(x,y:integer):integer;
begin if x>y then max:=x else max:=y end;
procedure printmaze;
var i,j,s:integer;
begin
     for i:=1 to sizex do
         for j:=1 to sizey do
         begin
              if maze[i,j].e=1 then line((j+1)*len,(i)*len,(j+1)*len,(i+1)*len);
              if maze[i,j].s=1 then line((j)*len,(i+1)*len,(j+1)*len,(i+1)*len);
         end;
end;
procedure draw(x1,y1,z1,x2,y2,z2,col:integer);
var i:integer;
begin
     setcolor(white);
     if (col>=pos[1,2]) and (col<=pos[1,4]) then
        for i:=x1 to x2 do circle(col*len+len div 2,i*len+len div 2,len div 3);
     setcolor(red);
     if (col>=pos[2,2]) and (col<=pos[2,4]) then
        for i:=y1 to y2 do circle(col*len+len div 2,i*len+len div 2,len div 3);
     setcolor(green);
     if (col>=pos[3,2]) and (col<=pos[3,4]) then
        for i:=z1 to z2 do circle(col*len+len div 2,i*len+len div 2,len div 3);
end;
procedure nextcol(col:integer);
var i,j,k:integer;
begin
     for i:=pos[1,1] to pos[1,3] do
         for j:=pos[2,1] to pos[2,3] do
             for k:=pos[3,1] to pos[3,3] do
             begin
                  d[i,j,k,1]:=i;
                  d[i,j,k,2]:=j;
                  d[i,j,k,3]:=k;
                  if (col>=pos[1,2]) and (col<pos[1,4])
                     then door[i,j,k]:=door[i,j,k]+maze[i,col].e;
                  if (col>=pos[2,2]) and (col<pos[2,4]) and (j<>i)
                     then  door[i,j,k]:=door[i,j,k]+maze[j,col].e;
                  if (col>=pos[3,2])and(col<pos[3,4])and(k<>i)and(k<>j)
                     then door[i,j,k]:=door[i,j,k]+maze[k,col].e
             end;
     for i:=pos[1,1] to pos[1,3] do
         for j:=pos[2,1] to pos[2,3] do
             for k:=pos[3,1] to pos[3,3] do
             begin
                  if (col=pos[1,4])and(i<>pos[1,3]) then door[i,j,k]:=-10000;
                  if (col=pos[2,4])and(j<>pos[2,3]) then door[i,j,k]:=-10000;
                  if (col=pos[3,4])and(k<>pos[3,3]) then door[i,j,k]:=-10000;
             end
end;
procedure calculate(leftcol,rightcol:integer);
var i,j,k,l,col,current,p:integer;
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
          for i:=pos[1,1] to pos[1,3] do
              for j:=pos[2,1] to pos[2,3] do
                  for k:=pos[3,1] to pos[3,3] do
                  begin
                       if (col=pos[1,2])and(i<>pos[1,1]) then door[i,j,k]:=10000;
                       if (col=pos[2,2])and(j<>pos[2,1]) then door[i,j,k]:=10000;
                       if (col=pos[3,2])and(k<>pos[3,1]) then door[i,j,k]:=10000
                  end;
          for i:=pos[1,1] to pos[1,3] do
              for j:=pos[2,1] to pos[2,3] do
                  for k:=pos[3,1] to pos[3,3] do
                      if (door[i,j,k]<5000) and (door[i,j,k]>=0) then
                         for p:=1 to 3 do
                             if (col>=pos[p,2])and(col<=pos[p,4]) then
                             begin
                                  current:=door[i,j,k];
                                  case p of
                                  1:if i<pos[p,3] then begin
                                    if ((i>=j)or(i<d[i,j,k,2]))and((i>=k)or(i<d[i,j,k,3]))
                                       then current:=current+maze[i,col].s;
                                    if current<door[i+1,j,k] then
                                    begin door[i+1,j,k]:=current;
                                          for l:=1 to 3 do d[i+1,j,k,l]:=d[i,j,k,l]
                                    end
                                    end;
                                  2:if j<pos[p,3] then begin
                                    if ((j>=i)or(j<d[i,j,k,1]))and((j>=k)or(j<d[i,j,k,3]))
                                       then current:=current+maze[j,col].s;
                                    if current<door[i,j+1,k] then
                                    begin door[i,j+1,k]:=current;
                                          for l:=1 to 3 do d[i,j+1,k,l]:=d[i,j,k,l]
                                    end
                                    end;
                                  3:if k<pos[p,3] then begin
                                    if ((k>=i)or(k<d[i,j,k,1]))and((k>=j)or(k<d[i,j,k,2]))
                                       then current:=current+maze[k,col].s;
                                    if current<door[i,j,k+1] then
                                    begin door[i,j,k+1]:=current;
                                          for l:=1 to 3 do d[i,j,k+1,l]:=d[i,j,k,l]
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
     leftcol:=min(min(pos[1,2],pos[2,2]),pos[3,2]);
     rightcol:=max(max(pos[1,4],pos[2,4]),pos[3,4]);
     calculate(leftcol,rightcol);
     writeln(door[pos[1,3],pos[2,3],pos[3,3]]);
     x2:=pos[1,3];y2:=pos[2,3];z2:=pos[3,3];
     x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
     draw(x1,y1,z1,x2,y2,z2,max(max(pos[1,4],pos[2,4]),pos[3,4]));
     for col:=rightcol-1 downto  leftcol do
     begin
          calculate(leftcol,col);
          x2:=x1;y2:=y1;z2:=z1;
          x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
          draw(x1,y1,z1,x2,y2,z2,col);
     end
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
     grDriver := Detect;
     InitGraph(grDriver, grMode,' ');
     printmaze;
     out;
     readln;
     closegraph
end.
