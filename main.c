/*
    Tablero de ajedrez 8x8, con puntero dinamico, el cual se pueda actualizar
   constantemente y actualice la vista del tablero.
   ╔═══╗
   ║ Q ║
   ╚═══╝
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#define SIZE 9
#define PIECE_SIZE 4

// Prototypes
char buildMenu(char *msg, char *opts);
char *menu();
char pieceTypeMenu();
char pieceColorMenu();
void showBoard(char board[SIZE][SIZE][SIZE]);
void setBoardPosition(char xLtr, int y, char *pieceName, char board[SIZE][SIZE][SIZE]);
char toUpper(char);
void printLine(int count, char *str);
void drawTop();
void drawColNumbers();
void drawRowNumbers(int row, int col, char board[SIZE][SIZE][SIZE]);
void drawIntermediate();
void drawBottom();
char *setStrDelimiter(const char *str);
char *letterToPiece(char ltr, char clr);
char numberToLetter(int n);
int letterToNumber(char ltr);

void initializeConsole() {
#ifdef _WIN32
    // Set UTF-8 encoding for console output
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int main() {
    initializeConsole();

    char x;
    int y;
    char *piece;
    // Board initialization
    char board[SIZE][SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            strcpy(board[i][j], " ");
        }
    }

    showBoard(board);

    do {
        piece = menu();

        printf("Digite la posicion en x: ");
        scanf(" %c", &x);

        printf("Digite la posicion en y: ");
        scanf(" %d", &y);

        setBoardPosition(x, y, piece, board);

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                strcpy(board[i][j], " ");
            }
        }
    } while (1);

    return 0;
}

char *menu() {
    char ltr = pieceTypeMenu();
    char clr = pieceColorMenu();
    return letterToPiece(ltr, clr);
}

char buildMenu(char *msg, char *opts) {
    int isValid = 0;
    char ltr;

    printf("%s", msg);

    do {
        // while((getchar() != '\n'));
        scanf(" %c", &ltr);
        ltr = toUpper(ltr);

        for (int i = 0; i < 6; i++) {
            if (ltr == 'S') {
                exit(1);
            } else if (ltr != opts[i]) {
                continue;
            }

            isValid = 1;
            break;
        }

        if (!isValid) {
            printf("\nOpcion invalida. Por favor, ingrese una inicial valida (%s) ", setStrDelimiter(opts));
            continue;
        }

        return ltr;

    } while (1);
}

char pieceTypeMenu() {
    char *opts = "RQTACP";
    char *ltrMenuMsg = (
        "Seleccione una ficha de ajedrez:\n\n"
        "( R. Rey \u265A ) ( Q. Reina \u265B ) ( T. Torre \u265C "
        ") ( A. Alfil \u265D )"
        "( C. Caballo \u265E ) ( P. Peon \u265F )\n\n"
        "Ingrese la inicial de la ficha deseada o (S. Salir): "
	);

    return buildMenu(ltrMenuMsg, opts);
}

char pieceColorMenu() {
    char *opts = "NB";
    char *clrMenuMsg = (
        "\n\nSeleccione el color de ficha:\n\n"
        "( N. Negro \u26AB ) ( B. Blanco \u26AA )\n\n"
        "Ingrese la inicial del color deseado o (S. Salir): "
	);

    return buildMenu(clrMenuMsg, opts);
}

/* void showBoard(char board[SIZE][SIZE][SIZE]){
    int row = 0, col = 0;

    for(row = 0; row < SIZE; row++) {
        if(row > 0) printf("%d ", row);
        for(col = 1; col < SIZE; col++) {
            if(row > 0) printf("%s ", board[row][col]);
            else printf("    %d", col);
        }
        printf("\n");
    }
} */

void showBoard(char board[SIZE][SIZE][SIZE]) {
    int row = 0, col = 0;

    for (row = 0; row < SIZE; row++) {
        if (row == 0) {
            drawColNumbers();
            continue;
        } else if (row == 1) {
            drawTop();
        } else {
            drawIntermediate();
        }

        drawRowNumbers(row, col, board);

        if (row == SIZE - 1) {
            drawBottom();
        }
    }

    printf("\n");
}

