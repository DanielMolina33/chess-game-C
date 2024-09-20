#include <stdio.h>
#include <stdlib.h>

// File headers
#include "utils.h"
#include "menu.h"

char *menu() {
    static char piece[LTR_SIZE];
    char ltr = pieceTypeMenu();
    char clr = pieceColorMenu();

    sprintf(piece, "%c%c", ltr, clr);

    return piece;
}

char buildMenu(char *msg, char *opts) {
    int isValid = 0;
    char ltr;

    printf("%s", msg);

    do {
        scanf(" %c", &ltr);
        ltr = toUpper(ltr);

        for (int i = 0; i < 6; i++) {
            if (ltr == 'S') exit(1);
            else if (ltr != opts[i]) continue;
            
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
    char *ltrMenuMsg =
        "Seleccione una ficha de ajedrez:\n\n"
        "( R. Rey \u265A ) ( Q. Reina \u265B ) ( T. Torre \u265C ) ( A. Alfil \u265D )"
        "( C. Caballo \u265E ) ( P. Peon \u265F )\n\n"
        "Ingrese la inicial de la ficha deseada o (S. Salir): ";

    return buildMenu(ltrMenuMsg, opts);
}

char pieceColorMenu() {
    char *opts = "NB";
    char *clrMenuMsg =
        "\n\nSeleccione el color de ficha:\n\n"
        "( N. Negro \u26AB ) ( B. Blanco \u26AA )\n\n"
        "Ingrese la inicial del color deseado o (S. Salir): ";

    return buildMenu(clrMenuMsg, opts);
}