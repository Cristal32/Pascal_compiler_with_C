/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définition des types de tokens
typedef enum {
    PROGRAM_TOKEN,
    ID_TOKEN,
    PV_TOKEN, // Point-virgule
    CONST_TOKEN,
    EG_TOKEN, // Égal
    NUM_TOKEN,
    VAR_TOKEN,
    VIT_TOKEN,
    BEGIN_TOKEN,
    AFF_TOKEN, // Affectation
    READ_TOKEN,
    PO_TOKEN, // Parenthèse ouvrante
    PF_TOKEN, // Parenthèse fermante
    END_TOKEN,
    PT_TOKEN, // Point
    EOF_TOKEN
} TokenType;

// Structure pour un token
typedef struct {
    TokenType type;
    char* value; // La valeur associée au token, s'il y en a une
} Token;

// Fonction pour obtenir le prochain token à partir du code source
Token getNextToken(char* source, int* currentPosition) {
    Token token;
    token.value = NULL;

    char currentChar = source[*currentPosition];
    while (isspace(currentChar)) {
        (*currentPosition)++;
        currentChar = source[*currentPosition];
    }

    if (currentChar == '\0') {
        token.type = EOF_TOKEN;
    } else if (currentChar == ';') {
        token.type = PV_TOKEN;
        (*currentPosition)++;
    } else if (currentChar == '.') {
        token.type = PT_TOKEN;
        (*currentPosition)++;
    } else if (isdigit(currentChar)) {
        int numLength = 0;
        char numValue[20]; // Taille arbitraire pour stocker le nombre

        while (isdigit(currentChar)) {
            numValue[numLength++] = currentChar;
            (*currentPosition)++;
            currentChar = source[*currentPosition];
        }

        numValue[numLength] = '\0';

        token.type = NUM_TOKEN;
        token.value = malloc((numLength + 1) * sizeof(char));
        strcpy(token.value, numValue);
    } else if (strncmp(&source[*currentPosition], "PROGRAM", 7) == 0) {
        token.type = PROGRAM_TOKEN;
        (*currentPosition) += 7; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "CONST", 5) == 0) {
        token.type = CONST_TOKEN;
        (*currentPosition) += 5; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "VAR", 3) == 0) {
        token.type = VAR_TOKEN;
        (*currentPosition) += 3; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "VIT", 3) == 0) {
        token.type = VIT_TOKEN;
        (*currentPosition) += 3; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "BEGIN", 5) == 0) {
        token.type = BEGIN_TOKEN;
        (*currentPosition) += 5; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "AFF", 3) == 0) {
        token.type = AFF_TOKEN;
        (*currentPosition) += 3; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "READ", 4) == 0) {
        token.type = READ_TOKEN;
        (*currentPosition) += 4; // Avance la position du curseur au-delà du mot-clé
    } else if (strncmp(&source[*currentPosition], "END", 3) == 0) {
        token.type = END_TOKEN;
        (*currentPosition) += 3; // Avance la position du curseur au-delà du mot-clé
    } else if (currentChar == '(') {
        token.type = PO_TOKEN;
        (*currentPosition)++;
    } else if (currentChar == ')') {
        token.type = PF_TOKEN;
        (*currentPosition)++;
    } else {
        // Si ce n'est aucun des mots-clés, c'est un identifiant (ID)
        int identifierLength = 0;
        while (isalnum(source[*currentPosition + identifierLength])) {
            identifierLength++;
        }

        if (identifierLength > 0) {
            token.type = ID_TOKEN;
            token.value = malloc((identifierLength + 1) * sizeof(char));
            strncpy(token.value, &source[*currentPosition], identifierLength);
            token.value[identifierLength] = '\0';
            (*currentPosition) += identifierLength;
        }
    }

    return token;
}



int main() {
    char sourceCode[] = "PROGRAM ID ; CONST ID = NUM ; VAR ID VIT ID ; BEGIN ID AFF ID ; READ ( ID ) ; END .";

    int currentPosition = 0;
    Token token;
    do {
        token = getNextToken(sourceCode, &currentPosition);
        // Imprimer le type et la valeur du token (si disponible)
        printf("Token Type: %d\n", token.type);
        if (token.value != NULL) {
            printf("Token Value: %s\n", token.value);
        }
    } while (token.type != EOF_TOKEN);

    return 0;
}
*/
