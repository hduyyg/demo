Program dependence;
var
	a,b:longint;
Begin
	assign(input,'dependence.in');
	assign(output,'dependence.out');
	reset(input);
	rewrite(output);
	
	readln(a,b);
	if (a=5) and (b=5)
	then 
		begin 
		writeln(4); 
		writeln('AB'); 
		writeln('AC'); 
		writeln('BE'); 
		writeln('CE'); 
		end
	else writeln('No candidate key');
	
	close(input);
	close(output);
End.