program Test;

label
    Start;

const
    MAX = 100;
    PI = 3;

type
    DayOfWeek = (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday);
    Point = record
        x, y: integer;
    end;


{*this is a comment*}
    IntArray = array [1 ..10] of integer;

var
    num1, num2: integer;
    arr: intArray;

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
DisplayMessage('bonjour');
end;

begin
    Start;
    num1 := 10;;
    num2 := 20;
    goto Start;

   {*if num1 > 5 then
	begin
	writeln('num1');
	end*}
    
   for i := 1 to 10 do
    begin
        arr[i] := i * 2;
    end;

    writeln('La somme de ', num1, ' et ', num2, ' est ');
end.