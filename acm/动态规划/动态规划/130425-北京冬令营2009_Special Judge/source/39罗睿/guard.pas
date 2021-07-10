Program guard;
Type
	what=record
		x,y:longint;
	end;
Var
	map:array[0..20,0..20]of longint;
	adress:array[0..15]of what;
	boo:array[0..20,0..20]of boolean;
	fx:array[0..15]of char;
	way:array[0..150]of char;
	n,g:longint;
	gate,classroom:what;
	
Procedure terminate;
begin
	close(input);
	close(output);
	halt;
end;

Procedure init;
var
	i,j,x:longint;
	c:char;
begin
	assign(input,'guard.in');
	assign(output,'guard.out');
	reset(input);
	rewrite(output);


	readln(n,g);
	for i:=1 to n do
	begin
		for j:=1 to n do
		begin
			read(c);
			if c='C' then begin classroom.x:=i; classroom.y:=j; map[i,j]:=0; end;
			if c='E' then begin gate.x:=i; gate.y:=j; map[i,j]:=0; end;
			if c='X' then map[i,j]:=2;
			if c='.' then map[i,j]:=0;
			if (ord(c)>ord('0'))and(ord(c)<=ord('9')) then 
			begin
				map[i,j]:=1;
				adress[ord(c)-ord('0')].x:=i;
				adress[ord(c)-ord('0')].y:=j;
			end;
		end;
		readln;
	end;
	//读数预处理

	for i:=1 to g do
	begin
		read(x);
		read(c);
		readln(c);
		fx[x]:=c;
	end;
end;
	
Procedure cant;
var
	i,j:longint;
begin
	for i:=1 to g do
	begin
		if fx[i]='N' then 
			for j:=adress[i].x downto 1 do
			begin
				if map[j,adress[i].y]=0 then map[j,adress[i].y]:=1;
				if map[j,adress[i].y]=2 then break; 
			end;

		if fx[i]='S' then 
			for j:=adress[i].x to n do
			begin
				if map[j,adress[i].y]=0 then map[j,adress[i].y]:=1;
				if map[j,adress[i].y]=2 then break;
			end;

		if fx[i]='E' then 
			for j:=adress[i].y to n do
			begin
				if map[adress[i].x,j]=0 then map[adress[i].x,j]:=1;
				if map[adress[i].x,j]=2 then break; 
			end;

		if fx[i]='W' then 
			for j:=adress[i].y downto 1 do
			begin
				if map[adress[i].x,j]=0 then map[adress[i].x,j]:=1;
				if map[adress[i].x,j]=2 then break;
			end;
	end;
	//把人能看见的地方设置成无法到达状态

	for i:=0 to n+1 do
	begin
		map[i,0]:=1;
		map[i,n+1]:=1;
		map[0,i]:=1;
		map[n+1,i]:=1;
	end;
	//保险起见，给地图加个边框
end;

Procedure print(step:longint);
var
	i:longint;
begin
	for i:=1 to step do
		writeln(way[i]);
	terminate;
	//坑爹- -忘记结束程序了
end;

Procedure dfs(x,y,step:longint);
begin
	if (x=classroom.x)and(y=classroom.y) then print(step);
	//边界
	
	if (x-1>0)and(y>0)and(y<=n)and(map[x-1,y]=0)and(boo[x-1,y]) then
	begin
		boo[x-1,y]:=false;
		way[step]:='N';
		dfs(x-1,y,step+1);
		boo[x-1,y]:=true;
	end;
	//向上
	
	if (x+1<=n)and(y>0)and(y<=n)and(map[x+1,y]=0)and(boo[x+1,y]) then
	begin
		boo[x+1,y]:=false;
		way[step]:='S';
		dfs(x+1,y,step+1);
		boo[x+1,y]:=true;
	end;	
	//向下
	
	if (y-1>0)and(x>0)and(x<=n)and(map[x,y-1]=0)and(boo[x,y-1]) then
	begin
		boo[x,y-1]:=false;
		way[step]:='W';
		dfs(x,y-1,step+1);
		boo[x,y]:=true;
	end;	
	//向左
	
	if (y+1<=n)and(x>0)and(x<=n)and(map[x,y+1]=0)and(boo[x,y+1]) then
	begin
		boo[x,y+1]:=false;
		way[step]:='E';
		dfs(x,y+1,step+1);
		boo[x,y+1]:=true;
	end;
	//向右
	
	//扩展时注意横纵坐标，跟数学不一样- -囧
end;
	

Procedure main;
var
	i,j:longint;
begin
	cant;
	//处理不能到达的地方
	
	{for i:=0 to n+1 do
	begin
		for j:=0 to n+1 do
			write(map[i,j]);
		writeln;
	end;

	writeln(gate.x,' ',gate.y);
	writeln(classroom.x,' ',classroom.y);}
	
	if (map[gate.x,gate.y]<>0)or(map[classroom.x,classroom.y]<>0) then 
	begin
		writeln(-1);
		terminate;
	end;
	//特判
	
	fillchar(boo,sizeof(boo),true);
	boo[gate.x,gate.y]:=false;
	//DFS预处理
	dfs(gate.x,gate.y,1);  //坑- -需要从1开始，所以开始的时候调了半天没发现问题- -、

	writeln(-1);	//failed
end;

Begin
	init;
	main;
	terminate;
End.
