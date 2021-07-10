Program ex4;
Const
    maxn=200000;
Type
    link=^node;
    node=record
           next:link;
           x,y:longint;
         end;
Var
    o1:array[1..maxn,1..3]of double;
    o2:array[1..maxn,1..2]of double;
    t,q,s,father,w:array[1..maxn]of longint;
    v:array[1..maxn]of boolean;
    g:array[1..maxn]of link;
    m:array[1..4]of double;
    n,i,j,k,x,y,z,f,r:longint;
    max,swap,temp:double;
    p:link;
Begin
    readln(n);
    for i:=1 to n do
      g[i]:=nil;
    for i:=1 to n-1 do
      begin
        readln(x,y,z);
        new(p);
        p^.x:=y;
        p^.y:=z;
        p^.next:=g[x];
        g[x]:=p;
        new(p);
        p^.x:=x;
        p^.y:=z;
        p^.next:=g[y];
        g[y]:=p;
      end;
    f:=1;
    r:=1;
    q[1]:=1;
    fillchar(v,sizeof(v),false);
    v[1]:=true;
    t[1]:=1;
    while f<=r do
      begin
        p:=g[q[f]];
        while p<>nil do
          begin
            if (not v[p^.x]) then
              begin
                inc(r);
                q[r]:=p^.x;
                v[p^.x]:=true;
                t[p^.x]:=r;
                father[p^.x]:=q[f];
                w[p^.x]:=p^.y;
              end;
            p:=p^.next;
          end;
        inc(f);
      end;
    fillchar(v,sizeof(v),false);
    for i:=r downto 1 do
      begin
        x:=q[i];
        for j:=1 to 3 do
          begin
            p:=g[x];
            o1[x,j]:=0;
            y:=0;
            while p<>nil do
              begin
                if (t[p^.x]>t[x])and(not v[p^.x])and(o1[x,j]<o1[p^.x,1]+p^.y) then
                  begin
                    y:=p^.x;
                    o1[x,j]:=o1[p^.x,1]+p^.y;
                  end;
                p:=p^.next;
              end;
            if y>0 then v[y]:=true;
            if j=1 then s[x]:=y;
          end;
        o2[x,1]:=o1[x,1];
        o2[x,2]:=o1[x,2];
      end;
    max:=o1[1,1]+o1[1,2]*2+o1[1,3];
    for i:=2 to r do
      begin
        x:=q[i];
        m[1]:=o1[x,1];
        m[2]:=o1[x,2];
        m[3]:=o1[x,3];
        if s[father[x]]=x then
          m[4]:=o2[father[x],2]+w[x]
        else
          m[4]:=o2[father[x],1]+w[x];
        temp:=m[4];
        for j:=1 to 3 do
          for k:=j+1 to 4 do
            if m[j]<m[k] then
              begin
                swap:=m[j];
                m[j]:=m[k];
                m[k]:=swap;
              end;
        if max<m[1]+m[2]*2+m[3] then max:=m[1]+m[2]*2+m[3];
        o2[x,1]:=m[1];
        o2[x,2]:=m[2];
        if temp=m[1] then
          s[x]:=0;
      end;
    writeln(max:0:0);
End.