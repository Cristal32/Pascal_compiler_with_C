program GestionNotes;

const
    MAX = 3;

var
    eleveNom: array[1 ..MAX] of string;
    eleveNote: array[1 ..MAX] of real;

procedure SaisirNotes();
var
    i: integer;
begin
    writeln('Saisie des notes des élèves :');
    for i := 1 to MAX do
    begin
        writeln(eleveNote[i]);

        writeln('Nom de leleve ', item, ' : ');
        readln(eleveNom[i]);
        writeln('Note de eleve ', i, ' : ');
        readln(eleveNote[i]);
    end;
end;

function MoyenneGenerale(): real;
var
    i: integer;
    total: real;
begin
    total := 0;
    for i := 1 to MAX do
    begin
        total := total + eleveNote[i];
    end;
    MoyenneGenerale := total / MAX;
end;

procedure AfficherNotesEtMoyenne();
var
    i: integer;
begin
    writeln('Liste des élèves et de leurs notes :');
    for i := 1 to MAX do
    begin
        writeln('Nom de lélève ', i, ' : ', eleveNom[i]);
        writeln('Note de lélève ', i, ' : ', eleveNote[i]);
    end;
    writeln('La moyenne générale est de : ', MoyenneGenerale());
end;

begin
    SaisirNotes();
    AfficherNotesEtMoyenne();
end.