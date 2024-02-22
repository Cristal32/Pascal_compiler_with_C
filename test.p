program Test;

label
    Start;

const
    MAX = 100;
    PI = 3;
var
    num1, num2, num3: integer;

procedure DisplayMessage(msg: string);
begin
    writeln(msg);
end;


function Add(a, b: integer): integer;
{*num4: integer;*}
var
    Add:integer;
begin
    Add := a + b;
end;


begin
    num1 := 10;
    num2 := 20;
    goto Start;
    Start;
    writeln('La somme de ', num1, ' et ', num2, ' est ');
end.