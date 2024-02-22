#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ID_TOKEN, PROGRAM_TOKEN,
    CONST_TOKEN, VAR_TOKEN,
    BEGIN_TOKEN, END_TOKEN,
    IF_TOKEN, THEN_TOKEN,
    WHILE_TOKEN, DO_TOKEN,
    READ_TOKEN, WRITE_TOKEN,
    PV_TOKEN, PT_TOKEN,
    PLUS_TOKEN, MOINS_TOKEN,
    MULT_TOKEN, DIV_TOKEN,
    VIR_TOKEN, AFF_TOKEN,
    INF_TOKEN, INFEG_TOKEN,
    SUP_TOKEN, SUPEG_TOKEN,
    DIFF_TOKEN, PO_TOKEN,
    PF_TOKEN, FIN_TOKEN,
    STRING_TOKEN,FLOAT_TOKEN,CHAR_TOKEN,BOOL_TOKEN,QUOTE_TOKEN,TP_TOKEN,COMMENTO_TOKEN,CBO_TOKEN,CBF_TOKEN,AND_TOKEN,OR_TOKEN,COMMENTF_TOKEN,
    TYPE_TOKEN,NOT_TOKEN,CROCHETO_TOKEN,CROCHETF_TOKEN,
    GOTO_TOKEN,ELSE_TOKEN,REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,TO_TOKEN,DOWNTO_TOKEN,WITH_TOKEN,
    LABEL_TOKEN,ARRAY_TOKEN,OF_TOKEN,RECORD_TOKEN,CASE_TOKEN,SETOF_TOKEN,FILEOF_TOKEN,PROCEDURE_TOKEN,FUNCTION_TOKEN,IN_TOKEN,DIVV_TOKEN,MOD_TOKEN,//div =/ et DIVV = div de BNF
    NUM_TOKEN, ERREUR_TOKEN, EOF_TOKEN,EG_TOKEN,DOTDOT_TOKEN,E_TOKEN,SET_TOKEN,FILE_TOKEN,INTEGER_TOKEN,
} CODES;


// erreur types
typedef enum
{

    PROGRAM_ERR,
    ID_ERR,
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
    STRING_ERR,
    FLOAT_ERR,
    CHAR_ERR,
    BOOL_ERR,
    QUOTE_ERR,
    TP_ERR,
    COMMENTO_ERR,
    CBO_ERR,
    CBF_ERR,
    AND_ERR,
    OR_ERR,
    COMMENTF_ERR,
    TYPE_ERR,
    NOT_ERR,
    CROCHETO_ERR,
    CROCHETF_ERR,
    GOTO_ERR,
    ELSE_ERR,
    REPEAT_ERR,
    UNTIL_ERR,
    FOR_ERR,
    TO_ERR,
    DOWNTO_ERR,
    WITH_ERR,
    LABEL_ERR,
    ARRAY_ERR,
    OF_ERR,
    RECORD_ERR,
    CASE_ERR,
    SETOF_ERR,
    FILEOF_ERR,
    PROCEDURE_ERR,
    FUNCTION_ERR,
    IN_ERR,
    DIVV_ERR,
    MOD_ERR,
    NUM_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    DOTDOT_ERR,
    E_ERR,
    SET_ERR,
    FILE_ERR,
    INTEGER_ERR,
} CODES_ERR;





typedef struct
{
    CODES CODE;
    char NOM[20];
    int VAL;
} Current_sym;

Current_sym SYM;
typedef enum {TPROG, TCONST, TVAR} TSYM;

//============================================= pour p-Code==================================
// Définition des constantes
#define TABLEINDEX 1000 // Taille du tableau TABLESYM


// Structure pour représenter un enregistrement dans TABLESYM
typedef struct {
    char NOM[50];
    TSYM CLASSE;
    int ADRESSE;
} ENREGISTREMENT;

// Définition du tableau TABLESYM
ENREGISTREMENT TABLESYM[TABLEINDEX];

// Définition de la variable OFFSET
int OFFSET;



// Définition des constantes
#define TAILLEMEM 100 // Taille du tableau MEM
#define TAILLECODE 100 // Taille du tableau PCODE

// Définition des mnémoniques
typedef enum {
    ADD, SUB, MUL, DIV, EQL, NEQ, GTR,
    LSS, GEQ, LEQ, PRN, INN, INT, LDI, LDA,
    LDV, STO, BRN, BZE, HLT
} MNEMONIQUES;

// Structure pour représenter une instruction
typedef struct {
    MNEMONIQUES MNE;
    int SUITE;
} INSTRUCTION;

// Définition des tableaux MEM et PCODE
int MEM[TAILLEMEM];
INSTRUCTION PCODE[TAILLECODE];

// Définition des variables SP et PC
int SP;
int PC;

// Fonction pour empiler sur la pile
void push(int value) {
    if (SP < TAILLEMEM) {
        MEM[SP] = value;
        SP++;
    } else {
        printf("Stack overflow!\n");
    }
}

int pop() {
    if (SP > 0) {
        SP--;
        return MEM[SP];
    } else {
        printf("Stack underflow!\n");
        return 0;  // Vous pouvez ajuster cela en fonction de vos besoins
    }
}

// Fonction pour générer une instruction
void GENERER1(MNEMONIQUES M) {
    // Vérifier si PC atteint la taille maximale
    if (PC == TAILLECODE) {
        printf("ERREUR : Tableau PCODE plein\n");
        return;
    }

    // Incrémenter PC et affecter le mnémonique à PCODE
    PC++;
    PCODE[PC].MNE = M;
}


// Fonction pour générer une instruction avec un argument
void GENERER2(MNEMONIQUES M, int A) {
    // Vérifier si PC atteint la taille maximale
    if (PC == TAILLECODE) {
        printf("ERREUR : Tableau PCODE plein\n");
        return;
    }

    // Incrémenter PC et affecter le mnémonique et l'argument à PCODE
    PC++;
    PCODE[PC].MNE = M;
    PCODE[PC].SUITE = A;
}
int IND_DER_SYM_ACC = 0;
int adresse_courante = 0;
int obtenir_adresse_constante() {
    return adresse_courante++;
}
// Fonction pour afficher le contenu du tableau PCODE
// Fonction pour afficher le contenu du tableau PCODE
void afficher_contenu_pile() {
    printf("Contenu de la pile :\n");
    for (int i = 0; i < SP; i++) {
        printf("%d ", MEM[i]);
    }
    printf("\n");

    printf("Instructions du p-code :\n");
    for (int i = 1; i <= PC; i++) {
        switch (PCODE[i].MNE) {
            case ADD:
                printf("ADD\n");
                break;
            case SUB:
                printf("SUB\n");
                break;
            case MUL:
                printf("MUL\n");
                break;
            case DIV:
                printf("DIV\n");
                break;
            case EQL:
                printf("EQL\n");
                break;
            case NEQ:
                printf("NEQ\n");
                break;
            case GTR:
                printf("GTR\n");
                break;
            case LSS:
                printf("LSS\n");
                break;
            case LEQ:
                printf("LEQ\n");
                break;
            case GEQ:
                printf("GEQ\n");
                break;
            case PRN:
                printf("PRN\n");
                break;
            case INN:
                printf("INN\n");
                break;
            case INT:
                printf("INT\n");
                break;
            case BRN:
                printf("BRN\n");
                break;
             case BZE:
                printf("BZE\n");
                break;
             case HLT:
                printf("HLT\n");
                break;


            // Ajoutez d'autres cas pour les autres mnémoniques selon vos besoins

            case LDI:
                printf("LDI %d\n", PCODE[i].SUITE);
                break;
            case LDA:
                printf("LDA %d\n", PCODE[i].SUITE);
                break;
            case LDV:
                printf("LDV %d\n", PCODE[i].SUITE);
                break;
            case STO:
                printf("STO\n");
                break;
            // Ajoutez d'autres cas pour les mnémoniques avec un argument

            default:
                printf("Instruction inconnue\n");
                break;
        }
    }
}

