Program ex9;
Const
    maxn=50;
Var
    g,h:array[1..maxn,0..maxn]of longint;
    i,m,n,x,y:longint;
Function bestmatch(x,y:longint):longint;
var
    r:array[1..maxn,1..maxn]of longint;
    lx,ly,link:array[1..maxn]of longint;
    vx,vy:array[1..maxn]of boolean;
    i,j,p,q,d,l:longint;
function find(k:longint):boolean;
var
    a,b:longint;
begin
    vx[k]:=true;
    for a:=1 to q do
      if (not vy[a])and(lx[k]+ly[a]=r[k,a]) then
        begin
          b:=link[a];
          link[a]:=k;
          vy[a]:=true;
          if (b=0)or(find(b)) then exit(true);
          link[a]:=b;
        end;
    find:=false;
end;
begin
    if g[x,0]*h[y,0]=0 then
      begin
        bestmatch:=1;
        exit;
      end;
    if g[x,0]<=h[y,0] then
      begin
        p:=g[x,0];
        q:=h[y,0];
        for i:=1 to g[x,0] do
          for j:=1 to h[y,0] do
            r[i,j]:=bestmatch(g[x,i],h[y,j]);
      end
    else
      begin
        p:=h[y,0];
        q:=g[x,0];
        for i:=1 to g[x,0] do
          for j:=1 to h[y,0] do
            r[j,i]:=bestmatch(g[x,i],h[y,j]);
      end;
    fillchar(lx,sizeof(lx),0);
    fillchar(ly,sizeof(ly),0);
    fillchar(link,sizeof(link),0);
    for i:=1 to p do
      for j:=1 to q do
        if lx[i]<r[i,j] then lx[i]:=r[i,j];
    for i:=1 to p do
      while true do
        begin
          fillchar(vx,sizeof(vx),false);
          fillchar(vy,sizeof(vy),false);
          if find(i) then break;
          d:=maxlongint;
          for j:=1 to p do
            if vx[j] then
              for l:=1 to q do
                if (not vy[l])and(lx[j]+ly[l]-r[j,l]<d) then
                  d:=lx[j]+ly[l]-r[j,l];
          for j:=1 to p do
            if vx[j] then dec(lx[j],d);
          for j:=1 to q do
            if vy[j] then inc(ly[j],d);
        end;
    d:=0;
    for i:=1 to q do
      if link[i]<>0 then
        inc(d,r[link[i],i]);
    bestmatch:=d+1;
end;
Begin
    while not seekeof do
      begin
        fillchar(g,sizeof(g),0);
        fillchar(h,sizeof(h),0);
        readln(n,m);
        for i:=1 to n-1 do
          begin
            readln(x,y);
            inc(g[y,0]);
            g[y,g[y,0]]:=x;
          end;
        for i:=1 to m-1 do
          begin
            readln(x,y);
            inc(h[y,0]);
            h[y,h[y,0]]:=x;
          end;
        writeln(bestmatch(1,1));
      end;
End.
