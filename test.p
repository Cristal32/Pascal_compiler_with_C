program Test;

label
    Start;

const
    MAX = 100;
    PI = 3;
var
    num1, num2: integer;

procedure DisplayMessage(msg: string);
var
   x: integer;
begin
    x := 2;
    writeln(msg);
end;


function Add(a, b: integer): integer;
{*num4: integer;*}
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