//===================================================================================


// ============================= table de symboles =====================================

typedef struct {
    char NOM[20];
    TSYM TIDF;
} T_TAB_IDF;

T_TAB_IDF TAB_IDFS[100];
int TIDFS_indice = 0;

// =======================================================================================
int ligne_actuelle = 1;

FILE *fichier;

char Car_Cour; // caract�re courant


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

    // Ajout du caract�re de fin de chaine
    mot[indice] = '\0';

    // Verifier si le mot est un mot-cle
    if (stricmp(mot, "program") == 0) { SYM.CODE = PROGRAM_TOKEN; }
    else if (stricmp(mot, "set") == 0) { SYM.CODE = SET_TOKEN; }
    else if (stricmp(mot, "const") == 0) { SYM.CODE = CONST_TOKEN; }
    else if (stricmp(mot, "var") == 0) { SYM.CODE = VAR_TOKEN; }
    else if (stricmp(mot, "boolean") == 0) { SYM.CODE = BOOL_TOKEN; }
    else if (stricmp(mot, "begin") == 0) { SYM.CODE = BEGIN_TOKEN; }
    else if (stricmp(mot, "end") == 0) { SYM.CODE = END_TOKEN; }
    else if (stricmp(mot, "if") == 0) { SYM.CODE = IF_TOKEN; }
    else if (stricmp(mot, "writeln") == 0) { SYM.CODE = WRITE_TOKEN; }
    else if (stricmp(mot, "file") == 0) { SYM.CODE = FILE_TOKEN; }
    else if (stricmp(mot, "then") == 0) { SYM.CODE = THEN_TOKEN; }
    else if (stricmp(mot, "while") == 0) { SYM.CODE = WHILE_TOKEN; }
    else if (stricmp(mot, "E") == 0) { SYM.CODE = E_TOKEN; }
    else if (stricmp(mot, "do") == 0) { SYM.CODE = DO_TOKEN; }
    else if (stricmp(mot, "readln") == 0) { SYM.CODE = READ_TOKEN; }
    else if (stricmp(mot, "string") == 0) { SYM.CODE = STRING_TOKEN; }
    else if (stricmp(mot, "real") == 0) { SYM.CODE = FLOAT_TOKEN; }
    else if (stricmp(mot, "integer") == 0) { SYM.CODE = INTEGER_TOKEN; }
    else if (stricmp(mot, "char") == 0) { SYM.CODE = CHAR_TOKEN; }
    else if (stricmp(mot, "and") == 0) { SYM.CODE = AND_TOKEN; }
    else if (stricmp(mot, "or") == 0) { SYM.CODE = OR_TOKEN; }
    else if (stricmp(mot, "goto") == 0) { SYM.CODE = GOTO_TOKEN; }
    else if (stricmp(mot, "else") == 0) { SYM.CODE = ELSE_TOKEN; }
    else if (stricmp(mot, "repeat") == 0) { SYM.CODE = REPEAT_TOKEN; }
    else if (stricmp(mot, "until") == 0) { SYM.CODE = UNTIL_TOKEN; }
    else if (stricmp(mot, "for") == 0) { SYM.CODE = FOR_TOKEN; }
    else if (stricmp(mot, "to") == 0) { SYM.CODE = TO_TOKEN; }
    else if (stricmp(mot, "downto") == 0) { SYM.CODE = DOWNTO_TOKEN; }
    else if (stricmp(mot, "with") == 0) { SYM.CODE = WITH_TOKEN; }
    else if (stricmp(mot, "type") == 0) { SYM.CODE = TYPE_TOKEN; }
    else if (stricmp(mot, "label") == 0) { SYM.CODE = LABEL_TOKEN; }
    else if (stricmp(mot, "array") == 0) { SYM.CODE = ARRAY_TOKEN; }
    else if (stricmp(mot, "of") == 0) { SYM.CODE = OF_TOKEN; }
    else if (stricmp(mot, "record") == 0) { SYM.CODE = RECORD_TOKEN; }
    else if (stricmp(mot, "case") == 0) { SYM.CODE = CASE_TOKEN; }
    else if (stricmp(mot, "setof") == 0) { SYM.CODE = SETOF_TOKEN; }
    else if (stricmp(mot, "fileof") == 0) { SYM.CODE = FILEOF_TOKEN; }
    else if (stricmp(mot, "procedure") == 0) { SYM.CODE = PROCEDURE_TOKEN; }
    else if (stricmp(mot, "function") == 0) { SYM.CODE = FUNCTION_TOKEN; }
    else if (stricmp(mot, "in") == 0) { SYM.CODE = IN_TOKEN; }
    else if (stricmp(mot, "div") == 0) { SYM.CODE = DIVV_TOKEN; }
    else if (stricmp(mot, "mod") == 0) { SYM.CODE = MOD_TOKEN; }
    else { SYM.CODE = ID_TOKEN; }


    // Stockage du mot dans le jeton
    strcpy(SYM.NOM, mot);
}


//===================== Lire_nombre ==========================
void lire_nombre() {
    char nombre[11];
    int indice = 0;
    int hasDecimal = 0; // Variable pour indiquer si le nombre contient un point décimal

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour) || Car_Cour == '.') {
        if (Car_Cour == '.') {
            // Vérifier s'il y a déjà un point décimal
            if (hasDecimal) {
                // Gérer l'erreur (deux points décimaux dans le nombre)
                // Vous pouvez ajuster cette partie selon la logique de gestion d'erreur que vous souhaitez
                // Par exemple, afficher un message d'erreur et sortir de la fonction
                printf("Erreur: Nombre mal formé\n");
                return;
            }
            hasDecimal = 1; // Indiquer que le nombre contient un point décimal
        }

        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    if (hasDecimal) {
        SYM.CODE = FLOAT_TOKEN;
    } else {
        SYM.CODE = NUM_TOKEN;
    }

    strcpy(SYM.NOM, nombre);
    SYM.VAL = atoi(SYM.NOM);
}


char Lire_Char() {
    Car_Cour = fgetc(fichier);
    return Car_Cour;
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
                Lire_Car();
                if (Car_Cour == ')'||Car_Cour == '}') {
                    SYM.CODE = COMMENTF_TOKEN;
                    Lire_Car();
                }else {
                    SYM.CODE = MULT_TOKEN;

                }
                break;

            case '/':
                Lire_Car();
                if (Car_Cour == '/') {
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = DIV_TOKEN;
                }
                break;
            case '\'':
                SYM.CODE = QUOTE_TOKEN;
                Lire_Car();
                break;

            case '{':
                Lire_Car();
                if (Car_Cour == '*') {
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = CBO_TOKEN;
                }
                break;
            case '.':
    Lire_Car();
    if (Car_Cour == '.') {
        SYM.CODE = DOTDOT_TOKEN;
        Lire_Car(); // Consommer le deuxième point
    } else {
        SYM.CODE = PT_TOKEN;
    }
    break;
            case ',':
                SYM.CODE = VIR_TOKEN;
                Lire_Car();
                break;
            case '}':
                SYM.CODE = CBF_TOKEN;
                Lire_Car();
                break;

            case ':':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM.CODE = AFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = TP_TOKEN;
                }
                break;

            case '<':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM.CODE = INFEG_TOKEN;
                    Lire_Car();
                } else if (Car_Cour == '>') {
                    SYM.CODE = DIFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = INF_TOKEN;
                }
                break;

            case '>':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM.CODE = SUPEG_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = SUP_TOKEN;
                }
                break;

            case '(':
                Lire_Car();
                if (Car_Cour == '*') {
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else {
                    SYM.CODE = PO_TOKEN;
                }
                break;
            case '=':
                SYM.CODE = EG_TOKEN;
                Lire_Car();
                break;

            case ')':
                SYM.CODE = PF_TOKEN;
                Lire_Car();
                break;
            case '[':
                SYM.CODE = CROCHETO_TOKEN;
                Lire_Car();
                break;

            case ']':
                SYM.CODE = CROCHETF_TOKEN;
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
    if (Car_Cour == '\n') {
        ligne_actuelle++; // Incrémentation du numéro de ligne en cas de saut de ligne
    }
}
//===================== Erreur ==========================
void Erreur(CODES_ERR code)
{
    printf("Erreur à la ligne %d: %d\n", ligne_actuelle, code);

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

    // l'identifiant de program est ajoute dans la table d'identifiants
    strncpy(TAB_IDFS[TIDFS_indice].NOM, SYM.NOM, sizeof(TAB_IDFS[TIDFS_indice].NOM) - 1);
    TAB_IDFS[TIDFS_indice].NOM[sizeof(TAB_IDFS[TIDFS_indice].NOM) - 1] = '\0';
    TAB_IDFS[TIDFS_indice].TIDF = TPROG;
    TIDFS_indice++;

    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();
    GENERER1(HLT);
      printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");


    //Test_Symbole(PT_TOKEN, PT_ERR);
    // Check for the dot after BLOCK
   /* if (SYM.CODE == PT_TOKEN)
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
    }*/
}
//===================== BLOCK ==========================

