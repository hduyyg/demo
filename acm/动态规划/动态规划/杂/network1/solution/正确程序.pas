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
var i,j,k,ck,n,limittime,v1,v2:longint;
    visited:array [1..maxn] of boolean;
    h,t:array [1..maxn] of longint;
    c1,mergec,merged:array [0..maxlimittime] of longint;
    g:array [1..maxn,1..maxn] of longint;
    c,d:array [1..maxn,1..maxlimittime] of longint;
    root:pointer;
    q:array [1..maxn] of pointer;

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
var i,j,k1,k2,max,minc,totalc:longint;
begin
     if p<>nil then
        begin
             for i:=1 to n do search(p^.son[i]);
             k1:=0;
             for i:=1 to n do
                 if (p^.son[i]<>nil) and (p^.son[i]^.d[0]>0) then
                 begin
                      inc(k1);
                      q[k1]:=p^.son[i]
                 end;
             if k1=0 then exit;
             if k1=1 then
                begin
                     for i:=0 to q[1]^.d[0] do merged[i]:=q[1]^.d[i];
                     for i:=0 to q[1]^.d[0] do mergec[i]:=q[1]^.c[i];
                end;
             for i:=1 to k1 do h[i]:=1;
             for i:=1 to k1 do t[i]:=q[i]^.d[0]+1;
             k2:=0;
             while k1>1 do
             begin
                  max:=0; totalc:=0;
                  for i:=1 to k1 do
                  begin
                       if q[i]^.d[h[i]]>max then max:=q[i]^.d[h[i]];
                       inc(totalc,q[i]^.c[h[i]])
                  end;
                  if max>limittime div 2 then
                     begin
                          for i:=1 to k1 do
                              while (t[i]>h[i]) and (q[i]^.d[t[i]-1]<=limittime-max) do dec(t[i]);
                          minc:=maxlongint;
                          for i:=1 to k1 do
                              if q[i]^.d[h[i]]=max then
                                 begin
                                      totalc:=q[i]^.c[h[i]];
                                      for j:=1 to k1 do
                                      begin
                                           if j=i then continue;
                                           if t[j]>q[j]^.d[0] then break;
                                           inc(totalc,q[j]^.c[t[j]])
                                      end;
                                      if (j<>i) and (t[j]>q[j]^.d[0]) then continue;
                                      if totalc<minc then minc:=totalc
                                 end
                     end;
                  if minc<>maxlongint then
                     begin
                          inc(k2);
                          merged[k2]:=max;
                          mergec[k2]:=totalc
                     end;
                  for i:=1 to k1 do
                      if q[i]^.d[h[i]]=max then
                         begin
                             inc(h[i]);
                             if h[i]>q[i]^.d[0] then break
                         end;
                  if h[i]>q[i]^.d[0] then break
             end;
             if k1>1 then merged[0]:=k2;
             i:=merged[0];
             j:=i-1;
             while j>0 do
             begin
                  if mergec[i]<=mergec[j] then mergec[j]:=-mergec[j] else i:=j;
                  dec(j)
             end;
             i:=1;
             j:=0;
             while i<=merged[0] do
             begin
                  if mergec[i]>0 then
                     begin inc(j); mergec[j]:=mergec[i]; merged[j]:=merged[i] end;
                  inc(i)
             end;
             merged[0]:=j;
             if merged[0]=0 then writeln('Error1!');
             {for i:=1 to merged[0]-1 do
                 if mergec[i]>=mergec[i+1] then writeln('Error1');}
             if p=root then
                begin
                     for i:=0 to merged[0] do p^.d[i]:=merged[i];
                     for i:=0 to merged[0] do p^.c[i]:=mergec[i];
                     exit
                end;
             for i:=1 to limittime do c1[i]:=maxlongint;
             for i:=1 to p^.d[0] do
                 for j:=1 to merged[0] do
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
             i:=p^.d[0];
             j:=i-1;
             while j>0 do
             begin
                  if p^.c[i]<=p^.c[j] then p^.c[j]:=-p^.c[j] else i:=j;
                  dec(j)
             end;
             i:=1;
             j:=0;
             while i<=p^.d[0] do
             begin
                  if p^.c[i]>0 then
                     begin inc(j); p^.c[j]:=p^.c[i]; p^.d[j]:=p^.d[i] end;
                  inc(i)
             end;
             p^.d[0]:=j;
             if p^.d[0]=0 then writeln('Error2!') {else 
                begin for i:=1 to p^.d[0] do write(p^.d[i],' ',p^.c[i],'   ');
                      writeln
                end;}
{         print(root);
         readln}
        end
end;

begin
     assign(output,'network.out');
     rewrite(output);
     assign(input,'network.in');
     reset(input);
     readln(n,limittime);
     fillchar(g,sizeof(g),0);
     for i:=1 to n-1 do
     begin
          read(v1,v2,k);
          ck:=0;
          for j:=1 to k do
          begin
               read(d[i,j],c[i,j]);
               if d[i,j]<=limittime then
                  begin inc(ck); d[i,ck]:=d[i,j]; c[i,ck]:=c[i,j] end
          end;
          readln;
          g[v1,v2]:=ck;
          if ck>0 then g[v2,v1]:=-i;
     end;
     close(input);
     assign(input,'');
     reset(input);
     for i:=1 to n do visited[i]:=false;
     create(root,nil,1);
     {print(root);}
     search(root);
     {print(root);}
{     maxcost:=0;
     for i:=1 to n do
         if root^.son[i]<>nil then
            begin
                 for j:=1 to root^.son[i]^.d[0] do
                     if root^.son[i]^.d[j]<=limittime then break;
                 inc(maxcost,root^.son[i]^.c[j])
            end;}
     if root^.d[0]=0
        then writeln(-1)
        else writeln(root^.c[1]);
     close(output)
end.

