program Test;

label
    start;

const
    MAX = 100;
    PI = 3;

type
    MyType = integer;

var
    num1, num2: integer;
procedure DisplayMessage(msg: string);
begin
    writeln(msg);
end;


function Add(a, b: integer): integer;
begin
    Add := a + b;
end;


begin
    num1 := 10;
    num2 := 20;

    writeln('La somme de ', num1, ' et ', num2, ' est ');
end.
