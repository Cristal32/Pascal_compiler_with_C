program Example;

const
    MAX = 100;
    PI = 3.1444;


var
    radius: Real;
    count: Integer;
    color: (Red, Green, Blue);
    shape: record
        X, Y: Integer;
    end;

function CalculateArea(radius: Real): Real;
begin 
    CalculateArea2 := PI * radius * radius;
end;

begin
    radius := 5.0;
    writeln('Laire du cercle avec un rayon de ', radius, ' est ',result) ;

    DisplayMessage ('Bonjour, monde!');

    if radius > 0 then
        writeln('Le rayon est positif.')
    else
        writeln('Le rayon est négatif ou nul.');

    count := 1;
    while count <= 5 do
    begin
        writeln('Compteur: ', count);
        count := count + 1;
    end;

    color := Green;
    

end.
