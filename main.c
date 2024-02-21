#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ================================== CODES : tokens ==================================
/* enumeration CODES, with a set of named constants each assigned an integer value.
The constants represent different types of tokens that might be encountered in a Pascal program during lexical analysis
(the process of converting a sequence of characters into a sequence of tokens)
*/
typedef enum {
    ID_TOKEN, // identifiant: variables
    PROGRAM_TOKEN, // PROGRAM
    CONST_TOKEN, VAR_TOKEN, // CONST & VAR
    BEGIN_TOKEN, END_TOKEN, // BEGIN & END
    IF_TOKEN, THEN_TOKEN, // IF & THEN
    WHILE_TOKEN, DO_TOKEN, // WHILE & DO
    READ_TOKEN, WRITE_TOKEN, // READ() & WRITE()
    PV_TOKEN, PT_TOKEN, // Point-virgule(;) & Point(.)
    PLUS_TOKEN, MOINS_TOKEN, // Plus(+) & Minus(-)
    MULT_TOKEN, DIV_TOKEN, // Multiply(*) & Divide(/)
    VIR_TOKEN, AFF_TOKEN, // Virgule(,) & Affectation(:=)
    INF_TOKEN, INFEG_TOKEN, // Inferieur(<) & Inferieur ou egal(<=)
    SUP_TOKEN, SUPEG_TOKEN, // Superieur(>) & Superieur ou egal(>=)
    DIFF_TOKEN, PO_TOKEN, // Not equal(<>) & Parenthese Ouvrante '('
    PF_TOKEN, FIN_TOKEN, // Parenthese Fermante ')'
    STRING_TOKEN,FLOAT_TOKEN,CHAR_TOKEN,BOOL_TOKEN,QUOTE_TOKEN,TP_TOKEN,COMMENTO_TOKEN,CBO_TOKEN,CBF_TOKEN,AND_TOKEN,OR_TOKEN,COMMENTF_TOKEN,
    TYPE_TOKEN,NOT_TOKEN,CROCHETO_TOKEN,CROCHETF_TOKEN,
    GOTO_TOKEN,ELSE_TOKEN,REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,TO_TOKEN,DOWNTO_TOKEN,WITH_TOKEN,
    LABEL_TOKEN,ARRAY_TOKEN,OF_TOKEN,RECORD_TOKEN,CASE_TOKEN,SETOF_TOKEN,FILEOF_TOKEN,PROCEDURE_TOKEN,FUNCTION_TOKEN,IN_TOKEN,DIVV_TOKEN,MOD_TOKEN,//div =/ et DIVV = div de BNF
    NUM_TOKEN, ERREUR_TOKEN, EOF_TOKEN,EG_TOKEN,DOTDOT_TOKEN,E_TOKEN,SET_TOKEN,FILE_TOKEN,INTEGER_TOKEN,
} CODES;

