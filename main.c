#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct user {
    char uname[20];
    char pass[20];
} player;

FILE *usuarios; // Declara apuntador tipo FILE
FILE *menu;

void leeArchivo();
int existeUsuario(char user[]);
void registrar();
void iniciarSesion();
void menuInicio();
void menuJuego();
void juego();

int main(void) {
    juego();
    return 0;
}

void leeArchivo(int parte, char arch[]) { // Lee e imprime partes de un archivo.
    char linea[100];
    int stop=0;
    int parteLeida=0;

    menu=fopen(arch, "r");

    if (!menu) {
        printf("No se encuentra el archivo del menú\n");
    }
    
    system("cls");
    while (!feof(menu) && !stop) {
        fgets(linea, 200, menu);
        if (linea[0]==';') {
            parteLeida++;
            if (parteLeida==parte-1)
                system("cls");
            if (parteLeida==parte)
                stop=1;
        } else
            printf("%s", linea);
    }

    fclose(menu);
}

int existeUsuario(char user[]) { // Verifica la existencia del usuario.
    char uArch[20];
    int existe=0;

    usuarios=fopen("users.txt", "r");
    
    if(!usuarios) {
        printf("No existe el archivo \"users.txt\"\n"); // Imprime mensaje en pantalla si el archivo no existe
    }
    
    while(!feof(usuarios)) { // Mientras no sea el final del archivo, comparará el usuario proporcionado con los usuarios del archivo
        fscanf(usuarios,"%s", uArch);
        if(!strcmp(user, uArch))
            existe++;
    }

    fclose(usuarios);
    return existe;
}

void registrar() { // Registra usuarios.
    struct user u;

    leeArchivo(1, "menu.txt");

    printf("\n\n\t\t\tCREAR USUARIO\n\n");

    do {
        fflush(stdin); // Limpia el buffer para volver a introducir los datos.
        if (existeUsuario(u.uname)) // Si ya exite el usuario, da el aviso.
            printf("\nEl usuario \"%s\" ya se encuentra registrado\n", u.uname);
        printf("Escribe un nombre de usuario: ");
        scanf("%20s", u.uname);
        printf("Escribe tu contrase%ca (max 20 caracteres): ", 164);
        scanf("%20s", u.pass);
    }
    while (existeUsuario(u.uname)); // Vuelve a pedir los datos si el usuario ya estaba registrado.

	usuarios=fopen("users.txt", "a");
	fprintf(usuarios,"%s\t%s\n", u.uname, u.pass); // Si la funcion exusuario es falsa, imprime el nombre de usuario y contraseña dentro del archivo
    //printf("El usuario \"%s\" se ha creado exitosamente con la contraseña \"%s\".\n", u.uname, u.pass);
    player=u; // Se asignan los datos del usuario al usuario global.
    menuJuego();
    fclose(usuarios);

}

void iniciarSesion() { // Permite iniciar sesion.
    struct user u, uArch;
    int correcto=0;

    leeArchivo(1, "menu.txt");

    printf("\n\n\t\t\tINICIO DE SESION\n\n");
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", &u.uname);
    printf("Introduce tu contrase%ca: ", 164);
    scanf("%s", &u.pass);

    if (existeUsuario(u.uname)) { // Si el usuario introducido exite.
        usuarios=fopen("users.txt", "r");

        while (!feof(usuarios) && !correcto) { // Mientras no se llegue al final del archivo y no coincidan los datos del usuario.
            fscanf(usuarios, "%s\t%s", uArch.uname, uArch.pass); // Lee usuario y contraseña.
            if (!strcmp(uArch.uname, u.uname) && !strcmp(uArch.pass, u.pass)) { // Revisa que coincidan el usuario y su contraseña.
                correcto=1;
                player=u; // Se asignan los datos del usuario al usuario global.
                menuJuego();
            }
        }
        
        if (!correcto) { // Si no coincidio la contraseña.
            printf("La contrase%ca no coincide.\n\nPresiona ENTER para volver al inicio.", 164);
            menuInicio();
        }
        
    } else { // En caso de que no exista el usuario.
        printf("El usuario \"%s\" no existe.\n\nPresiona ENTER para volver al inicio.", u.uname);
        menuInicio();
    }
    
    fclose(usuarios);
}

