uses graph;
const maxsize=20;len=20;
type recordtype=record e,s:byte end;
     array1=array[1..4] of integer;
     array2=array[1..maxsize,1..maxsize] of integer;
var i,i1,i2,j,j1,j2,n,sizex,sizey:integer;
    d1,d2,d3:array2;
    maze:array [1..maxsize,1..maxsize] of  recordtype;
    d:array[1..maxsize,1..maxsize,1..maxsize,1..3] of shortint;
    door:array[1..maxsize,1..maxsize,1..maxsize] of integer;
    pos:array[1..4] of array1;
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
     for i:=1 to sizex do
     begin
          for j:=1 to sizey do
              if maze[i,j].e=1 then line((j+1)*len,(i)*len,(j+1)*len,(i+1)*len);
          for j:=1 to sizey do
              if maze[i,j].s=1 then line((j)*len,(i+1)*len,(j+1)*len,(i+1)*len);
     end;
end;
function opendoor(x1,y1,x2,y2:integer;var door:array2):integer;
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
     if cx1=-1 then begin setcolor(red);
                          out1(pos[1,1],pos[1,2],pos[1,3],pos[1,4]);
                          setcolor(white);
                          out1(pos[2,1],pos[2,2],pos[2,3],pos[2,4]) end
               else begin setcolor(red);
                          out1(pos[1,1],pos[1,2],cx1,cy1);
                          setcolor(white);
                          out1(pos[2,1],pos[2,2],cx1,cy1);
                          setcolor(white);
                          out1(cx2,cy2,pos[1,3],pos[1,4]);
                          setcolor(red);
                          out1(cx2,cy2,pos[2,3],pos[2,4]);
                          setcolor(green);
                          out1(cx1,cy1,cx2,cy2) end

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
procedure out3;
var i,j,k,l,col,right,current,x1,x2,y1,y2,z1,z2:integer;
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
     for col:=min(min(pos[1,2],pos[2,2]),pos[3,2]) to max(max(pos[1,4],pos[2,4]),pos[3,4]) do
     begin
          if col=pos[1,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if i<>pos[1,1] then door[i,j,k]:=10000;
          if col=pos[2,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if j<>pos[2,1] then door[i,j,k]:=10000;
          if col=pos[3,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if k<>pos[3,1] then door[i,j,k]:=10000;
          for i:=pos[1,1] to pos[1,3] do
              for j:=pos[2,1] to pos[2,3] do
                  for k:=pos[3,1] to pos[3,3] do
                  if (door[i,j,k]<5000) and (door[i,j,k]>=0) then
                  begin
                       if (col>=pos[1,2])and(col<=pos[1,4])and(i<pos[1,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((i>=j)or(i<d[i,j,k,2]))and((i>=k)or(i<d[i,j,k,3]))
                               then current:=current+maze[i,col].s;
                            if current<door[i+1,j,k] then
                            begin door[i+1,j,k]:=current;
                                  for l:=1 to 3 do d[i+1,j,k,l]:=d[i,j,k,l]
                            end
                       end;
                       if (col>=pos[2,2])and(col<=pos[2,4])and(j<pos[2,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((j>=i)or(j<d[i,j,k,1]))and((j>=k)or(j<d[i,j,k,3]))
                               then current:=current+maze[j,col].s;
                            if current<door[i,j+1,k] then
                            begin door[i,j+1,k]:=current;
                                  for l:=1 to 3 do d[i,j+1,k,l]:=d[i,j,k,l]
                            end
                       end;
                       if (col>=pos[3,2]) and (col<=pos[3,4]) and (k<pos[3,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((k>=i)or(k<d[i,j,k,1]))and((k>=j)or(k<d[i,j,k,2]))
                               then current:=current+maze[k,col].s;
                            if current<door[i,j,k+1] then
                            begin door[i,j,k+1]:=current;
                                  for l:=1 to 3 do d[i,j,k+1,l]:=d[i,j,k,l]
                            end
                       end
                  end;
          if col<max(max(pos[1,4],pos[2,4]),pos[3,4]) then
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
          if col=pos[1,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if i<>pos[1,3] then door[i,j,k]:=-10000;
          if col=pos[2,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if j<>pos[2,3] then door[i,j,k]:=-10000;
          if col=pos[3,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if k<>pos[3,3] then door[i,j,k]:=-10000;
     end;
     end;
     writeln;
     writeln(door[pos[1,3],pos[2,3],pos[3,3]]);
     x2:=pos[1,3];y2:=pos[2,3];z2:=pos[3,3];
     x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
     draw(x1,y1,z1,x2,y2,z2,max(max(pos[1,4],pos[2,4]),pos[3,4]));
     for right:=max(max(pos[1,4],pos[2,4]),pos[3,4])-1 downto min(min(pos[1,2],pos[2,2]),pos[3,2]) do
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
     for col:=min(min(pos[1,2],pos[2,2]),pos[3,2]) to right do
     begin
          if col=pos[1,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if i<>pos[1,1] then door[i,j,k]:=10000;
          if col=pos[2,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if j<>pos[2,1] then door[i,j,k]:=10000;
          if col=pos[3,2] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if k<>pos[3,1] then door[i,j,k]:=10000;
          for i:=pos[1,1] to pos[1,3] do
              for j:=pos[2,1] to pos[2,3] do
                  for k:=pos[3,1] to pos[3,3] do
                  if (door[i,j,k]<5000) and (door[i,j,k]>=0) then
                  begin
                       if (col>=pos[1,2])and(col<=pos[1,4])and(i<pos[1,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((i>=j)or(i<d[i,j,k,2]))and((i>=k)or(i<d[i,j,k,3]))
                               then current:=current+maze[i,col].s;
                            if current<door[i+1,j,k] then
                            begin door[i+1,j,k]:=current;
                                  for l:=1 to 3 do d[i+1,j,k,l]:=d[i,j,k,l]
                            end
                       end;
                       if (col>=pos[2,2])and(col<=pos[2,4])and(j<pos[2,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((j>=i)or(j<d[i,j,k,1]))and((j>=k)or(j<d[i,j,k,3]))
                               then current:=current+maze[j,col].s;
                            if current<door[i,j+1,k] then
                            begin door[i,j+1,k]:=current;
                                  for l:=1 to 3 do d[i,j+1,k,l]:=d[i,j,k,l]
                            end
                       end;
                       if (col>=pos[3,2]) and (col<=pos[3,4]) and (k<pos[3,3]) then
                       begin
                            current:=door[i,j,k];
                            if ((k>=i)or(k<d[i,j,k,1]))and((k>=j)or(k<d[i,j,k,2]))
                               then current:=current+maze[k,col].s;
                            if current<door[i,j,k+1] then
                            begin door[i,j,k+1]:=current;
                                  for l:=1 to 3 do d[i,j,k+1,l]:=d[i,j,k,l]
                            end
                       end
                  end;
          if col<right then
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
          if col=pos[1,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if i<>pos[1,3] then door[i,j,k]:=-10000;
          if col=pos[2,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if j<>pos[2,3] then door[i,j,k]:=-10000;
          if col=pos[3,4] then
             for i:=pos[1,1] to pos[1,3] do
                 for j:=pos[2,1] to pos[2,3] do
                     for k:=pos[3,1] to pos[3,3] do
                         if k<>pos[3,3] then door[i,j,k]:=-10000;
     end;
     end;
     x2:=x1;y2:=y1;z2:=z1;
     x1:=d[x2,y2,z2,1];y1:=d[x2,y2,z2,2];z1:=d[x2,y2,z2,3];
     draw(x1,y1,z1,x2,y2,z2,right);
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
     printmaze;
     case n of
     1:out1(pos[1,1],pos[1,2],pos[1,3],pos[1,4]);
     2:out2;
     3:out3
     end;
     readln;
     closegraph
end.




