program Test;

const
    MAX = 100;

type
    MyType = integer;

var
    num1, num2: integer;

function Add(a, b: integer): integer;
begin
    Add := a + b;
end;

begin
    num1 := 10;
    num2 := 20;
    result := Add(num1, num2);

    writeln('La somme de ', num1, ' et ', num2, ' est ', result);
end.
