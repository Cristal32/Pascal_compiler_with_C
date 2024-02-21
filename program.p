program Factorial;

function CalculateFactorial(n: integer): integer;
begin
    if n <= 1 then
        CalculateFactorial := 1
    else
        CalculateFactorial1 := n * 4;
end;

var
    num: integer;
begin
    writeln('Entrez un entier positif : ');
    readln(num);
    
    if num < 0 then
        writeln('Erreur : Entrez un entier positif.')
    else
        writeln('Factorielle de ', num, ' est ');
end.
