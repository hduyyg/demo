const maxn=100;
      maxlimittime=3000;
type arraytype=array [0..maxlimittime] of longint;
     pointer=^node;
     node=record
                no:longint;
                d,c:arraytype;
                son:array [1..maxn] of pointer;
                father:pointer
          end;
var i,j,k,n,maxcost,limittime,v1,v2:longint;
    visited:array [1..maxn] of boolean;
    h:array [1..maxn] of longint;
    c1,c2,mergec,merged:array [1..maxlimittime] of longint;
    g:array [1..maxn,1..maxn] of longint;
    c,d:array [1..maxn,1..maxlimittime] of longint;
    root:pointer;
procedure create(var p:pointer; f:pointer; no:longint);
var i,v,v1,v2:longint;
begin
     visited[no]:=true;
     new(p);
     p^.no:=no;
     p^.father:=f;
     if p^.father=nil
        then begin
                  p^.d[0]:=0;
                  p^.c[0]:=0
             end
        else begin
                  v1:=p^.no;
                  v2:=p^.father^.no;
                  if g[v1,v2]<0 then
                     begin v:=v1; v1:=v2; v2:=v end;
                  p^.d[0]:=g[v1,v2]; p^.c[0]:=g[v1,v2];
                  for i:=1 to g[v1,v2] do
                  begin
                       p^.d[i]:=d[-g[v2,v1],i];
                       p^.c[i]:=c[-g[v2,v1],i];
                  end;
             end;
     for i:=1 to n do p^.son[i]:=nil;
     for i:=1 to n do
         if not(visited[i]) and (g[no,i]>0)
            then create(p^.son[i],p,i)
end;
procedure print(p:pointer);
var i:longint;
begin
     if p<>nil then
        begin
             write(p^.no:5);
             if p<>root then write(p^.father^.no:5) else write(' ':5);
             write(p^.d[0]:5);
             for i:=1 to p^.d[0] do write(p^.d[i]:5,p^.c[i]:5);
             writeln;
             for i:=1 to n do print(p^.son[i]);
        end
end;
procedure search(p:pointer);
var i,j,k,k1,k2,max,mincost,totalc:longint;
begin
     if p<>nil then
        begin
             for i:=1 to n do search(p^.son[i]);
             for i:=1 to n do
                 if p^.son[i]<>nil then
                 begin
                    for k:=p^.son[i]^.d[0] downto 1 do
                        if p^.son[i]^.d[k]<=limittime then break;
                    if p^.son[i]^.c[k]>maxcost
                       then maxcost:=p^.son[i]^.c[k]
                 end;
             for i:=1 to n-1 do
                 if p^.son[i]<>nil then
                   for j:=i+1 to n do
                       if p^.son[j]<>nil then
                       begin
                            mincost:=maxlongint;
                            k1:=p^.son[i]^.d[0];
                            k2:=1;
                            while k1>0 do
                            begin
                                 while (k2<=p^.son[j]^.d[0]) and (p^.son[i]^.d[k1]+p^.son[j]^.d[k2]>limittime) do inc(k2);
                                 if k2>p^.son[j]^.d[0] then break;
                                 if p^.son[i]^.c[k1]+p^.son[j]^.c[k2]<mincost
                                    then mincost:=p^.son[i]^.c[k1]+p^.son[j]^.c[k2];
                                 dec(k1)
                            end;
                            if mincost>maxcost then maxcost:=mincost
                       end;
            for i:=1 to n do
                if p^.son[i]<>nil then break;
            if p^.son[i]=nil then exit;
            for i:=1 to n do
                if p^.son[i]<>nil then h[i]:=1 else h[i]:=0;
            k:=0;
            repeat
                  max:=0; totalc:=0;
                  for i:=1 to n do
                      if h[i]>0 then
                         begin
                              inc(totalc,p^.son[i]^.c[h[i]]);
                              if p^.son[i]^.d[h[i]]>max then max:=p^.son[i]^.d[h[i]]
                         end;
                  inc(k);
                  merged[k]:=max;
                  mergec[k]:=totalc;
                  for i:=1 to n do
                      if p^.son[i]^.d[h[i]]=max then
                         begin
                             inc(h[i]);
                             if h[i]>p^.son[i]^.d[0] then break
                         end;
                  if h[i]>p^.son[i]^.d[0] then break
            until 1<0;
            for i:=1 to limittime do c1[i]:=maxlongint;
            for i:=1 to p^.d[0] do
                for j:=1 to k do
                    if p^.d[i]+merged[j]<=limittime
                       then if p^.c[i]+mergec[j]<c1[p^.d[i]+merged[j]]
                               then c1[p^.d[i]+merged[j]]:=p^.c[i]+mergec[j];
            k:=0; p^.c[0]:=maxlongint;
            for i:=1 to limittime do
                if (c1[i]<>maxlongint) and (c1[i]<p^.c[k]) then
                   begin
                        inc(k);
                        p^.d[k]:=i;
                        p^.c[k]:=c1[i]
                   end;
            p^.d[0]:=k;
            for i:=1 to k div 2 do
            begin k1:=p^.d[i]; p^.d[i]:=p^.d[k+1-i]; p^.d[k+1-i]:=k1;
                  k1:=p^.c[i]; p^.c[i]:=p^.c[k+1-i]; p^.c[k+1-i]:=k1;
        end;
{        print(root);
        writeln(maxcost);
        readln}
        end
end;
begin
     assign(input,'network.in');
     reset(input);
     readln(n,limittime);
     fillchar(g,sizeof(g),0);
     for i:=1 to n-1 do
     begin
          read(v1,v2,k);
          g[v1,v2]:=k;
          g[v2,v1]:=-i;
          for j:=1 to k do read(d[i,j],c[i,j]);
          readln
     end;
     close(input);
     assign(input,'');
     reset(input);
     for i:=1 to n do visited[i]:=false;
     create(root,nil,1);
{     print(root);}
     maxcost:=0;
     search(root);
     maxcost:=0;
     for i:=1 to n do
         if root^.son[i]<>nil then
            begin
                 for j:=1 to root^.son[i]^.d[0] do
                     if root^.son[i]^.d[j]<=limittime then break;
                 inc(maxcost,root^.son[i]^.c[j])
            end;
     assign(output,'network.out');
     rewrite(output);
     writeln(maxcost);
     close(output)
end.

