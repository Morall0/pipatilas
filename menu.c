#include <stdio.h>
#include <stdlib.h>

FILE *menu;

void leeMenu(int op) {
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
            if (opVista==op-1)
                system("clear");
            if (opVista==op)
                stop=1;
        } else
            printf("%s", linea);
    }

    fclose(menu);
}

int main(void) {
    char c;
    int op=1;
    leeMenu(op); // Inicializa el menu en la posicion de "Jugar".
    
    while (1) { // Ciclo que detecta cuando se introduce 
        system("/bin/stty raw"); // Cambia funcionamiento de la consola (input sin enter).
        system("/bin/stty -echo");
        c=getchar(); // Lee el input teclado.
        system("/bin/stty echo");
        system("/bin/stty cooked"); // Devuelve la consola a su estado normal.
        switch (c) {
            case 'A': // Flecha de direccion ARRIBA.
                op=(op<=1)? 3:op-1;
                leeMenu(op);
                break;
            case 'B': // Flecha de direccion ABAJO.
                op=(op>=3)? 1:op+1;
                leeMenu(op);
                break;
        } 
    }
    return 0;
}
