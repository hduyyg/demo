program guard;
const
  dx:array[1..4]of longint=(1,-1,0,0);
  dy:array[1..4]of longint=(0,0,1,-1);
  ch:array[1..4]of char=('S','N','E','W');
var
  map:array[1..10,1..10]of char;
  gx,gy:array[1..10]of longint;
  duix,duiy:array[1..100]of longint;
  visit,ok:array[0..11,0..11]of boolean;
  pre:array[1..10,1..10]of longint;
  bx,by,ex,ey,x,y,n,g,i,j,head,tail,temp,x1,y1:longint;
  z:char;

procedure print(x,y:longint);
var
  temp:longint;
begin
  if (x=bx)and(y=by)then exit;
  temp:=pre[x,y];
  print(x-dx[temp],y-dy[temp]);
  writeln(ch[temp]);
end;
  
begin
  assign(input,'guard.in');reset(input);
  assign(output,'guard.out');rewrite(output);
  readln(n,g);
  fillchar(ok,sizeof(ok),false);
  for i:=1 to n do begin
    for j:=1 to n do begin
      read(map[i,j]);
      ok[i,j]:=true;
      if map[i,j]in['1'..'9']then begin
        ok[i,j]:=false;
        temp:=ord(map[i,j])-48;
        gx[temp]:=i;
        gy[temp]:=j;
      end else if map[i,j]='E' then begin
        bx:=i;by:=j;
      end else if map[i,j]='C' then begin
        ex:=i;ey:=j;
      end else if map[i,j]='X' then ok[i,j]:=false;
    end;
    readln;
  end;
  for i:=1 to g do begin
    read(temp);
    x:=gx[temp];y:=gy[temp];
    read(z);readln(z);
    case z of
      'E':while(y<=n)and(map[x,y]<>'X')do begin
        ok[x,y]:=false;
        inc(y);
      end;
      'W':while(y>0)and(map[x,y]<>'X')do begin
        ok[x,y]:=false;
        dec(y);
      end;
      'S':while(x<=n)and(map[x,y]<>'X')do begin
        ok[x,y]:=false;
        inc(x);
      end;
      'N':while(x>0)and(map[x,y]<>'X')do begin
        ok[x,y]:=false;
        dec(x);
      end;
    end;
  end;
  fillchar(visit,sizeof(visit),false);
  head:=0;tail:=1;
  duix[1]:=bx;duiy[1]:=by;
  if not ok[bx,by] then begin
    writeln(-1);
    close(input);close(output);halt;
  end;
  repeat
    inc(head);
    x:=duix[head];y:=duiy[head];
    for i:=1 to 4 do begin
      x1:=x+dx[i];y1:=y+dy[i];
      if (not ok[x1,y1])or(visit[x1,y1])then continue;
      visit[x1,y1]:=true;
      inc(tail);
      duix[tail]:=x1;duiy[tail]:=y1;
      pre[x1,y1]:=i;
    end;
  until head=tail;
  if not visit[ex,ey] then writeln(-1)else print(ex,ey);
  close(input);close(output);
end.
  
  

    
