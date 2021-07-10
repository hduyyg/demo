program guard;
const
  maxn=10+2;maxm=1000+30;
  dx:array[1..4] of longint=(-1,0,1,0);
  dy:array[1..4] of longint=(0,1,0,-1);
type
  dui=record
    x,y,last,way:longint;
  end;
var
  n,m:longint;
  map:array[0..maxn,0..maxn] of longint;
  map2:array[0..maxn,0..maxn] of boolean;
  map4:array[0..maxn,0..maxn] of boolean;
  way:array[0..maxn] of longint;
  q:array[0..maxm] of dui;
  stx,sty:longint;
  edx,edy:longint;
procedure init;
begin
  assign(input,'guard.in');
  assign(output,'guard.out');
  reset(input);
  rewrite(output);
end;

procedure terminate;
begin
  close(input);
  close(output);
  halt;
end;

procedure readdata;
var
  i,j,k1,k2,kk:longint;
  ch:char;
begin
  fillchar(map,sizeof(map),0);
  fillchar(map2,sizeof(map2),false);
  readln(n,m);
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if (ord(ch)>48)and(ord(ch)<58) then
      begin
        map[i,j]:=ord(ch)-48;
        map2[i,j]:=true;
        continue;
      end;
      case ch of
        '.':
        begin
          continue;
        end;
        'E':
        begin
          stx:=i;sty:=j;
          map2[i,j]:=true;
        end;
        'X':
        begin
          map[i,j]:=20;
          map2[i,j]:=true;
        end;
        'C':
        begin
          edx:=i;edy:=j;
        end;
      end;
    end;
    readln;
  end;
  for i:=1 to m do
  begin
    read(j);
    read(ch);
    read(ch);
    for k1:=1 to n do
      for k2:=1 to n do
      begin
        if map[k1,k2]=j then
        begin
          case ch of
            'N':
            begin
              for kk:=k1-1 downto 1 do
              begin
                if map[kk,k2]=20 then break;
                if (kk=stx)and(k2=sty)then
                begin
                  writeln(-1);
                  terminate;
                end;
                map2[kk,k2]:=true;
              end;
            end;
            'E':
            begin
              for kk:=k2+1 to n do
              begin
                if map[k1,kk]=20 then break;
                if (k1=stx)and(kk=sty)then
                begin
                  writeln(-1);
                  terminate;
                end;
                map2[k1,kk]:=true;
              end;
            end;
            'S':
            begin
              for kk:=k1+1 to n do
              begin
                if map[kk,k2]=20 then break;
                if (kk=stx)and(k2=sty)then
                begin
                  writeln(-1);
                  terminate;
                end;
                map2[kk,k2]:=true;
              end;
            end;
            'W':
            begin
              for kk:=k2-1 downto 1 do
              begin
                if map[k1,kk]=20 then break;
                if (k1=stx)and(kk=sty)then
                begin
                  writeln(-1);
                  terminate;
                end;
                map2[k1,kk]:=true;
              end;
            end;
          end;
          break;
        end;
      end;
  end;
  if map2[edx,edy]=true then
  begin
    writeln(-1);
    terminate;
  end;
end;

procedure print(i,l:longint);
var
  k,oo:longint;
begin
  oo:=0;
  way[oo]:=i;
  while q[l].last<>0 do
  begin
    inc(oo);
    way[oo]:=q[l].way;
    l:=q[l].last;
  end;
  for k:=oo downto 0 do
  begin
    if way[k]=1 then writeln('N');
    if way[k]=2 then writeln('E');
    if way[k]=3 then writeln('S');
    if way[k]=4 then writeln('W');
  end;
end;

procedure bfs;
var
  l,r,i:longint;
  newx,newy:longint;
begin
  l:=0;r:=1;
  q[r].x:=stx;q[r].y:=sty;
  q[r].last:=0;
  while l<r do
  begin
    inc(l);
    for i:=1 to 4 do
    begin
      newx:=q[l].x+dx[i];
      newy:=q[l].y+dy[i];
      if (not map4[newx,newy])and(newx>=1)and(newy>=1)and(newx<=n)and(newy<=n) then
      begin
        if (newx=edx)and(newy=edy) then
        begin
          print(i,l);
          terminate;
        end;
        map4[newx,newy]:=true;
        inc(r);
        q[r].last:=l;q[r].way:=i;
        q[r].x:=newx;q[r].y:=newy;
      end;
    end;
  end;
end;

procedure work;
begin
  move(map2,map4,sizeof(map2));
  bfs;
  writeln(-1);
end;

begin
  init;
  readdata;
  work;
  terminate;
end.