void BLOCK()
{
         OFFSET = 0;
    label_declaration_part();//consts();
    constant_definition_part();//VARS();
    type_definition_part();//INSTS*
    variable_declaration_part();
    PCODE[0].MNE = INT;
    PCODE[0].SUITE = OFFSET;
    procedure_and_function_declaration_part();

    INSTS();
   // statement_part();
}
//===================== label declaration part ==========================
void label_declaration_part() {
    if (SYM.CODE == LABEL_TOKEN) {
        Sym_Suiv(); // Consommer le token "label"
        label();    // Appeler la fonction pour analyser un label

        // Ensuite, analysez les virgules suivies de labels
        while (SYM.CODE == VIR_TOKEN) {
            Sym_Suiv(); // Consommer le token ","
            if (SYM.CODE == NUM_TOKEN) {
                label();    // Analyser le prochain label
            } else {
                // Gérer une erreur si le token suivant n'est pas un nombre
                printf("Erreur : Nombre attendu après ',' dans la déclaration de label\n");
                Erreur(NUM_ERR);
            }
        }
        if (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le token ";"
        } else {
            // Gérer une erreur si le ";"
            printf("Erreur : ';' attendu après la déclaration de label\n");
            Erreur(PV_ERR);
        }
    } else {
                  // Sym_Suiv(); // Consommer le token ";"

    }
}
//===================== LABEL ===========================
void label() {
    if (SYM.CODE == NUM_TOKEN) {
        // Traitement du label
        // Ici, vous pouvez stocker ou utiliser la valeur du label
        Sym_Suiv(); // Consommer le token NUM
    }
    if (SYM.CODE == ID_TOKEN) {
        // Traitement du label
        // Ici, vous pouvez stocker ou utiliser la valeur du label
        Sym_Suiv(); // Consommer le token NUM
    }  else {
        // Gérer une erreur si le token n'est pas un entier non signé
        printf("Erreur : Entier non signé attendu dans la déclaration de label\n");
        Erreur(NUM_ERR);
    }
}
//===================== STRING ===========================
/*
void string() {
    if (SYM.CODE == QUOTE_TOKEN) {
        Sym_Suiv(); // Consommer le token "'"
        char caractere = Lire_Char();
        while (caractere != QUOTE_TOKEN) {
            caractere = Lire_Car();
        }
        Sym_Suiv(); // Consommer le guillemet simple de fin de chaîne
    } else {
        // Gérer une erreur si la chaîne ne commence pas par un guillemet simple
        printf("Erreur : Début de la chaîne de caractères attendu\n");
        Erreur(QUOTE_ERR);
    }
}
*/
//===================== constant_definition_part ==========================

// Implémentation de la production <constant definition part>
void constant_definition_part() {

    if (SYM.CODE == CONST_TOKEN) {
        Sym_Suiv(); // Consommer le token "const"

        constant_definition(); // Appeler la fonction pour traiter la première définition de constante

        // Ensuite, analysez les autres définitions de constantes séparées par des points-virgules
        while (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le token ";"

            constant_definition(); // Analyser la prochaine définition de constante


        }



       /* if (SYM.CODE != PV_TOKEN) {
            // Gérer une erreur si le dernier token n'est pas ";"
            printf("Erreur : ';' attendu après la définition des constantes\n");
            Erreur(PV_ERR);
        }*/
    }
               // Sym_Suiv();
}