void menuInicio() {
    int op;

    do {
        leeArchivo(1, "menu.txt");
        printf("\n\n\t\t\t1. Inicio de sesion");
        printf("\n\t\t\t2. Crear usuario");
        printf("\n\t\t\t3. Salir");
        printf("\n\nSelecciona una opcion (1, 2 o 3): ");
        scanf("%i", &op);
        switch (op) {
            case 1:
                iniciarSesion();
                break;
            case 2:
                registrar();
                break;
            case 3:
                system("cls");
                break;
        }
    } while(op<1 || op>3); // Se asegura de que se elija una opcion válida.

}

void menuJuego() {
    int op=1;
    do {
        leeArchivo(2, "menu.txt");

        printf("\n\nBienvenido %s, elige una opcion", player.uname);
        if (op<1 || op>3) 
            printf(" VALIDA: ");
        else
            printf(": ");

        scanf("%i", &op);

        switch (op) {
            case 1:
                printf("Jugar");
                break;
            case 2:
                printf("Scores");
                break;
            case 3:
                printf("Salir");
                break;
        }
    } while (op<1 || op>3);
    
}

void juego() {
    // Las distintas opciones asociadas con un número.
    srand(time(NULL));
    int piedra = 1;
    int papel = 2;
    int tijera = 3;
    int lagarto = 4;
    int spock = 5;
    char opciones[5][8] = {"Piedra\0", "Papel\0", "Tijeras\0", "Lagarto\0", "Spock\0"};

    // Almacenan las opciones elegidas.
    int opUs=1; // usuario
    int opMa = rand()%5 + 1; // maquina (random del 1 al 5)

    leeArchivo(1, "menu.txt");
    printf("\n\n%cQue eliges?\n1. Piedra\n2. Papel\n3. Tijeras\n4. Lagarto\n5. Spock\n", 168);
    printf("Tu eleccion: ");

    do {
        if (opUs<1 || opUs>5)
            printf("Elige una opcion valida: ");
        scanf("%i", &opUs);
    } while (opUs<1 || opUs>5);

    printf("Elegiste %s\n",opciones[opUs-1]);
    printf("El programa eligio %s\n\n" , opciones[opMa-1]);
    

    switch (opUs) {
        case 1: // Piedra
            if (opMa == piedra)
                printf ("Empate!\nAmbos eligieron Piedra.");
            else if (opMa == papel)
                printf("Perdiste!\nPapel cubre Piedra.");
            else if (opMa == tijera)
                printf("Ganaste!\nPiedra aplasta Tijeras.");
            else if (opMa == lagarto)
                printf("Ganaste!\nPiedra aplasta Lagarto.");
            else if (opMa == spock) 
                printf("Perdiste!\nSpock vaporiza piedra.");
            break;

        case 2: // Papel
            if (opMa == piedra)
                printf("Ganaste!\nPapel cubre Piedra.");
            else if (opMa == papel)
                printf ("Empate!\nAmbos eligieron Papel.");
            else if (opMa == tijera)
                printf("Perdiste!\nTijeras cortan papel.");
            else if (opMa == lagarto)
                printf("Perdiste!\nLagarto come Papel.");
            else if (opMa == spock)
                printf("Ganaste!\nPapel desaprueba Spock.");
            break;

        case 3: // Tijera
            if(opMa == piedra)
                printf("Perdiste!\nPiedra aplasta tijeras.");
            else if(opMa == papel)
                    printf("Ganaste!\nTijeras cortan Papel.");
            else if(opMa == tijera)
                printf("Empate!\nAmbos eligieron Tijeras.");
            else if(opMa == lagarto)
                printf("Ganaste!\nTijeras decapitan Lagarto.");
            else if(opMa == spock)
                printf("Perdiste!\nSpock destruye Tijeras.");
            break;

        case 4: // Lagarto
            if(opMa == piedra)
                printf("Perdiste!\nPiedra aplasta Lagarto.");
            else if(opMa == papel)
                printf("Ganaste!\nLagarto come Papel.");
            else if(opMa == tijera)
                printf("Perdiste!\nTijeras decapitan Lagarto.");
            else if(opMa == lagarto)
                printf("Empate!\nAmbos eligieron Lagarto.");
            else if(opMa == spock)
                printf("Ganaste!\nLagarto envenena Spock.");
            break;

        case 5: // Spock
            if (opMa == piedra)
                printf("Ganaste!\nSpock vaporiza Piedra.");
            else if (opMa == papel)
                printf ("Perdiste!\nPapel desaprueba Spock.");
            else if (opMa == tijera)
                printf ("Ganaste!\nSpock destruye Tijeras.");
            else if (opMa == lagarto)
                printf ("Perdiste!\nLagarto envenena Spock.");
            else if (opMa == spock)
                printf("Empate!\nAmbos eligieron Spock");
            break;
    }    
}