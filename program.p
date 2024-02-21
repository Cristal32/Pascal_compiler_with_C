program AnotherExample;

const
    MAX = 100;
    PI = 3;
type
    MyType = integer;
    RealArray = array [1..5] of real;
    Point = record
                x, y: real;
            end;

function CalculateArea(radius: real): real;
begin
    CalculateArea := PI * radius * radius;
end;

procedure DisplayMessage(message: string);
begin
    writeln(message);
end;

begin
    writeln('Max value:', MAX);
    writeln('Area of circle with radius 5:', CalculateArea(5));
    DisplayMessage('Hello, world!');
end.
