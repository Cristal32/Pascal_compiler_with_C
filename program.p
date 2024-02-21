program Example;

const
    MAX = 100;
    PI = 3.14159;

type
    Color = (Red, Green, Blue);
    Shape = record
        X, Y: Integer;
    end;

var
    radius: Real;
    count: Integer;
    color: Color;
    shape: Shape;

function CalculateArea(radius: Real): Real;
begin
    CalculateArea := PI * radius * radius;
end;

procedure DisplayMessage(msg: string);
begin
    writeln(msg);
end;

begin
    // Exemple d'utilisation d'une fonction
    radius := 5.0;
    writeln('L''aire du cercle avec un rayon de ', radius, ' est ', CalculateArea(radius));

    // Exemple d'utilisation d'une procédure
    DisplayMessage('Bonjour, monde!');

    // Exemple d'instructions conditionnelles
    if radius > 0 then
        writeln('Le rayon est positif.')
    else
        writeln('Le rayon est négatif ou nul.');

    // Exemple de boucle while
    count := 1;
    while count <= 5 do
    begin
        writeln('Compteur: ', count);
        count := count + 1;
    end;

    // Exemple d'instruction case
    color := Green;
    case color of
        Red: writeln('La couleur est rouge.');
        Green: writeln('La couleur est verte.');
        Blue: writeln('La couleur est bleue.');
    end;

    // Exemple de structure d'enregistrement
    shape.X := 10;
    shape.Y := 20;
    writeln('Coordonnées du point: X=', shape.X, ', Y=', shape.Y);
end.
