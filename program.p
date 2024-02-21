program NewTypesExample;

type
    DayOfWeek = (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday);
    Point = record
        x, y: integer;
    end;
    IntArray = array [1 ..10] of integer;

var
    day: DayOfWeek;
    p: Point;
    arr: IntArray;
    i: integer;

begin
    day := Monday;
    writeln('Day: ', day);


    for i := 1 to 10 do
    begin
        arr[item] := i * 2;
    end;

    writeln('Array:');
    for i := 1 to 10 do
    begin
        writeln('Element ', i, ': ', arr[i]);
    end;
end.