//===================== constant_definition ==========================
// Fonction pour analyser une définition de constante
void constant_definition() {
    if (SYM.CODE == ID_TOKEN) {
            // l'identifiant de la variable est ajoute dans la table d'identifiants---------
            //first, check if this identifier already exists
            illegal_program_name(SYM.NOM);
            double_declaration(SYM.NOM, TCONST);
            // ---------------------- fin partie table d'identifiants / semantique ---------------------
             int adresse_constante = obtenir_adresse_constante();
             TABLESYM[IND_DER_SYM_ACC].ADRESSE = adresse_constante;

        // Après avoir obtenu l'adresse, générez le p-code pour cette constante
             GENERER2(LDA, adresse_constante);
           //GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC++].ADRESSE);
            Sym_Suiv(); // Consommer le token identifiant

            if (SYM.CODE == EG_TOKEN) {
                Sym_Suiv(); // Consommer le token "="
                // Vérifier si la constante est une valeur directe
                if (SYM.CODE == NUM_TOKEN || SYM.CODE == STRING_TOKEN || SYM.CODE == CHAR_TOKEN || SYM.CODE == FLOAT_TOKEN ) {
                    GENERER2(LDI, SYM.VAL);
                    GENERER1(STO);
                    Sym_Suiv(); // Consommer la constante directe


                } else {
                    // Si ce n'est pas une constante directe, analyser la constante associée
                    constant(); // Analyser la constante associée

                }
            } else {
                // Gérer une erreur si le token suivant n'est pas "="
                printf("Erreur : '=' attendu dans la définition de constante\n");
                Erreur(EG_ERR);
            }
    } else {
                       // Sym_Suiv();

        // Gérer une erreur si le token n'est pas un identifiant
       // printf("Erreur : Identifiant attendu dans la définition de constante\n");
       // Erreur(TP_ERR);
    }
    // Ajouter du code pour afficher le p-code généré pour cette instruction
  /*  printf("=== P-Code de la définition de constante ===\n");
    printf("LDA %d\n", TABLESYM[IND_DER_SYM_ACC].ADRESSE);
    printf("LDI %d\n", SYM.VAL);
    printf("STO\n");
    printf("===========================================\n");*/
   /*/ printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
}
//===================== constant ==========================
// Fonction pour analyser une constante
void constant() {
    if (SYM.CODE == NUM_TOKEN ||SYM.CODE == FLOAT_TOKEN ) {
            GENERER2(LDI, SYM.VAL);
    } else if (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN||SYM.CODE == ID_TOKEN || SYM.CODE == CHAR_TOKEN) {
        // Pas besoin de Sym_Suiv() ici non plus
        if (SYM.CODE == ID_TOKEN) {
            // Pas besoin de Sym_Suiv() ici non plus
        } else {
            // Gérer une erreur si le token suivant n'est pas un identifiant
            printf("Erreur : Identifiant attendu après le signe dans la constante\n");
            Erreur(TP_ERR);
        }
    }
    else if (SYM.CODE == QUOTE_TOKEN) {
        string();
    }else {
        // Gérer une erreur si le token n'est pas une constante valide
        printf("Erreur : Constante invalide dans la définition de constante\n");
        Erreur(CONST_ERR);
    }
    GENERER1(STO);
    // Ajouter du code pour afficher le p-code généré pour cette instruction
   /* printf("=== P-Code de la définition de constante ===\n");
    printf("LDA %d\n", TABLESYM[IND_DER_SYM_ACC].ADRESSE);
    printf("LDI %d\n", SYM.VAL);
    printf("STO\n");
    printf("===========================================\n");*/
  /*  printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/

}
//===================== unsigned_number ==========================
// Implémentation de la production <unsigned number>
void unsigned_number() {
    if (SYM.CODE == NUM_TOKEN) {
        // Si le token actuel est un nombre, c'est un nombre non signé
        Sym_Suiv();
    } else if (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN || SYM.CODE == ID_TOKEN || SYM.CODE == QUOTE_TOKEN) {
        // Sinon, c'est une constante identifiée, un signe ou une chaîne de caractères
        constant_identifier();
    } else {
        // Gérer une erreur si le token n'est pas un nombre, un identifiant ou un signe
        printf("Erreur : Nombre, identifiant, signe ou chaîne de caractères attendu\n");
        Erreur(NUM_ERR);
    }
}
//===================== unsigned_integer ==========================

// Implémentation de la production <unsigned integer>
void unsigned_integer() {
    if (SYM.CODE == NUM_TOKEN) {
        // Si le token actuel est un nombre, c'est un entier non signé
        Sym_Suiv();
    } else {
        // Gérer une erreur si le token n'est pas un nombre
        printf("Erreur : Nombre attendu dans l'entier non signé\n");
        Erreur(NUM_ERR);
    }
}
//===================== unsigned_real ==========================

// Implémentation de la production <unsigned real>
void unsigned_real() {
    unsigned_integer(); // Un nombre non signé est requis avant le point décimal

    if (SYM.CODE == PT_TOKEN) {
        Sym_Suiv(); // Consommer le token "."
        unsigned_integer(); // Analyser la partie fractionnaire

        if (SYM.CODE == E_TOKEN) {
            Sym_Suiv(); // Consommer le token "E"
            scale_factor(); // Analyser le facteur d'échelle
        }
    }
}
//===================== scale_factor ==========================

// Implémentation de la production <scale factor>
void scale_factor() {
    if (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN || SYM.CODE == NUM_TOKEN) {
        // Si le token est un signe ou un nombre, c'est un facteur d'échelle valide
        sign();
        unsigned_integer();
    } else {
        // Gérer une erreur si le token n'est pas un signe ou un nombre
        printf("Erreur : Signe ou nombre attendu dans le facteur d'échelle\n");
        Erreur(NUM_ERR);
    }
}
//===================== sign ==========================

// Implémentation de la production <sign>
void sign() {
    if (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN) {
        Sym_Suiv(); // Consommer le signe
    } else {
        // Gérer une erreur si le token n'est pas un signe
        printf("Erreur : Signe attendu\n");
        Erreur(NUM_ERR);
    }
}
//===================== constant_identifier ==========================
// Implémentation de la production <constant identifier>
void constant_identifier() {
    if (SYM.CODE == ID_TOKEN || SYM.CODE == QUOTE_TOKEN) {
        // Si le token actuel est un identifiant ou une chaîne de caractères, c'est une constante identifiée
        Sym_Suiv();
    } else {
        // Gérer une erreur si le token n'est pas un identifiant ou une chaîne de caractères
        printf("Erreur : Identifiant ou chaîne de caractères attendu dans la constante identifiée\n");
        Erreur(ID_ERR);
    }
}
//===================== string ==========================
// Implémentation de la production <string>
void string() {
    if (SYM.CODE == QUOTE_TOKEN) {
        // Si le token actuel est une quote, cela signifie que nous commençons une chaîne de caractères
        Sym_Suiv(); // Consommer la quote

        while (SYM.CODE != QUOTE_TOKEN && SYM.CODE != FIN_TOKEN) {
            // Tant que nous n'avons pas rencontré une autre quote ou la fin du fichier, nous consommons les caractères de la chaîne de caractères
            printf(SYM.NOM);
            printf("\n");
            Sym_Suiv();
        }

        if (SYM.CODE == QUOTE_TOKEN) {
            Sym_Suiv(); // Consommer la quote fermante
        } else {
            // Gérer une erreur si nous n'avons pas trouvé la quote fermante
            printf("Erreur : Quote fermante attendue pour la chaîne de caractères\n");
        Erreur(QUOTE_ERR);
        }
    } else {
        // Gérer une erreur si le token actuel n'est pas une quote
        printf("Erreur : Quote attendue pour commencer la chaîne de caractères\n");
        Erreur(QUOTE_ERR);
    }
}

void type_definition_part() {
    // Vérifier si le token actuel est "type"
    if (SYM.CODE == TYPE_TOKEN) {
        // Consommer le token "type"
        Sym_Suiv();
        // Analyser la définition du type
                  //  printf("j'entre avant le while \n ");

        type_definition();

        // Tant qu'on trouve des points-virgules et que le prochain symbole n'est pas une déclaration de procédure ou de fonction, analysons les définitions de type suivantes
        while (SYM.CODE == PV_TOKEN && SYM.CODE != PROCEDURE_TOKEN && SYM.CODE != FUNCTION_TOKEN) {
            Sym_Suiv(); // Consommer le point-virgule
          //  printf("j'entre de while \n ");
            if (SYM.CODE != PROCEDURE_TOKEN && SYM.CODE != FUNCTION_TOKEN && SYM.CODE != LABEL_TOKEN && SYM.CODE != CONST_TOKEN && SYM.CODE != VAR_TOKEN){
            type_definition(); // Analyser la définition de type suivante
        }
    }
        // Pas besoin de consommer le dernier point-virgule ici, car la boucle s'arrête lorsque le prochain symbole n'est pas un point-virgule
    } else {
        // Si aucun token de type n'est présent, la production est vide
        // Aucune action requise
    }
}

void type_definition() {
    if (SYM.CODE == ID_TOKEN) {
        // Si le token actuel est un identifiant, c'est la définition d'un type
        Sym_Suiv(); // Consommer l'identifiant

        // Vérifier le signe "="
        if (SYM.CODE != EG_TOKEN) {
            printf("Erreur : Signe '=' attendu dans la définition de type\n");
            Erreur(EG_ERR);
        }

        Sym_Suiv(); // Consommer le signe "="

        // Analyser le type
        type();
    } else {
        // Gérer une erreur si l'identifiant n'est pas présent
        printf("Erreur : Identifiant attendu dans la définition de type\n");
        Erreur(ID_ERR);
    }
}
//===================== type ==========================
void type() {
    printf(SYM.NOM);
    printf("\n");
    if (SYM.CODE == INTEGER_TOKEN || SYM.CODE == FLOAT_TOKEN || SYM.CODE == CHAR_TOKEN || SYM.CODE == STRING_TOKEN || SYM.CODE == BOOL_TOKEN ||SYM.CODE == ID_TOKEN) {
        Sym_Suiv(); // Avance au prochain symbole après le type prédéfini
    }else if (SYM.CODE == PO_TOKEN) {
        // Consommer "("
        Sym_Suiv();

        // Appeler la fonction de type scalaire
        scalar_type();

        // Vérifier si le prochain jeton est ")"
        if (SYM.CODE == PF_TOKEN) {
            // Consommer ")"
            Sym_Suiv();
        } else {
            // Si le prochain jeton n'est pas ")", signaler une erreur
            printf("Erreur : Symbole ')' attendu\n");
            Erreur(PF_ERR);
        }
    }
    else if (SYM.CODE == CONST_TOKEN) {
        // Appeler la fonction de type sous-gamme
        subrange_type();
    } else if (SYM.CODE == ID_TOKEN) {
        // Appeler la fonction de type identifiant
        Sym_Suiv();
        // Vérifier si le jeton suivant est un point-virgule (PT_TOKEN)
        if (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le PT_TOKEN
        } else {
            // Si le jeton suivant n'est pas un point-virgule, signaler une erreur
            printf("Erreur : Symbole ';' attendu après l'identifiant\n");
            Erreur(PV_ERR);
        }
    } else if (SYM.CODE == ARRAY_TOKEN) {
        // Appeler la fonction de type tableau
        array_type();
    } else if (SYM.CODE == RECORD_TOKEN) {
        // Appeler la fonction de type enregistrement
        record_type();
    } else if (SYM.CODE == SET_TOKEN) {
        // Appeler la fonction de type ensemble
        set_type();
    } else if (SYM.CODE == FILE_TOKEN) {
        // Appeler la fonction de type fichier
        file_type();
    } else {
        // Si le prochain jeton ne correspond à aucun type, signaler une erreur
        printf("Erreur : Type attendu\n");
        Erreur(TYPE_ERR);
    }
}

//===================== simple_type ==========================
void simple_type() {
    // Vérifier si le type est un type scalaire, un type de plage ou un identifiant de type
    if (SYM.CODE == PO_TOKEN) { scalar_type(); }
    else if (SYM.CODE == NUM_TOKEN) { subrange_type(); }
    else if (SYM.CODE == ID_TOKEN) { type_identifier(); }
    else {
        // Si aucun des cas ci-dessus n'est vrai, signaler une erreur
        printf("Erreur : Type scalaire, de plage ou identifiant de type attendu\n");
        Erreur(TYPE_ERR);
    }
}

//===================== field_identifier ==========================

void field_identifier() {
    // Vérifier si le jeton actuel est un identifiant
    if (SYM.CODE == ID_TOKEN) {
        // Récupérer l'identifiant et effectuer toute autre action nécessaire
        // Passer au jeton suivant
        Sym_Suiv();
    } else {
        // Si le jeton actuel n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant de champ attendu\n");
        Erreur(ID_ERR);
    }
}

//===================== scalar_type ==========================
void scalar_type() {
    // Appeler la fonction de l'identifiant
    variable_identifier();

    // Tant que nous trouvons une virgule, lire d'autres identifiants de variables
    while (SYM.CODE == VIR_TOKEN) {
        // Consommer la virgule
        Sym_Suiv();

        // Appeler la fonction de l'identifiant
        variable_identifier();
    }
}
//===================== variable_identifier ==========================

void variable_identifier() {
    // Vérifier si le jeton actuel est un identifiant
    if (SYM.CODE == ID_TOKEN) { Sym_Suiv(); } // Consommer l'identifiant en passant au jeton suivant
    else {
        Erreur(ID_ERR); // Utilisation de la fonction Erreur pour signaler l'erreur

        // Si le jeton actuel n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant attendu variable identifier\n");
        Erreur(ID_ERR);
    }
}
//===================== subrange_type ==========================
void subrange_type() {
    // Appeler la fonction de constante
    constant();
    Sym_Suiv();

    // Vérifier si le prochain jeton est ".."
    if (SYM.CODE == DOTDOT_TOKEN) {
        // Consommer ".."
        Sym_Suiv();

        // Appeler la fonction de constante
        constant();
    } else {
        // Si le prochain jeton n'est pas "..", signaler une erreur
        printf("Erreur : Symbole '..' attendu\n");
        Erreur(DOTDOT_ERR);
    }
}
//===================== type_identifier ==========================
void type_identifier() {
    // Vérifier si le prochain jeton est un identifiant
    if (SYM.CODE == ID_TOKEN) { Sym_Suiv(); } // Consommer l'identifiant
    else {
        // Si le prochain jeton n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant de type attendu\n");
        Erreur(ID_ERR);
    }
}
//===================== structured_type ==========================
void structured_type() {
    // Vérifier si le type est un type tableau, un type enregistrement, un ensemble ou un fichier
    if (SYM.CODE == ARRAY_TOKEN) { array_type();}
    else if (SYM.CODE == RECORD_TOKEN) { record_type(); }
    else if (SYM.CODE == SETOF_TOKEN) { set_type(); }
    else if (SYM.CODE == FILEOF_TOKEN) { file_type(); }
    else {
        // Si aucun des cas ci-dessus n'est vrai, signaler une erreur
        printf("Erreur : Type structuré attendu\n");
        Erreur(TYPE_ERR);
    }
}
//===================== array_type ==========================
void array_type() {
    // Vérifier si le prochain jeton est "array"
    if (SYM.CODE == ARRAY_TOKEN) {
        // Consommer "array"
        Sym_Suiv();

        // Vérifier si le prochain jeton est "["
        if (SYM.CODE == CROCHETO_TOKEN) {
            // Consommer "["
            Sym_Suiv();

            // Appeler la fonction de type d'index
            index_type();
            Sym_Suiv();

            // Tant que nous trouvons une virgule, lire d'autres types d'index
            while (SYM.CODE == VIR_TOKEN) {
                // Consommer ","
                Sym_Suiv();

                // Appeler la fonction de type d'index
                index_type();
            }

            // Vérifier si le prochain jeton est "]"
            if (SYM.CODE == CROCHETF_TOKEN) { Sym_Suiv(); } // Consommer "]"
            else {
                // Si le prochain jeton n'est pas "]", signaler une erreur
                printf("Erreur : Symbole ']' attendu\n");
                Erreur(CROCHETF_ERR);
            }

            // Vérifier si le prochain jeton est "of"
            if (SYM.CODE == OF_TOKEN) {
                // Consommer "of"
                Sym_Suiv();

                // Appeler la fonction du type de composant
                component_type();
            } else {
                // Si le prochain jeton n'est pas "of", signaler une erreur
                printf("Erreur : Mot-clé 'of' attendu\n");
                Erreur(OF_ERR);
            }
        } else {
            // Si le prochain jeton n'est pas "[", signaler une erreur
            printf("Erreur : Symbole '[' attendu\n");
            Erreur(CROCHETO_ERR);
        }
    } else {
        // Si le prochain jeton n'est pas "array", signaler une erreur
        printf("Erreur : Mot-clé 'array' attendu\n");
        Erreur(ARRAY_ERR);
    }
}

//===================== index_type ==========================
void index_type() {
    // Appeler la fonction de type simple
    simple_type();
}

//===================== component_type ==========================
void component_type() {
    // Appeler la fonction de type
    type();
}

//===================== record_type ==========================
void record_type() {
    // Vérifier si le prochain jeton est "record"
    if (SYM.CODE == RECORD_TOKEN) {
        // Consommer "record"
        Sym_Suiv();

        // Appeler la fonction de liste de champs
        field_list();

        // Vérifier si le prochain jeton est "end"
        if (SYM.CODE == END_TOKEN) { Sym_Suiv(); } // Consommer "end"
        else {
            // Si le prochain jeton n'est pas "end", signaler une erreur
            printf("Erreur : Mot-clé 'end' attendu\n");
            Erreur(END_ERR);
        }
    } else {
        // Si le prochain jeton n'est pas "record", signaler une erreur
        printf("Erreur : Mot-clé 'record' attendu\n");
        Erreur(RECORD_ERR);
    }
}

//===================== field_list ==========================
void field_list() {
    // Appeler la fonction de partie fixe
    fixed_part();

    // Vérifier si le prochain jeton est ";"
    if (SYM.CODE == PV_TOKEN) {
        // Consommer ";"
        Sym_Suiv();

        // Vérifier s'il y a une partie suivante
        if (SYM.CODE == CASE_TOKEN || SYM.CODE == ID_TOKEN) {
            // Appeler la partie suivante (peut être une partie fixe ou une partie variante)
            Sym_Suiv();
            if (SYM.CODE == CASE_TOKEN) { variant_part(); } // Appeler la fonction de partie variante
            else { field_list(); } // Si ce n'est pas la partie variante, c'est une autre partie fixe
        }
    }
}

//===================== fixed_part ==========================
void fixed_part() {
    // Appeler la fonction de section d'enregistrement
    record_section();

    // Tant que nous trouvons un point-virgule, lire d'autres sections d'enregistrement
    while (SYM.CODE == PV_TOKEN) {
        // Consommer le point-virgule
        Sym_Suiv();

        // Appeler la fonction de section d'enregistrement
        record_section();
    }
}

//===================== record_section ==========================
void record_section() {
    // Vérifier si le prochain jeton est un identifiant de champ
    if (SYM.CODE != ID_TOKEN) {
        // Si le prochain jeton n'est pas un identifiant, cela signifie que la section est vide
        return;
    }

    // Appeler la fonction d'identifiant de champ
    field_identifier();

    // Tant que nous trouvons une virgule, lire d'autres identifiants de champ
    while (SYM.CODE == VIR_TOKEN) {
        // Consommer la virgule
        Sym_Suiv();

        // Appeler la fonction d'identifiant de champ
        field_identifier();
    }

    // Vérifier si le prochain jeton est ":"
    if (SYM.CODE == TP_TOKEN) {
        // Consommer ":"
        Sym_Suiv();

        // Appeler la fonction de type
        type();
    } else {
        // Si le prochain jeton n'est pas ":", signaler une erreur
        printf("Erreur : Symbole ':' attendu\n");
        exit(1);
    }
}


//===================== variant_part ==========================
void variant_part() {
    // Vérifier si la partie variante est vide
    if (SYM.CODE == CASE_TOKEN) {
        // Consommer "case"
        Sym_Suiv();

        // Appeler la fonction de champ d'étiquette
        tag_field();

        // Appeler la fonction de type d'identifiant
        type_identifier();

        // Vérifier si le prochain jeton est "of"
        if (SYM.CODE == OF_TOKEN) {
            // Consommer "of"
            Sym_Suiv();

            // Appeler la fonction de variante
            variant();

            // Tant que nous trouvons un point-virgule, lire d'autres variantes
            while (SYM.CODE == PV_TOKEN) {
                // Consommer le point-virgule
                Sym_Suiv();

                // Appeler la fonction de variante
                variant();
            }
        } else {
            // Si le prochain jeton n'est pas "of", signaler une erreur
            printf("Erreur : Mot-clé 'of' attendu\n");
            exit(1);
        }
    } else {
        // Si le prochain jeton n'est pas "case", signaler une erreur
        printf("Erreur : Mot-clé 'case' attendu\n");
        exit(1);
    }
}

//===================== tag_field ==========================
void tag_field() {
    // Vérifier si le prochain jeton est un identifiant
    if (SYM.CODE == ID_TOKEN) {
        // Consommer l'identifiant
        Sym_Suiv();

        // Vérifier si le prochain jeton est ":"
        if (SYM.CODE == TP_TOKEN) {
            // Consommer ":"
            Sym_Suiv();
        } else {
            // Si le prochain jeton n'est pas ":", signaler une erreur
            printf("Erreur : Symbole ':' attendu\n");
            exit(1);
        }
    } else {
        // Si le prochain jeton n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant attendu\n");
        exit(1);
    }
}
//===================== variant ==========================
void variant() {
    // Vérifier si la variante est vide
    if (SYM.CODE == CASE_TOKEN) {
        // Appeler la fonction de liste d'étiquettes de cas
        case_label_list();

        // Vérifier si le prochain jeton est ":"
        if (SYM.CODE == TP_TOKEN) {
            // Consommer ":"
            Sym_Suiv();

            // Vérifier si le prochain jeton est "("
            if (SYM.CODE == PO_TOKEN) {
                // Consommer "("
                Sym_Suiv();

                // Appeler la fonction de liste de champs
                field_list();

                // Vérifier si le prochain jeton est ")"
                if (SYM.CODE == PF_TOKEN) {
                    // Consommer ")"
                    Sym_Suiv();
                } else {
                    // Si le prochain jeton n'est pas ")", signaler une erreur
                    printf("Erreur : Symbole ')' attendu\n");
                    exit(1);
                }
            } else {
                // Si le prochain jeton n'est pas "(", signaler une erreur
                printf("Erreur : Symbole '(' attendu\n");
                exit(1);
            }
        } else {
            // Si le prochain jeton n'est pas ":", signaler une erreur
            printf("Erreur : Symbole ':' attendu\n");
            exit(1);
        }
    } else {
        // Si le prochain jeton n'est pas "case", signaler une erreur
        printf("Erreur : Mot-clé 'case' attendu\n");
        exit(1);
    }
}
//===================== case_label_list ==========================
void case_label_list() {
    // Vérifier si la liste d'étiquettes de cas est vide
    if (SYM.CODE != CASE_TOKEN) {
        // Rien à faire, donc retourner
        return;
    }

    // Appeler la fonction d'étiquette de cas
    case_label();

    // Tant que nous trouvons une virgule, lire d'autres étiquettes de cas
    while (SYM.CODE == VIR_TOKEN) {
        // Consommer la virgule
        Sym_Suiv();

        // Appeler la fonction d'étiquette de cas
        case_label();
    }
}
//===================== case_label ==========================
void case_label() {
    // Appeler la fonction de constante
    constant();
}
//===================== set_type ==========================
void set_type() {
    // Vérifier si le prochain jeton est "set"
    if (SYM.CODE == SETOF_TOKEN) {
        // Consommer "set"
        Sym_Suiv();

        // Vérifier si le prochain jeton est "of"
        if (SYM.CODE == OF_TOKEN) {
            // Consommer "of"
            Sym_Suiv();

            // Appeler la fonction du type de base
            base_type();
        } else {
            // Si le prochain jeton n'est pas "of", signaler une erreur
            printf("Erreur : Mot-clé 'of' attendu\n");
            exit(1);
        }
    } else {
        // Si le prochain jeton n'est pas "set", signaler une erreur
        printf("Erreur : Mot-clé 'set' attendu\n");
        exit(1);
    }
}
//===================== base_type ==========================
void base_type() {
    // Appeler la fonction de type
    simple_type();
}
//===================== variable_declaration_part ==========================
void variable_declaration_part() {
    // Vérifier si la partie de déclaration de variable est vide
    if (SYM.CODE != VAR_TOKEN) {
        // Rien à faire, donc retourner
        return;
    }

    // Consommer "var"
    Sym_Suiv();

    // Tant que nous trouvons un identifiant (nom de variable), lire et traiter les déclarations de variables
    while (SYM.CODE == ID_TOKEN) {

            illegal_program_name(SYM.NOM);
            double_declaration(SYM.NOM, TVAR);

            // Appeler la fonction de déclaration de variable
            variable_declaration();

            // Vérifier si nous avons atteint la fin des déclarations de variables
            if (SYM.CODE != PV_TOKEN) {
                // Si le prochain symbole n'est pas un point-virgule, cela signifie qu'il n'y a plus de variables à déclarer
                // Donc nous pouvons sortir de la boucle
                break;
            }

            // Consommer le point-virgule
            Sym_Suiv();
    }
}
//===================== variable_declaration ==========================
// Fonction pour la déclaration de variable
void variable_declaration() {
    // Appeler la fonction de l'identifiant de variable
    //printf("je suis dans variable_declaration \n");
    variable_identifier();
            int adresse_constante = obtenir_adresse_constante();
             TABLESYM[IND_DER_SYM_ACC].ADRESSE = adresse_constante;
             GENERER2(LDA, adresse_constante);
    // Tant que nous trouvons une virgule, lire d'autres identifiants de variables
    while (SYM.CODE == VIR_TOKEN) {
        // Consommer la virgule
        Sym_Suiv();

        // l'identifiant de la variable est ajoute dans la table d'identifiants -----------------------
        //first, check if this identifier already exists
        illegal_program_name(SYM.NOM);
        double_declaration(SYM.NOM, TVAR);
        // --------------------------- fin partie semantique ------------------------------------

        // Appeler la fonction de l'identifiant de variable
        variable_identifier();
        int adresse_constante = obtenir_adresse_constante();
             TABLESYM[IND_DER_SYM_ACC].ADRESSE = adresse_constante;
             GENERER2(LDA, adresse_constante);
    }

    // Vérifier si le prochain jeton est ":"
    if (SYM.CODE == TP_TOKEN) {
        // Consommer ":"
        Sym_Suiv();

        // Appeler la fonction du type
        type();
    }
   /* else if (SYM.CODE == PV_TOKEN) {
        // Consommer ";"
       // Sym_Suiv();

        // Appeler la fonction du type
       // type();
    } else {
        // Si le prochain jeton n'est pas ";", signaler une erreur
        printf("Erreur : Symbole ';' ou ':' attendu\n");
        exit(1);
    }*/
}
//===================== file_type ==========================
// Fonction pour le type de fichier
void file_type() {
    // Vérifier si le prochain jeton est "file"
    if (SYM.CODE == FILEOF_TOKEN) {
        // Consommer "file"
        Sym_Suiv();

        // Vérifier si le prochain jeton est "of"
        if (SYM.CODE == OF_TOKEN) {
            // Consommer "of"
            Sym_Suiv();

            // Appeler la fonction du type
            type();
        } else {
            // Si le prochain jeton n'est pas "of", signaler une erreur
            printf("Erreur : Mot-clé 'of' attendu\n");
            exit(1);
        }
    } else {
        // Si le prochain jeton n'est pas "file", signaler une erreur
        printf("Erreur : Mot-clé 'file' attendu\n");
        exit(1);
    }
}
//===================== pointer_type ==========================
// Fonction pour le type pointeur
void pointer_type() {
    // Vérifier si le type est un identifiant
    if (SYM.CODE == ID_TOKEN) {
        // Consommer l'identifiant
        Sym_Suiv();
    } else {
        // Si le type n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant de type attendu\n");
        exit(1);
    }
}