void setBoardPosition(char xltr, int y, char *piece, char board[SIZE][SIZE][SIZE]) {
    char opt[PIECE_SIZE];
    char figure[SIZE];
    int x = letterToNumber(xltr);

    sprintf(figure, "%s", piece);
    if (x != 0 || y != 0) strcpy(board[x][y], figure);
    showBoard(board);
}

void drawTop() {
    printf("   ╔════");
    printLine(SIZE - 1, "╦════");
    printf("╗\n");
}

void drawColNumbers() {
    for (int y = 1; y < SIZE; y++) {
        printf(y == 1 ? "      %d" : "    %d", y);
    }
    printf("\n");
}

void drawIntermediate() {
    printf("   ╠════╬");
    printLine(SIZE - 2, "════╬");
    printf("════╣\n");
}

void drawRowNumbers(int row, int col, char board[SIZE][SIZE][SIZE]) {
    char rowLtr = numberToLetter(row);
    printf("%c  ║ %s", rowLtr, board[row][1]);

    for (col = 2; col < SIZE; col++) {
        printf("  ║ %s", board[row][col]);
    }

    printf("  ║\n");
}

void drawBottom() {
    printf("   ╚═");
    printLine(SIZE - 1, "═══╩═");
    printf("═══╝");
}

char numberToLetter(int n) {
    switch (n) {
        case 1:
            return 'A';
        case 2:
            return 'B';
        case 3:
            return 'C';
        case 4:
            return 'D';
        case 5:
            return 'E';
        case 6:
            return 'F';
        case 7:
            return 'G';
        case 8:
            return 'H';
        default:
            return ' ';
    }
}

int letterToNumber(char ltr) {
    switch (ltr) {
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        case 'D':
            return 4;
        case 'E':
            return 5;
        case 'F':
            return 6;
        case 'G':
            return 7;
        case 'H':
            return 8;
        default:
            return 0;
    }
}

// Converts a single ascii character into upper case
char toUpper(char ltrIn) {
    int DIFF = 32;
    return (ltrIn >= 97 && ltrIn <= 122) ? ltrIn - DIFF : ltrIn;
}

char *setStrDelimiter(const char *str) {
    static char strOut[256];  // Static buffer for the result
    size_t len = strlen(str);

    strOut[0] = '\0';  // Initialize the buffer

    for (size_t i = 0; i < len; i++) {
        char buffer[5];                                    // Temporary buffer for one character and a comma
        snprintf(buffer, sizeof(buffer), "%c, ", str[i]);  // Append a comma
        strcat(strOut, buffer);                            // Append to the result buffer
    }

    // Remove the last comma if necessary
    if (len > 0) {
        strOut[strlen(strOut) - 2] = '\0';  // Replace the last comma with null terminator
    }

    return strOut;
}

void printLine(int count, char *str) {
    for (int i = 1; i < count; i++) {
        printf("%s", str);
    }
}

char *letterToPiece(char ltr, char clr) {
    static char piece[PIECE_SIZE];

    switch (ltr) {
        case 'R': {
            strcpy(piece, clr == 'N' ? "\u265A" : "\u2654");
            break;
        }
        case 'Q': {
            strcpy(piece, clr == 'N' ? "\u265B" : "\u2655");
            break;
        }
        case 'T': {
            strcpy(piece, clr == 'N' ? "\u265C" : "\u2656");
            break;
        }
        case 'A': {
            strcpy(piece, clr == 'N' ? "\u265D" : "\u2657");
            break;
        }
        case 'C': {
            strcpy(piece, clr == 'N' ? "\u265E" : "\u2658");
            break;
        }
        case 'P': {
            strcpy(piece, clr == 'N' ? "\u265F" : "\u2659");
            break;
        }
    }

    return piece;
}