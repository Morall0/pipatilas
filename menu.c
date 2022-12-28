#include <stdio.h>
#include <stdlib.h>

FILE *menu;

void leeMenu(int opSel) {
    char linea[100];
    int stop=0;
    int opVista=0;

    menu=fopen("menu.txt", "r");

    if (!menu) {
        printf("No se encuentra el archivo del menú");
        return;
    }
    
    system("clear");
    while (!feof(menu) && !stop) {
        fgets(linea, 100, menu);
        if (linea[0]==';') {
            opVista++;
            if (opVista==opSel-1)
                system("clear");
            if (opVista==opSel)
                stop=1;
        } else
            printf("%s", linea);
    }

    fclose(menu);
}

int main(void) {
    leeMenu(3);
    return 0;
}