//=====================Function_procedure ==========================
// Fonctions pour les fonctions et les procedures
void procedure_and_function_declaration_part() {
    while (SYM.CODE == PROCEDURE_TOKEN || SYM.CODE == FUNCTION_TOKEN) {
        procedure_or_function_declaration();
        Test_Symbole(PV_TOKEN, PV_ERR); // Point-virgule entre les déclarations
    }

}

void procedure_or_function_declaration() {
    if (SYM.CODE == PROCEDURE_TOKEN) {
        procedure_declaration();
    } else if (SYM.CODE == FUNCTION_TOKEN) {
        function_declaration();
        printf(SYM.NOM);
    }
}

void procedure_declaration() {
    procedure_heading();
    BLOCK();
}

void procedure_heading() {
    Test_Symbole(PROCEDURE_TOKEN, PROCEDURE_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    if (SYM.CODE == PV_TOKEN) {
        Sym_Suiv(); // Consommer le point-virgule
    } else if (SYM.CODE == PO_TOKEN) {
        Sym_Suiv(); // Consommer la parenthèse gauche

        formal_parameter_section();

        while (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le point-virgule
            formal_parameter_section();
        }
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
            Sym_Suiv(); // Consommer la parenthèse gauche

}
void procedure_or_function_calling() {
    //Test_Symbole(ID_TOKEN, ID_ERR);
    if (SYM.CODE == PO_TOKEN) {
        Sym_Suiv(); // Consommer la parenthèse gauche

        printf("on a consomme ( \n");
        //Test_Symbole(ID_TOKEN, ID_ERR);
        if (SYM.CODE == ID_TOKEN||SYM.CODE == FLOAT_TOKEN||SYM.CODE == NUM_TOKEN){ Sym_Suiv(); } // Consommer la parenthèse gauche
        else if(SYM.CODE == QUOTE_TOKEN){ string(); }
        while (SYM.CODE == VIR_TOKEN) {
            Sym_Suiv(); // Consommer la virgule
            Test_Symbole(ID_TOKEN, ID_ERR);
        }
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
}

void formal_parameter_section() {
    if (SYM.CODE == VAR_TOKEN) { Sym_Suiv(); } // Consommer VAR

    //Test_Symbole(ID_TOKEN, ID_ERR);
    if (SYM.CODE == ID_TOKEN){
        Sym_Suiv(); // Consommer VAR

        while (SYM.CODE == VIR_TOKEN) {
            Sym_Suiv(); // Consommer la virgule
            Test_Symbole(ID_TOKEN, ID_ERR);
        }
        Test_Symbole(TP_TOKEN, TP_ERR);

        //Test_Symbole(TYPE_TOKEN, TYPE_ERR);
        type();
    } else{ printf("\n pas de parametre  "); }
}

void function_declaration() {
    function_heading();
    BLOCK();
    printf("on a termine function_declaration \n");
}

void function_heading() {
    printf("in the function heading\n");
    Test_Symbole(FUNCTION_TOKEN, FUNCTION_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);

    if (SYM.CODE == PV_TOKEN) { Sym_Suiv(); } // Consommer le point-virgule
    else if (SYM.CODE == PO_TOKEN) {
        Sym_Suiv(); // Consommer la parenthèse gauche
        formal_parameter_section();
        while (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le point-virgule
            formal_parameter_section();
        }
        Test_Symbole(PF_TOKEN, PF_ERR);
    }
    Test_Symbole(TP_TOKEN, TP_ERR);
    // Test_Symbole(TYPE_TOKEN, TYPE_ERR);
   // printf("probleme ici ?");
    type();

    Test_Symbole(PV_TOKEN, PV_ERR); // Point-virgule
}

//===================== INSTS ==========================
void INSTS()
{
    // Vérifier si le prochain jeton est "begin"
    if (SYM.CODE == BEGIN_TOKEN)
    {
        // Consommer "begin"
        Sym_Suiv();

        // Appeler la fonction pour analyser la première instruction
        INST();

        // Tant que nous trouvons un point-virgule, lire d'autres instructions
        while (SYM.CODE == PV_TOKEN)
        {
            // Consommer le point-virgule
            Sym_Suiv();

            // Appeler la fonction pour analyser l'instruction suivante
            INST();
        }

        // Vérifier si le prochain jeton est "end"
        if (SYM.CODE == END_TOKEN) { Sym_Suiv(); } // Consommer "end"
        else { Erreur(END_ERR); } // Si le prochain jeton n'est pas "end", signaler une erreur
    }
    else { Erreur(BEGIN_ERR); } // Si le prochain jeton n'est pas "begin", signaler une erreur
}

//===================== INST ==========================
void INST(){
    int exists = 0;
    //INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM.CODE) {
        case BEGIN_TOKEN:

            INSTS();
            break;

        case ID_TOKEN: //usage d'un identifiant
            //check si il a ete declare
            exists = check_if_declared(SYM.NOM);
            if(exists == 1){
                Sym_Suiv();
                if (SYM.CODE == PT_TOKEN){
                    Sym_Suiv();
                    Test_Symbole(ID_TOKEN, ID_ERR);
                }
                if (SYM.CODE == CROCHETO_TOKEN){
                        Sym_Suiv();
                        Test_Symbole(ID_TOKEN, ID_ERR);
                        Test_Symbole(CROCHETF_TOKEN, CROCHETF_ERR);
                }
                if (SYM.CODE == AFF_TOKEN){
                        is_constant_affectee(SYM.NOM);
                        AFFEC();}
                else{ procedure_or_function_calling();}
                break;
            }else{
                printf("Erreur: cet identifiant n'a pas ete declare: %s, ligne %d", SYM.NOM, ligne_actuelle);
                exit(1);
            }

        case FUNCTION_TOKEN:
            procedure_and_function_declaration_part();
            break;

        case PROCEDURE_TOKEN:
            procedure_and_function_declaration_part();
            break;

        case IF_TOKEN:
            SI();
            break;

        case FOR_TOKEN:
            POUR();
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
       /*   printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
}


//===================== AFFEC ==========================
void AFFEC()
{
    //ID := EXPR
   // Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    EXPR();
    GENERER1(STO);
   /*   printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
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
    if (SYM.CODE == QUOTE_TOKEN){
        string();
    }
    else{
    EXPR();
    }
    while (SYM.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
if (SYM.CODE == QUOTE_TOKEN){
        string();
    }
    else{
    EXPR();    }
    }
    Test_Symbole(PF_TOKEN, PF_ERR);
}

//===================== LIRE ==========================
void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    if (SYM.CODE == QUOTE_TOKEN){ string(); }
    else if (SYM.CODE==ID_TOKEN) { Sym_Suiv(); }
    while (SYM.CODE == VIR_TOKEN) {
        Sym_Suiv();
        if (SYM.CODE == QUOTE_TOKEN){ string(); }
    }
    if (SYM.CODE == CROCHETO_TOKEN){
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
        Test_Symbole(CROCHETF_TOKEN, CROCHETF_ERR);
    } else if (SYM.CODE== PT_TOKEN){
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
    //Test_Symbole(ID_TOKEN, ID_ERR);
    switch (SYM.CODE)
    {
    case ELSE_TOKEN://à ajouter
        Test_Symbole(ELSE_TOKEN, ELSE_ERR);
        INST();
        printf("fin de inst\n");
        printf(SYM.NOM);
        printf("\n");


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
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    printf("\n pas de prob dans := \n");

    FACT();
    printf("\n pas de prob dans fact \n");

    Test_Symbole(TO_TOKEN, TO_ERR);
    printf("\n pas de prob dans to \n");

    FACT();
    printf("\n pas de prob dans fact2 \n");

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
    Test_Symbole(TP_TOKEN, TP_ERR);
    INST();

    while (SYM.CODE == NUM_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(TP_TOKEN, TP_ERR);
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
/*    case INTO_TOKEN://à ajouter
        Test_Symbole(INTO_TOKEN, INTO_ERR);
        break;*/
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
        GENERER1(ADD);
    }
     /* printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
}

//===================== TERM ==========================
void TERM()
{
    FACT();

    while (SYM.CODE == MULT_TOKEN || SYM.CODE == DIV_TOKEN)
    {
        MULOP();
        FACT();
        GENERER1(MUL);
    }
   /* printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
}

//===================== FACT ==========================
void FACT()
{
    switch (SYM.CODE)
    {
    case ID_TOKEN:
        Test_Symbole(ID_TOKEN, ID_ERR);
         int adresse_constante = obtenir_adresse_constante();
         TABLESYM[IND_DER_SYM_ACC].ADRESSE = adresse_constante;

        GENERER2(LDA, TABLESYM[IND_DER_SYM_ACC].ADRESSE);
        GENERER1(LDV);
        if (SYM.CODE == PO_TOKEN){ procedure_or_function_calling(); }
        else if (SYM.CODE == CROCHETO_TOKEN){
                Sym_Suiv();
                Test_Symbole(ID_TOKEN, ID_ERR);
                Test_Symbole(CROCHETF_TOKEN, CROCHETF_ERR);
            }else if (SYM.CODE== PT_TOKEN){
                Sym_Suiv();
                Test_Symbole(ID_TOKEN, ID_ERR);
            }
            break;
    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN, NUM_ERR);
                GENERER2(LDI, SYM.VAL);
        break;
        case FLOAT_TOKEN:
        Test_Symbole(FLOAT_TOKEN, FLOAT_ERR);
                GENERER2(LDI, SYM.VAL);
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
  /*  printf("=== Contenu de la pile après l'opération ===\n");
        afficher_contenu_pile();
        printf("===========================================\n");*/
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
/*    case INTO_TOKEN:
        Test_Symbole(SYM.CODE,INTO_ERR);
        break;*/
    case DOWNTO_TOKEN:
        Test_Symbole(SYM.CODE, DOWNTO_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

// ======================================= semantique ================================
// regle 3: ts les symboles identifiants etre declares avant BEGIN
int check_if_declared(char* idf_nom){
    for(int i=0; i < TIDFS_indice; i++){
        if (strcmp(TAB_IDFS[i].NOM, idf_nom) == 0) {
                return 1;
        }
    }
    return 0;
}
//regle 2: pas de double declaration
void double_declaration(char* idf_nom, TSYM idf_code){
    int exist = 0;
    for(int i=0; i < TIDFS_indice; i++){
        if (strcmp(TAB_IDFS[i].NOM, idf_nom) == 0) {
                exist = 1;
                break;
        }
    }
    if(exist == 0){
        strncpy(TAB_IDFS[TIDFS_indice].NOM, idf_nom, sizeof(TAB_IDFS[TIDFS_indice].NOM) - 1);
        TAB_IDFS[TIDFS_indice].NOM[sizeof(TAB_IDFS[TIDFS_indice].NOM) - 1] = '\0';
        TAB_IDFS[TIDFS_indice].TIDF = idf_code;
        TIDFS_indice++;
    } else {
        printf("Erreur: double declaration de %s, ligne %d\n", idf_nom, ligne_actuelle);
        exit(1);
    }
}

//regle 4: pas d'affectation pour les constantes

void is_constant_affectee(char* idf_nom){
    for(int i=0; i < TIDFS_indice; i++){
        if (strcmp(TAB_IDFS[i].NOM, idf_nom) == 0) {
                if(TAB_IDFS[i].TIDF == TCONST){
                    printf("Erreur: Pas d'affectation pour les constantes: %s, ligne %d\n", idf_nom, ligne_actuelle);
                    exit(1);
                }
        }
    }
}

//regle 5: pas de declaration avec le nom du programme
void illegal_program_name(char* idf_nom){
    if(TAB_IDFS[0].NOM != NULL && stricmp(idf_nom, TAB_IDFS[0].NOM) == 0){
        printf("Erreur: Declaration illegale: interdit de declarer une variable avec le nom du programme %s, ligne %d\n", idf_nom, ligne_actuelle);
        exit (1);
    }
}

//===================== main ==========================

/*
// Fonction pour vérifier si le type est un type pointeur
int is_pointer_type() {
    // Vérifier si le type est un identifiant
    return SYM.CODE == ID_TOKEN;
}

// Fonction pour vérifier si le type est un type structuré
int is_structured_type() {
    // Vérifier si le type est un type structuré
    return SYM.CODE == ARRAY_TOKEN || SYM.CODE == RECORD_TOKEN || SYM.CODE == SETOF_TOKEN || SYM.CODE == FILEOF_TOKEN;
}

// Fonction pour vérifier si le type est un type simple
int is_simple_type() {
    // Vérifier si le type est un type simple
    return SYM.CODE == SCALAR_TOKEN || SYM.CODE == SUBRANGE_TOKEN || SYM.CODE == ID_TOKEN;
}*/


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

    if (SYM.CODE == PT_TOKEN)
    {
        printf("BRAVO de main: le programme est correcte on arrive a la fin !!!\n");
        printf("Contenu de TAB_IDFS :\n");
        for (int i = 0; i < TIDFS_indice; i++) {
            printf("Indice %d : %s\n", i, TAB_IDFS[i].NOM);
        }
    }
    else
    {
        printf("PAS BRAVO de MAIN: fin de programme errone!!!!\n");
        printf("Current Token: %d\n", SYM.CODE);
        printf("Current Lexeme: %s\n", SYM.NOM);
        Sym_Suiv(); // Move this line inside the else block
    }

    fclose(fichier);

    return 0;
}
