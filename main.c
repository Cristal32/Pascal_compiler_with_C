#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    ID_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    EOF_TOKEN,
    EG_TOKEN,
    ELSE_TOKEN,
    REPEAT_TOKEN,
    UNTIL_TOKEN,
    FOR_TOKEN,
    INTO_TOKEN,
    DOWNTO_TOKEN,
    CASE_TOKEN,
    OF_TOKEN,
    PPT_TOKEN
} CODES;

// erreur types
typedef enum
{
    ID_ERR,
    PROGRAM_ERR,
    CONST_ERR,
    VAR_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    THEN_ERR,
    WHILE_ERR,
    DO_ERR,
    READ_ERR,
    WRITE_ERR,
    PV_ERR,
    PT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    FIN_ERR,
    NUM_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    CONST_VAR_BEGIN_ERR,
    VAR_BEGIN_ERR,
    ELSE_ERR,
    REPEAT_ERR,
    UNTIL_ERR,
    FOR_ERR,
    INTO_ERR,
    DOWNTO_ERR,
    CASE_ERR,
    OF_ERR,
    PPT_ERR
} CODES_ERR;

typedef struct
{
    CODES CODE;
    char NOM[20];
} Current_sym;

Current_sym SYM;

FILE *fichier;

char Car_Cour; // caract�re courant

// functions declaration
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void MULOP();
void ADDOP();
void RELOP();
void NTOP();
void COND();
void REPETER();
void POUR();
void CAS();
void Lire_Car();
void Erreur(CODES_ERR code);
void Test_Symbole(CODES cl, CODES_ERR COD_ERR);
void PROGRAM();
void BLOCK();
void CONSTS();
void Sym_Suiv();
void lire_mot();
void lire_nombre();

// functions definition

//===================== lire_mot ==========================
void lire_mot()
{
    char mot[20];
    int indice = 0;

    // Lecture du premier caract�re (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caract�res suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caract�re de fin de cha�ne
    mot[indice] = '\0';

    // V�rifier si le mot est un mot-cl�
    if (strcasecmp(mot, "program") == 0)
    {
        SYM.CODE = PROGRAM_TOKEN;
    }
    else if (strcasecmp(mot, "const") == 0)
    {
        SYM.CODE = CONST_TOKEN;
    }
    else if (strcasecmp(mot, "var") == 0)
    {
        SYM.CODE = VAR_TOKEN;
    }
    else if (strcasecmp(mot, "begin") == 0)
    {
        SYM.CODE = BEGIN_TOKEN;
    }
    else if (strcasecmp(mot, "end") == 0)
    {
        SYM.CODE = END_TOKEN;
    }
    else if (strcasecmp(mot, "if") == 0)
    {
        SYM.CODE = IF_TOKEN;
    }
    else if (strcasecmp(mot, "then") == 0)
    {
        SYM.CODE = THEN_TOKEN;
    }
    else if (strcasecmp(mot, "while") == 0)
    {
        SYM.CODE = WHILE_TOKEN;
    }
    else if (strcasecmp(mot, "do") == 0)
    {
        SYM.CODE = DO_TOKEN;
    }
    else if (strcasecmp(mot, "read") == 0)
    {
        SYM.CODE = READ_TOKEN;
    }
    else if (strcasecmp(mot, "write") == 0)
    {
        SYM.CODE = WRITE_TOKEN;
    }
    else
    {
        // If it's not a keyword, it's an identifier
        SYM.CODE = ID_TOKEN;
    }

    // Stockage du mot dans le jeton
    strcpy(SYM.NOM, mot);
}

//===================== Lire_nombre ==========================
void lire_nombre()
{
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour))
    {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caract�re de fin de cha�ne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    SYM.CODE = NUM_TOKEN;
    strcpy(SYM.NOM, nombre);
}