// ================================== CODES_ERR : Errors associated to tokens ==================================
// erreur types
typedef enum
{
    PROGRAM_ERR, ID_ERR, CONST_ERR, VAR_ERR, BEGIN_ERR,
    END_ERR, IF_ERR, THEN_ERR, WHILE_ERR, DO_ERR, READ_ERR, WRITE_ERR, PV_ERR, PT_ERR, PLUS_ERR, MOINS_ERR, MULT_ERR,
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

// ================================== Current_sym : current symbol ==================================
// structure of the token: token = (code, nom). ex: token de var = (VAR_TOKEN, "var")
typedef struct{
    CODES CODE;
    char NOM[20];
} Current_sym;

Current_sym SYM; // SYM : current symbol

// ================================== functions declaration ==================================
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
void label_declaration_part();
void const_definition_part();
void type_definition_part();
void variable_declaration_part();
//void procedure_and_function_declaration_part();
void statement_part();
void empty();
void label();
void constant_definition_part();
void constant_definition();
void unsigned_real();
void string();
void constant();
void unsigned_number();
void unsigned_integer();
void unsigned_real();
void scale_factor();
void sign();
void constant_identifier();
void string();
void type_definition_part();
void type_definition();
void type();
void simple_type();
void scalar_type();
void subrange_type();
void type_identifier();
void structured_type();
void array_type();
void index_type();
void component_type();
void record_type();
void field_list();
void fixed_part();
void record_section();
void variant_type();
void tag_field();
void variant();
void case_label_list();
void case_label();
void set_type();
void unsigned_constant();
void function_designator();
void function_identifier();
void set();
void element_list();
void element();
void procedure_statement();
void procedure_identifier();
void actual_parameter();
void goto_statement();
void empty_statement();
void empty();
void structured_statement();
void compound_statement();
void conditional_statement();
void if_statement();
void case_statement();
void case_list_element();
void case_label_list();
void repetitive_statement();
void while_statement();


// functions definition
// ================================== Lire_Car() : read the next character ==================================
int ligne_actuelle = 1;
FILE *fichier;
char Car_Cour; // caractere courant

void Lire_Car()
{
    Car_Cour = fgetc(fichier);
    if (Car_Cour == '\n') { ligne_actuelle++; } // Incrémentation du numéro de ligne en cas de saut de ligne
}

// ================================== lire_mot() ==================================
/* It reads a word from input and checks if it matches any of the predefined keywords in Pascal. Let's break down what it does:
*/
void lire_mot()
{
    char mot[20]; // Initialize empty word of max size = 20
    int indice = 0; // Initialize index (that we will use to go through 'mot') to 0

    // Lecture du premier caractere (la 1ere lettre)
    mot[indice++] = Car_Cour; // mot(0) = Car_Cour then indice +=1
    Lire_Car(); // Read the next character

    // Do the same for index >= 1, while the current character is a letter (isalpha()) or a number (isdigit())
    while (isalpha(Car_Cour) || isdigit(Car_Cour)) {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractere de fin de chaine. mot = [..., ..., ..., '\0']
    mot[indice] = '\0';

    // Verifier si le mot est un mot-cle
    if (stricmp(mot, "program") == 0) { SYM.CODE = PROGRAM_TOKEN; } // if mot == 'program' ==> current symbol is program and its token is PROGRAM_TOKEN
    else if (stricmp(mot, "set") == 0) { SYM.CODE = SET_TOKEN; }
    else if (stricmp(mot, "const") == 0) { SYM.CODE = CONST_TOKEN; }
    else if (stricmp(mot, "var") == 0) { SYM.CODE = VAR_TOKEN; }
    else if (stricmp(mot, "begin") == 0) { SYM.CODE = BEGIN_TOKEN; }
    else if (stricmp(mot, "end") == 0) { SYM.CODE = END_TOKEN; }
    else if (stricmp(mot, "if") == 0) { SYM.CODE = IF_TOKEN; }
    else if (stricmp(mot, "file") == 0) { SYM.CODE = FILE_TOKEN; }
    else if (stricmp(mot, "then") == 0) { SYM.CODE = THEN_TOKEN; }
    else if (stricmp(mot, "while") == 0) { SYM.CODE = WHILE_TOKEN; }
    else if (stricmp(mot, "E") == 0) { SYM.CODE = E_TOKEN; }
    else if (stricmp(mot, "do") == 0) { SYM.CODE = DO_TOKEN; }
    else if (stricmp(mot, "read") == 0) { SYM.CODE = READ_TOKEN; }
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
    else { SYM.CODE = ID_TOKEN; } // if none of the special keywords, then it's an identifier

    strcpy(SYM.NOM, mot); // then the current symbol's NOM is mot itself
}

// ================================== Lire_nombre() ==================================
// ex: on lit le nombre 13 ==> SYM = (NUM_TOKEN, '13')
void lire_nombre()
{
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour)) {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractere de fin de chaine
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    SYM.CODE = NUM_TOKEN;
    strcpy(SYM.NOM, nombre);
}

// ==================================================================== SYNTAXIQUE ====================================================================

// ================================== Sym_Suiv() ==================================
// Manage the next symbol to a specific symbol. ex: var x = 5; '=' is the next symbol to 'x'
void Sym_Suiv()
{
    //ignore spaces ' ', end of lines '\n' and tabulations '\t'
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t') { Lire_Car(); }

    //once we hit a letter or number, read the word
    if (isalpha(Car_Cour)) { lire_mot(); }
    else if (isdigit(Car_Cour)) { lire_nombre(); }
    else {
        switch (Car_Cour) {

            case ';':
                SYM.CODE = PV_TOKEN;
                Lire_Car();
                break;

            case '..':
                SYM.CODE = DOTDOT_TOKEN; // '..' : range (ex: array[1..10]
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
                if (Car_Cour == ')' || Car_Cour == '}') { // if we have *) or *}  ==> comment
                    SYM.CODE = COMMENTF_TOKEN;
                    Lire_Car();
                }else { SYM.CODE = MULT_TOKEN; } // if just * ==> multiplication
                break;

            case '/':
                Lire_Car();
                if (Car_Cour == '/') { // if we have // ==> comment
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = DIV_TOKEN; } // if just / ==> divide
                break;

            case '\'':
                SYM.CODE = QUOTE_TOKEN; // if we have quote character: '
                Lire_Car();
                break;

            case ',':
                SYM.CODE = VIR_TOKEN;
                Lire_Car();
                break;

            case '{':
                Lire_Car();
                if (Car_Cour == '*') { // if we have {*  ==> comment
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = CBO_TOKEN; } // if just ( ==> Curly Brace Fermante
                break;

             case '}':
                SYM.CODE = CBF_TOKEN;
                Lire_Car();
                break;

            case ':':
                Lire_Car();
                if (Car_Cour == '=') { // if we have := then affectation symbol
                    SYM.CODE = AFF_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = TP_TOKEN; } // if just : then Type declaration
                break;

            case '<':
                Lire_Car();
                if (Car_Cour == '=') { // if we have <=
                    SYM.CODE = INFEG_TOKEN;
                    Lire_Car();
                } else if (Car_Cour == '>') { // if we have <> (equiv to !=)
                    SYM.CODE = DIFF_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = INF_TOKEN; } // if just <
                break;

            case '>':
                Lire_Car();
                if (Car_Cour == '=') { // if we have >=
                    SYM.CODE = SUPEG_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = SUP_TOKEN; } // if just >
                break;

            case '(':
                Lire_Car();
                if (Car_Cour == '*') { // if we have (*
                    SYM.CODE = COMMENTO_TOKEN;
                    Lire_Car();
                } else { SYM.CODE = PO_TOKEN; } // if just (
                break;

            case ')':
                SYM.CODE = PF_TOKEN;
                Lire_Car();
                break;

            case '=':
                SYM.CODE = EG_TOKEN;
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

            case EOF: //End Of File
                SYM.CODE = FIN_TOKEN;
                break;

            default:
                SYM.CODE = ERREUR_TOKEN;
                Lire_Car();
        }
    }

}

// ================================== Erreur(CODES_ERR) ==================================
// Print an error message, with the line and the error code, as well as the current symbol's CODE and NOM
void Erreur(CODES_ERR code)
{
    printf("Erreur à la ligne %d: %d\n", ligne_actuelle, code);
    printf("Current Token: %d\n", SYM.CODE);
    printf("Current Lexeme: %s\n", SYM.NOM);
    exit(EXIT_FAILURE);
}

// ================================== Test_Symbole(CODES, CODES_ERR) ==================================
// if the current symbol's code matches the code, move to the next symbol, else error function
void Test_Symbole(CODES cl, CODES_ERR COD_ERR)
{
    if (SYM.CODE == cl) { Sym_Suiv(); }
    else {Erreur(COD_ERR); }
}
// ================================== BLOCK ==================================
void BLOCK()
{
    label_declaration_part(); //in the block, we usually start with label declarations (go to)
    constant_definition_part(); // constant declarations
    type_definition_part(); // type declarations
    variable_declaration_part(); //variable declaration
    // procedure_and_function_declaration_part();
    // statement_part();
}

// ================================== label declaration part ==================================
void label_declaration_part() {
    if (SYM.CODE == LABEL_TOKEN) {
        Sym_Suiv(); // Consommer le token "label"
        label();    // Appeler la fonction pour analyser un label

        // Ensuite, analysez les virgules suivies de labels
        while (SYM.CODE == VIR_TOKEN) {
            Sym_Suiv(); // Consommer le token ","
            if (SYM.CODE == NUM_TOKEN) { label(); } // Analyser le prochain label
            else { // Gérer une erreur si le token suivant n'est pas un nombre
                printf("Erreur: Nombre attendu après ',' dans la déclaration de label\n");
                Erreur(NUM_ERR);
            }
        }

        if (SYM.CODE == PV_TOKEN) { Sym_Suiv(); } // Consommer le token ";"
        else {
            // Gérer une erreur si pas de ";"
            printf("Erreur : ';' attendu après la déclaration de label\n");
            Erreur(PV_ERR);
        }
    } else {
        // Si le token n'est pas "label", il s'agit d'une production vide
        // Aucune action requise
    }
}

// ================================== label() ==================================
void label() {
    if (SYM.CODE == NUM_TOKEN) {
        // Traitement du label
        // Ici, vous pouvez stocker ou utiliser la valeur du label
        Sym_Suiv(); // Consommer le token NUM
    } else {
        // Gérer une erreur si le token n'est pas un entier non signé
        printf("Erreur : Entier non signé attendu dans la déclaration de label\n");
        Erreur(NUM_ERR);
    }
}

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

        if (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le dernier point-virgule
        } else {
            // Gérer une erreur si le dernier token n'est pas ";"
            printf("Erreur : ';' attendu après la définition des constantes\n");
                    Erreur(PV_ERR);

        }
    } else {
                    Sym_Suiv(); // Consommer le dernier point-virgule

    }
}
//===================== constant_definition ==========================

