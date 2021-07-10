const
        maxn=300;

var
        a:array[0..maxn+1]of longint;
        opt:array[1..maxn,1..maxn]of int64;
        n,k:longint;

procedure setup;
begin
        assign(input,'tree.in');
        reset(input);
        assign(output,'tree.out');
        rewrite(output);
end;

procedure endit;
begin
        close(input);
        close(output);
end;

procedure init;
var
        i,j,t:longint;
begin
        fillchar(opt,sizeof(opt),255);
        read(n,k);
        for i:=1 to k do read(a[i]);
        a[0]:=0;
        a[k+1]:=n+1;
        for i:=1 to k-1 do
                for j:=i+1 to k do if a[i]>a[j] then
                begin
                        t:=a[i];
                        a[i]:=a[j];
                        a[j]:=t;
                end;
end;

function work(l,r:longint):int64;
var
        i:longint;
        t,j,tr,tl:int64;
begin
        tr:=a[r+1]-1;
        tl:=a[l-1]+1;
        if tr>n then tr:=n;
        if tl<1 then tl:=1;
        if l>r then begin work:=0;exit end;
        if a[l]>n then begin work:=0;exit end;
        if tl>tr then begin work:=0;exit end;
        if opt[l,r]>=0 then begin work:=opt[l,r];exit;end;
        j:=maxlongint;
        for i:=l to r do
        begin
                t:=work(l,i-1);
                if t<j then inc(t,work(i+1,r));
                if t<j then j:=t;
        end;
        inc(j,tr-tl+1);
        opt[l,r]:=j;
        work:=j;
end;

begin
        setup;
        init;
        writeln(work(1,k));
        endit;
end.