//===================== Sym_Suiv ==========================
void Sym_Suiv()
{
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car();
    }
    if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    else if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else
    {
        switch (Car_Cour)
        {
        case ';':
            SYM.CODE = PV_TOKEN;
            Lire_Car();
            break;

        case '+':
            SYM.CODE = PLUS_TOKEN;
            Lire_Car();
            break;

        case '-':
            SYM.CODE = MOINS_TOKEN;
            Lire_Car();
            break;

        case '*':
            SYM.CODE = MULT_TOKEN;
            Lire_Car();
            break;

        case '/':
            SYM.CODE = DIV_TOKEN;
            Lire_Car();
            break;

        case ',':
            SYM.CODE = VIR_TOKEN;
            Lire_Car();
            break;

        case ':':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM.CODE = AFF_TOKEN;
                Lire_Car();
            }
           /* if (Car_Cour == "begin"||SYM.CODE  == ID_TOKEN||Car_Cour == "if"||Car_Cour == "while"||Car_Cour == "write"||Car_Cour == "read"||Car_Cour == "IF"||Car_Cour == "REPEAT"||Car_Cour == "FOR"||Car_Cour == "CASE")
            {
                SYM.CODE = INST_TOKEN;//: de l'instruction case
                Lire_Car();
            }*/

            else
            {
                SYM.CODE = PPT_TOKEN;//à ajouter
            }
            break;

        case '<':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM.CODE = INFEG_TOKEN;
                Lire_Car();
            }
            else if (Car_Cour == '>')
            {
                SYM.CODE = DIFF_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM.CODE = INF_TOKEN;
            }
            break;

        case '>':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM.CODE = SUPEG_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM.CODE = SUP_TOKEN;
            }
            break;

        case '(':
            SYM.CODE = PO_TOKEN;
            Lire_Car();
            break;
        case '=':
            SYM.CODE = EG_TOKEN;
            Lire_Car();
            break;

        case ')':
            SYM.CODE = PF_TOKEN;
            Lire_Car();
            break;

        case '.':
            SYM.CODE = PT_TOKEN;
            Lire_Car();
            break;

        case EOF:
            SYM.CODE = FIN_TOKEN;
            break;

        default:
            SYM.CODE = ERREUR_TOKEN;
            Lire_Car();
        }
    }
}

//===================== Lire_Car ==========================
void Lire_Car()
{
    Car_Cour = fgetc(fichier);
}

//===================== Erreur ==========================
void Erreur(CODES_ERR code)
{
    printf("Erreur: %d\n", code);
    printf("Current Token: %d\n", SYM.CODE);
    printf("Current Lexeme: %s\n", SYM.NOM);
    exit(EXIT_FAILURE);
}

//===================== Test_Symbole ==========================
void Test_Symbole(CODES cl, CODES_ERR COD_ERR)
{
    if (SYM.CODE == cl)
    {
        Sym_Suiv();
    }
    else
        Erreur(COD_ERR);
}

//===================== PROGRAM ==========================
void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();

    //Test_Symbole(PT_TOKEN, PT_ERR);
    // Check for the dot after BLOCK
    if (SYM.CODE == PT_TOKEN)
    {
        Sym_Suiv(); // Consume the dot
        printf("Program execution completed.\nBRAVO: le programme est correcte FIN PROGRAMME!!!");
    }
    else
    {
        Erreur(PT_ERR);
        printf("PAS BRAVO: fin de programme erron�e!!!!\n");

        // Add this line to consume symbols until the end of the file
        while (SYM.CODE != FIN_TOKEN)
        {
            printf("Current Token: %d\n", SYM.CODE);
            printf("Current Lexeme: %s\n", SYM.NOM);
            Sym_Suiv();
        }
    }
}

//===================== BLOCK ==========================
void BLOCK()
{
    CONSTS();

    VARS();
    INSTS();
}

//===================== CONST ==========================
void CONSTS()
{
    switch (SYM.CODE)
    {
    case CONST_TOKEN:
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        Test_Symbole(PV_TOKEN, PV_ERR);
        while (SYM.CODE == ID_TOKEN)
        {
            Sym_Suiv();
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(PV_TOKEN, PV_ERR);
        };
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
}

//===================== VARS ==========================
void VARS()
{
    switch (SYM.CODE)
    {
    case VAR_TOKEN:
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);

        while (SYM.CODE == VIR_TOKEN)
        {
            Sym_Suiv();
            Test_Symbole(ID_TOKEN, ID_ERR);
        }

        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(VAR_BEGIN_ERR);
        break;
    }
}

//===================== INSTS ==========================
void INSTS()
{
    //begin INST { ; INST } end
    if (SYM.CODE == BEGIN_TOKEN)
    {
        Sym_Suiv();
        INST();

        while (SYM.CODE == PV_TOKEN)
        {
            Sym_Suiv();
            INST();
        }

        if (SYM.CODE == END_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur(FIN_ERR);
        }
    }
    else
    {
        Erreur(BEGIN_ERR);
    }
}

//===================== INST ==========================
void INST()

{
    //INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM.CODE)
    {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:
        AFFEC();
        break;
    case IF_TOKEN:
        SI();
        break;
    case WHILE_TOKEN:
        TANTQUE();
        break;
    case WRITE_TOKEN:
        ECRIRE();
        break;
    case READ_TOKEN:
        LIRE();
        break;
    default:
        break;
    }
}

