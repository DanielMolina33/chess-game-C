#include <stdio.h>
#include <stdlib.h>

// File headers
#include "utils.h"
#include "menu.h"

// Main menu, collects and shows all the submenus
char *mainMenu() {
    static char piece[LTR_SIZE];

    // Checks for the exit option in the first submenu
    char ltr = pieceTypeMenu();
    if (ltr == 'S') return "S";

    // Checks for the exit option in the second submenu
    char clr = pieceColorMenu();
    if (ltr == 'S') return "S";

    // Creates the chosen option, given by the piece initial and the color, E.g. TB (Torre Blanca)
    sprintf(piece, "%c%c", ltr, clr);
    return piece;
}

// Piece type submenu, collects all the chess pieces to the player
char pieceTypeMenu() {
    char *opts = "RQTACP";
    char *ltrMenuMsg =
        "Seleccione una ficha de ajedrez:\n\n"
        "( R. Rey \u265A ) ( Q. Reina \u265B ) ( T. Torre \u265C ) ( A. Alfil \u265D )"
        "( C. Caballo \u265E ) ( P. Peon \u265F )\n\n"
        "Ingrese la inicial de la ficha deseada o (S. Salir): ";

    return buildMenu(ltrMenuMsg, opts);
}

// Piece color submenu, collects the white and black colors to the player
char pieceColorMenu() {
    char *opts = "NB";
    char *clrMenuMsg =
        "\n\nSeleccione el color de ficha:\n\n"
        "( N. Negro \u26AB ) ( B. Blanco \u26AA )\n\n"
        "Ingrese la inicial del color deseado o (S. Salir): ";

    return buildMenu(clrMenuMsg, opts);
}

// Build and show a menu, using a submenu data
char buildMenu(char *msg, char *opts) {
    int isValid = 0;
    char ltr;

    // Shows a message
    printf("%s", msg);

    // Scan the user input based on a given constraints (Needs a valid option)
    do {
        scanf(" %c", &ltr);
        ltr = toUpper(ltr);
        
        // Look for a valid option or the exit flag
        for (int i = 0; i < 6; i++) {
            if (ltr == 'S') return ltr;
            else if (ltr != opts[i]) continue;
            
            isValid = 1;
            break;
        }

        // When a valid option is not found, neither is the exit flag, notify the user of the valid options again.
        if (!isValid) {
            printf("\nOpcion invalida. Por favor, ingrese una inicial valida (%s) ", setStrDelimiter(opts));
            continue;
        }

        return ltr;

        // Continue until a valid option is chosen
    } while (1);
}