// Fonction pour analyser une définition de constante
void constant_definition() {
    if (SYM.CODE == ID_TOKEN) {
        Sym_Suiv(); // Consommer le token identifiant

        if (SYM.CODE == EG_TOKEN) {
            Sym_Suiv(); // Consommer le token "="
            // Vérifier si la constante est une valeur directe
            if (SYM.CODE == NUM_TOKEN || SYM.CODE == STRING_TOKEN || SYM.CODE == CHAR_TOKEN) {
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
        // Gérer une erreur si le token n'est pas un identifiant
        printf("Erreur : Identifiant attendu dans la définition de constante\n");
        Erreur(TP_ERR);
    }
}

//===================== constant ==========================

// Fonction pour analyser une constante
void constant() {
    if (SYM.CODE == NUM_TOKEN || SYM.CODE == ID_TOKEN || SYM.CODE == STRING_TOKEN) {
        Sym_Suiv(); // Consommer la constante valide (numérique, identifiant ou chaîne de caractères)
    } else if (SYM.CODE == PLUS_TOKEN || SYM.CODE == MOINS_TOKEN) {
        Sym_Suiv(); // Consommer le token de signe
        if (SYM.CODE == ID_TOKEN) {
            Sym_Suiv(); // Consommer le token identifiant
        } else {
            // Gérer une erreur si le token suivant n'est pas un identifiant
            printf("Erreur : Identifiant attendu après le signe dans la constante\n");
        Erreur(TP_ERR);
        }
    } else {
        // Gérer une erreur si le token n'est pas une constante valide
        printf("Erreur : Constante invalide dans la définition de constante\n");
        Erreur(CONST_ERR);
    }
}

// ================================== PROGRAM ==================================
void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR); // Basically, necessarily the 1st symbol of the program should be the "program" symbol
    Test_Symbole(ID_TOKEN, ID_ERR); // necessarily the 2nd symbol should be the name of the program which will be an identifier
    Test_Symbole(PV_TOKEN, PV_ERR); // then the 3rd symbole is ';'
    BLOCK(); // and now it's a block of code

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

//===================== type_definition_part ==========================
// Implémentation de la production <type definition part>
void type_definition_part() {
    if (SYM.CODE == TYPE_TOKEN) {
        // Si le token actuel est "type", consommons-le
        Sym_Suiv();

        // Analysons la définition du type
        type_definition();

        // Tant qu'on trouve des points-virgules, continuons d'analyser les définitions de type
        while (SYM.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consommer le point-virgule
            type_definition(); // Analyser la définition de type suivante
        }

        // Vérifier le point-virgule final
        if (SYM.CODE != PV_TOKEN) {
            printf("Erreur : Point-virgule attendu après la définition de type\n");
        Erreur(PV_ERR);
        }

       Sym_Suiv(); // Consommer le point-virgule final
    }
    else {

    }
}


//===================== type_definition ==========================
// Implémentation de la production <type definition>
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
    if (SYM.CODE == INTEGER_TOKEN || SYM.CODE == FLOAT_TOKEN || SYM.CODE == CHAR_TOKEN || SYM.CODE == STRING_TOKEN || SYM.CODE == BOOL_TOKEN) {
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
        if (SYM.CODE == PT_TOKEN) {
            Sym_Suiv(); // Consommer le PT_TOKEN
        } else {
            // Si le jeton suivant n'est pas un point-virgule, signaler une erreur
            printf("Erreur : Symbole ';' attendu après l'identifiant\n");
            Erreur(PT_ERR);
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
    if (SYM.CODE == PO_TOKEN) {
        scalar_type();
    } else if (SYM.CODE == NUM_TOKEN) {
        subrange_type();
    } else if (SYM.CODE == ID_TOKEN) {
        type_identifier();
    }
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
        // Ici, vous pouvez copier l'identifiant dans une variable ou effectuer d'autres traitements
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
    if (SYM.CODE == ID_TOKEN) {
        // Consommer l'identifiant en passant au jeton suivant
        Sym_Suiv();
    } else {
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
    if (SYM.CODE == ID_TOKEN) {
        // Consommer l'identifiant
        Sym_Suiv();
    } else {
        // Si le prochain jeton n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant de type attendu\n");
        Erreur(ID_ERR);
    }
}
//===================== structured_type ==========================
void structured_type() {
    // Vérifier si le type est un type tableau, un type enregistrement, un ensemble ou un fichier
    if (SYM.CODE == ARRAY_TOKEN) {
        array_type();
    } else if (SYM.CODE == RECORD_TOKEN) {
        record_type();
    } else if (SYM.CODE == SETOF_TOKEN) {
        set_type();
    } else if (SYM.CODE == FILEOF_TOKEN) {
        file_type();
    } else {
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

            // Tant que nous trouvons une virgule, lire d'autres types d'index
            while (SYM.CODE == VIR_TOKEN) {
                // Consommer ","
                Sym_Suiv();

                // Appeler la fonction de type d'index
                index_type();
            }

            // Vérifier si le prochain jeton est "]"
            if (SYM.CODE == CROCHETF_TOKEN) {
                // Consommer "]"
                Sym_Suiv();
            } else {
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
        if (SYM.CODE == END_TOKEN) {
            // Consommer "end"
            Sym_Suiv();
        } else {
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
            if (SYM.CODE == CASE_TOKEN) {
                // Appeler la fonction de partie variante
                variant_part();
            } else {
                // Si ce n'est pas la partie variante, c'est une autre partie fixe
                field_list();
            }
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

    // Appeler la fonction de déclaration de variable
    variable_declaration();

    // Tant que nous trouvons un point-virgule, lire d'autres déclarations de variables
    while (SYM.CODE == PV_TOKEN) {
        // Consommer le point-virgule
        Sym_Suiv();

        // Appeler la fonction de déclaration de variable
        variable_declaration();
    }
}
//===================== variable_declaration ==========================
// Fonction pour la déclaration de variable
void variable_declaration() {
    // Appeler la fonction de l'identifiant de variable
    variable_identifier();

    // Tant que nous trouvons une virgule, lire d'autres identifiants de variables
    while (SYM.CODE == VIR_TOKEN) {
        // Consommer la virgule
        Sym_Suiv();

        // Appeler la fonction de l'identifiant de variable
        variable_identifier();
    }

    // Vérifier si le prochain jeton est ":"
    if (SYM.CODE == TP_TOKEN) {
        // Consommer ":"
        Sym_Suiv();

        // Appeler la fonction du type
        type();
    } else {
        // Si le prochain jeton n'est pas ":", signaler une erreur
        printf("Erreur : Symbole ':' attendu\n");
        exit(1);
    }
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

//=================unsigned constant=========================
// Implémentation de la production <unsigned constant>
void unsigned_constant() {
    if (SYM.CODE == NUM_TOKEN) {
        // Si le token est un nombre, c'est une constante nonsignée
        unsigned_number();
    } else if(SYM.CODE == STRING_TOKEN){
        string();
    }
    else if (SYM.CODE == CONST_TOKEN){
        constant_identifier();
    }
    else {
        // Gérer une erreur si le token n'est pas un signe ou un nombre
        printf("Erreur : Ce n'est pas une constante non signée\n");
        exit(1);
    }
    Sym_Suiv();
}

//=================function designator=========================
// Implémentation de la production <function designator>
void function_designator() {
    if (SYM.CODE == ID_TOKEN) {
        function_identifier();
        Sym_Suiv();
        if(SYM.CODE == PO_TOKEN){
            Sym_Suiv();
            actual_parameter();
            Sym_Suiv();
            while(SYM.CODE == VIR_TOKEN){
                Sym_Suiv();//consommer la virgule
                actual_parameter();
            }
        if(SYM.CODE == PF_TOKEN){
            Sym_Suiv();
        }else{
             printf("Erreur : Symbole ')' attendu\n");
            Erreur(PF_ERR);
        }
    }else{ printf("Erreur : Mot-clé '(' attendu\n");
                Erreur(PO_ERR);
 }
    if(SYM.CODE == PV_TOKEN){
        break;
    }
    }
    else {
        printf("Erreur liée à function designator\n");
        exit(1);
    }
}

//===================== function_identifier ==========================
void function_identifier() {
    // Vérifier si le prochain jeton est un identifiant
    if (SYM.CODE == ID_TOKEN) {
        // Consommer l'identifiant
        Sym_Suiv();
    } else {
        // Si le prochain jeton n'est pas un identifiant, signaler une erreur
        printf("Erreur : Identifiant de fonction attendu\n");
        Erreur(ID_ERR);
    }
}
//===================== set ==========================
// Implémentation de la production <set>
void set() {
    if (SYM.CODE == CROCHETO_TOKEN) {
        Sym_Suiv();
        while (SYM.CODE != CROCHETF_TOKEN) {
            element_list();
        }
    }
    else {
        printf("Erreur liée à l'implémentation de set")
    }
}

//===================== element_list ==========================
// Implémentation de la production <element_list>
void element_list() {
            element();
            Sym_Suiv();
        // Tant qu'on trouve des virgules, continuons d'analyser les elements
            while (SYM.CODE == VIR_TOKEN) {
                Sym_Suiv(); // Consommer la virgule
                element(); // Analyser l'element
        }
        // Vérifier le point-virgule final
        if (SYM.CODE != PV_TOKEN) {
            printf("Erreur : Point-virgule attendu après la définition de liste des elements\n");
            exit(1);
        }
       Sym_Suiv(); // Consommer le point-virgule final
    }
    else {
        printf("erreur liée à liste des élements")
    }
}


//===================== element ==========================
// Implémentation de la production <element>
void element() {
        expression();
        Sym_Suiv();
        if(SYM.CODE == DOTDOT_TOKEN){
            Sym_Suiv();
            expression();
        }else if(SYM.CODE == PV_TOKEN){
            break;
        }
        else {
        printf("erreur liée à l'element")
       }
}

//=================procedure identifier=========================
// Implémentation de la production <procedure identifier>
void procedure_identifier() {
    if (SYM.CODE == ID_TOKEN ) {
        // Si le token est un ID, c'est un identifiant d'une constante
        Sym_Suiv();
    } else {
        // Gérer une erreur si le token n'est pas un signe ou un nombre
        printf("Erreur : Ce n'est pas un identifiant d'une fonction\n");
        exit(1);
    }
}

//=============procedure statement===============================
// Implémentation de la production <procedure statement>
void procedure_statement() {
    if (SYM.CODE == ID_TOKEN) {
        procedure_identifier();
        Sym_Suiv();
        if(SYM.CODE == PO_TOKEN){
            Sym_Suiv();
            actual_parameter();
            Sym_Suiv
            while(SYM.CODE == VIR_TOKEN){
                Sym_Suiv();//consommer la virgule
                actual_parameter();
            }
            if(SYM.CODE == PF_TOKEN){
            Sym_Suiv();
            }else {
             printf("Erreur : Symbole ')' attendu\n");
            Erreur(CROCHETO_ERR);
            }
          } 
            else if(SYM.CODE == PV_TOKEN){
                break;
            }
    }else {
        printf("Erreur liée à procedure statement\n");
        exit(1);
    }
}

//=============actual parameter===========
// Implémentation de la production <actual parameter>
void actual_parameter() {
    if (SYM.CODE == §§§§§§) {
         expression();}
    else if(SYM.CODE == VAR_TOKEN){
         Sym_Suiv();
         variable();}
    else if(SYM.CODE == ID_TOKEN){
         procedure_identifier();
         }
    else {

        printf("Erreur liée à procedure statement\n");
        exit(1);
    }
}

//=================goto statement=========================
// Implémentation de la production <goto statement>
void goto_statement() {
    if (SYM.CODE == GOTO_TOKEN) {
        // Si le token est un goto, on va le consommer
        Sym_Suiv();
        label();
    } else {
        printf("Erreur liée à goto statement\n");
        exit(1);
    }
}

//===================== compound_statement ==========================
// Implémentation de la production <compound_statement>
void compound_statement() {
          if(SYM.CODE == BEGIN_TOKEN){
              Sym_Suiv();
              statement();
              Sym_Suiv();
            while (SYM.CODE == PV_TOKEN) {
                Sym_Suiv(); // Consommer le point-virgule
                statement();
            }
            if(SYM.CODE == END_TOKEN){
                Sym_Suiv();
                } else {
                // Si le prochain jeton n'est pas "end", signaler une erreur
                printf("Erreur : Symbole 'end' attendu\n");
                Erreur(END_ERR);
            }
             // Vérifier si le prochain jeton est ";"
            if (SYM.CODE == PV_TOKEN) {
                // Consommer ";"
                Sym_Suiv();
                break;
            } else {
                // Si le prochain jeton n'est pas ";", signaler une erreur
                printf("Erreur : Mot-clé ';' attendu\n");
                Erreur(PV_ERR);
            }         
        }else {
        // Si le prochain jeton n'est pas "begin", signaler une erreur
        printf("Erreur : Mot-clé 'begin' attendu\n");
        Erreur(BEGIN_ERR);
    }
}

//=================conditionnal statement=========================
// Implémentation de la production <conditionnal statement>
void conditionnal_statement() {
    if (SYM.CODE == IF_TOKEN) {
        // Si le token est un goto, on va le consommer
        Sym_Suiv();
        if_statement();
    }else if(SYM.CODE == CASE_TOKEN){
        Sym_Suiv();
        case_statement();
    }
    else {
        printf("Erreur liée à goto statement\n");
        exit(1);
    }
}

//===================== case_label_list ==========================
// Implémentation de la production <case_label_list>
void case_label_list() {
            case_label();
            Sym_Suiv();
        // Tant qu'on trouve des virgules, continuons d'analyser les elements
            while (SYM.CODE == VIR_TOKEN) {
                Sym_Suiv(); // Consommer la virgule
                case_label();
                Sym_Suiv(); //
        }
        // Vérifier le point-virgule final
        if (SYM.CODE != PV_TOKEN) {
            printf("Erreur : Point-virgule attendu après la définition de liste des elements\n");
            exit(1);
        }
       Sym_Suiv(); // Consommer le point-virgule final
    }
    else {
        printf("erreur liée à liste des cas")
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