//===================== AFFEC ==========================
void AFFEC()
{
    //ID := EXPR
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    EXPR();
}

/*void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST();
}
*/

//===================== TANTQUE ==========================
void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
}

//===================== ECRIRE ==========================
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPR();

    while (SYM.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR();
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

//===================== LIRE ==========================
void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);

    while (SYM.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

//===================== SI ==========================
void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST();
    Test_Symbole(ID_TOKEN, ID_ERR);
    switch (SYM.CODE)
    {
    case ELSE_TOKEN://à ajouter
        Test_Symbole(ELSE_TOKEN, ELSE_ERR);
        INST();
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
}}

//===================== REPETER ==========================
void REPETER()
{
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR);//à AJOUTER
    INST();
    Test_Symbole(UNTIL_TOKEN, UNTIL_ERR);//à AJOUTER
    COND();
}

//===================== POUR ==========================
void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR);//à AJOUTER
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(DO_TOKEN, DO_ERR);
    AFFEC();
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    NTOP();
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
}

//===================== CAS ==========================
void CAS()
{
    Test_Symbole(CASE_TOKEN, CASE_ERR);//à AJOUTER
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(OF_TOKEN, OF_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(PPT_TOKEN, PPT_ERR);
    INST();

    while (SYM.CODE == NUM_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(PPT_TOKEN, PPT_ERR);
        INST();
    }
    switch (SYM.CODE)
    {
    case ELSE_TOKEN://à ajouter
        Test_Symbole(ELSE_TOKEN, ELSE_ERR);
        INST();
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
}
    Test_Symbole(END_TOKEN, END_ERR);



    Test_Symbole(PF_TOKEN, PF_ERR);
    switch (SYM.CODE)
    {
    case INTO_TOKEN://à ajouter
        Test_Symbole(INTO_TOKEN, INTO_ERR);
        break;
    case DOWNTO_TOKEN://à ajouter
        Test_Symbole(DOWNTO_TOKEN, DOWNTO_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
}

}

//===================== COND ==========================
void COND()
{
    EXPR();
    RELOP();
    EXPR();
}

//===================== EXPR ==========================
void EXPR()
{
    //TERM { ADDOP TERM }
    TERM();

    while (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN)
    {
        ADDOP();
        TERM();
    }
}

//===================== TERM ==========================
void TERM()
{
    FACT();

    while (SYM.CODE == MULT_TOKEN || SYM.CODE == DIV_TOKEN)
    {
        MULOP();
        FACT();
    }
}

//===================== FACT ==========================
void FACT()
{
    switch (SYM.CODE)
    {
    case ID_TOKEN:
        Test_Symbole(ID_TOKEN, ID_ERR);
        break;
    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        break;
    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR();
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//===================== RELOP ==========================
void RELOP()
{
    switch (SYM.CODE)
    {
    case EG_TOKEN:
    case DIFF_TOKEN:
    case INF_TOKEN:
    case SUP_TOKEN:
    case INFEG_TOKEN:
    case SUPEG_TOKEN:
        Test_Symbole(SYM.CODE, EG_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//===================== ADDOP ==========================
void ADDOP()
{
    switch (SYM.CODE)
    {
    case PLUS_TOKEN:
        Test_Symbole(SYM.CODE, PLUS_ERR);
        break;
    case MOINS_TOKEN:
        Test_Symbole(SYM.CODE, MOINS_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//===================== MULOP ==========================
void MULOP()
{
    switch (SYM.CODE)
    {
    case MULT_TOKEN:
        Test_Symbole(SYM.CODE, MULT_ERR);
        break;
    case DIV_TOKEN:
        Test_Symbole(SYM.CODE, DIV_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//===================== NTOP ==========================
void NTOP()
{
    switch (SYM.CODE)
    {
    case INTO_TOKEN:
        Test_Symbole(SYM.CODE,INTO_ERR);
        break;
    case DOWNTO_TOKEN:
        Test_Symbole(SYM.CODE, DOWNTO_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

//===================== main ==========================
int main()
{
    fichier = fopen("program.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // PREMIER_SYM();
    Lire_Car();
    Sym_Suiv();

    PROGRAM();

    printf("Program execution completed.\n");

    if (SYM.CODE == FIN_TOKEN)
    {
        printf("BRAVO: le programme est correcte on arrive a la fin !!!\n");
    }
    else
    {
        printf("PAS BRAVO: fin de programme errone!!!!\n");
        printf("Current Token: %d\n", SYM.CODE);
        printf("Current Lexeme: %s\n", SYM.NOM);
        Sym_Suiv(); // Move this line inside the else block
    }

    fclose(fichier);

    return 0;
}
