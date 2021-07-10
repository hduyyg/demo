var     a:array[1..200,0..72]of longint;
        b,c,d,l,r:array[1..200]of longint;
        n,i,j,t:longint;
procedure init(i1,j1:longint);
var     x,y,n1:longint;
begin
        inc(n);
        read(b[n],c[n]);
        d[n]:=i1;
        if j1=1 then l[i1]:=n;
        if j1=2 then r[i1]:=n;
        n1:=n;
        if c[n]=0 then
        begin
                init(n1,1);
                init(n1,2);
        end;
end;
procedure search(i:longint);
var j,k:longint;
begin
        if (l[i]=0) and (r[i]=0)
                then begin
                        a[i,0]:=0;
                        for j:=1 to c[i] do
                                a[i,j]:=5*j+b[i]*2;
                end
                else begin
                        if l[i]<>0 then search(l[i]);
                        if r[i]<>0 then search(r[i]);
                        for j:=0 to 72 do
                        for k:=0 to 72-j do
                                if a[i,j+k]>a[l[i],j]+a[r[i],k]+b[i]*2
                                        then a[i,j+k]:=a[l[i],j]+a[r[i],k]+b[i]*2;
                end;
end;
begin
        assign(input,'gallery.in');
        reset(input);
        assign(output,'gallery.out');
        rewrite(output);
        readln(t);
        n:=1;
        init(1,1);
        for i:=1 to 200 do
                for j:=1 to 72 do a[i,j]:=1000;
        search(2);
        i:=72;
        while a[2,i]>=t do
                dec(i);
        writeln(i);
        close(input);
        close(output);
end.
