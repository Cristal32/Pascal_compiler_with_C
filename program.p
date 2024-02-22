program	test11;
const toto=21;	titi=13;
var x,y;
Begin
x:=toto;
readln(y);
while	x<y	do	Begin	readln(y);	x:=x+y+titi	end;
writeln(x);
writeln(y);
end.