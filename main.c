#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct user {
    char uname[20];
    char pass[20];
    int pjugadas;
    int pganadas;
    int pperdidas;
} player;

FILE *usuarios; // Declara apuntador tipo FILE

void leeArchivo();
int existeUsuario(char user[]);
void registrar();
void iniciarSesion();
void menuInicio();
void menuJuego();
void actPuntos();
void juego();

int main(void) {
    system("cls");
    menuInicio();
    return 0;
}

void leeArchivo(int parte, char arch[]) { // Lee e imprime partes de un archivo.
    FILE *archivo;
    char linea[100];
    int stop=0;
    int parteLeida=0;

    archivo=fopen(arch, "r");

    if (!archivo) {
        printf("No se encuentra el archivo %s\n", arch);
    }
    
    while (!feof(archivo) && !stop) {
        fgets(linea, 200, archivo);

        if (parteLeida == parte-1 && linea[0]!=';')
            printf("%s", linea);

        if (linea[0]==';') {
            parteLeida++;
            if (parteLeida==parte) 
                stop=1;
        }
    }

    fclose(archivo);
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

    // Inicializando en 0 el registro de partidas.
    u.pjugadas=0; 
    u.pganadas=0;
    u.pperdidas=0;

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

    // Se registra el usuario al archivo.
	usuarios=fopen("users.txt", "a");
	fprintf(usuarios,"%s\t%s\t%i\t%i\t%i\n", u.uname, u.pass, u.pjugadas, u.pganadas, u.pperdidas); // Si la funcion exusuario es falsa, imprime el nombre de usuario y contraseña dentro del archivo.
    fclose(usuarios);
    
    player=u; // Se asignan los datos del usuario al usuario global.

    system("cls");
    menuJuego();
}

void iniciarSesion() { // Permite iniciar sesion.
    struct user uArch;
    char uname[20];
    char pass[20];
    int correcto=0;

    leeArchivo(1, "menu.txt");

    printf("\n\n\t\t\tINICIO DE SESION\n\n");
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", uname);
    printf("Introduce tu contrase%ca: ", 164);
    scanf("%s", pass);

    if (existeUsuario(uname)) { // Si el usuario introducido exite.
        usuarios=fopen("users.txt", "r");

        while (!feof(usuarios) && !correcto) { // Mientras no se llegue al final del archivo y no coincidan los datos del usuario.
            fscanf(usuarios, "%s\t%s\t%i\t%i\t%i\n", uArch.uname, uArch.pass, &uArch.pjugadas, &uArch.pganadas, &uArch.pperdidas); // Lee usuario y contraseña.
            if (!strcmp(uArch.uname, uname) && !strcmp(uArch.pass, pass)) { // Revisa que coincidan el usuario y su contraseña.
                correcto=1;
                player=uArch; // Se asignan los datos del usuario al usuario global.
                fclose(usuarios);
                system("cls");
                menuJuego();
            }
        }
        
        if (!correcto) { // Si no coincidio la contraseña.
            printf("La contrase%ca no coincide.\n\nPresiona ENTER para volver al inicio.", 164);
            fflush(stdin); // Limpia el buffer para que no falle getchar.
            getchar();
            fclose(usuarios);
            system("cls");
            menuInicio();
        }
        
    } else { // En caso de que no exista el usuario.
        printf("El usuario \"%s\" no existe.\n\nPresiona ENTER para volver al inicio.", uname);
        fflush(stdin); // Limpia el buffer para que no falle getchar.
        getchar();
        fclose(usuarios);
        system("cls");
        menuInicio();
    }
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
        system("cls");
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

        system("cls");

        switch (op) {
            case 1:
                juego();
                break;
            case 2:
                printf("Scores");
                break;
            case 3:
                system("cls");
                break;
        }
    } while (op<1 || op>3);
    
}

// TODO: Crear funcion que despliegue el score.

void actPuntos() {
    FILE *tmp; // Archivo temporal en el que se reescriben los usuarios.
    struct user usArch;

    usuarios=fopen("users.txt", "r");
    tmp=fopen("users.tmp", "w");

    // Va leyendo del archivo de usuarios y lo imprime en el temporal.
    while (!feof(usuarios)) {
        fscanf(usuarios, "%s\t%s\t%i\t%i\t%i\n", usArch.uname, usArch.pass, &usArch.pjugadas, &usArch.pganadas, &usArch.pperdidas);

        if (strcmp(usArch.uname, player.uname)) {
            if (usArch.uname) 
                fprintf(tmp, "%s\t%s\t%i\t%i\t%i\n", usArch.uname, usArch.pass, usArch.pjugadas, usArch.pganadas, usArch.pperdidas);
        } else if (!strcmp(usArch.uname, player.uname)) // Cuando llega al usuario, imprime la info actualizada.
            fprintf(tmp, "%s\t%s\t%i\t%i\t%i\n", player.uname, player.pass, player.pjugadas, player.pganadas, player.pperdidas);
    }

    fclose(usuarios);
    fclose(tmp);

    
    remove("users.txt"); // Se elimina el archivo con la informacion vieja.
    rename("users.tmp", "users.txt"); // Se cambia el nombre del archivo temporal al nombre del archivo original.

}

void juego() {
    srand(time(NULL));
    
    int victoria[2]={0,0}; // [0]: victorias de usuario | [1]: victorias de maquina.
    int conti=1; // Perimte volver a jugar (se inicializa en 1 para que no salte la validacion).

    // Las distintas opciones asociadas con un número.
    int piedra = 1;
    int papel = 2;
    int tijera = 3;
    int lagarto = 4;
    int spock = 5;

    // Almacenan las opciones elegidas.
    int opUs=1; // usuario (se inicializa en 1 para que no salte la validacion).
    int opMa; // maquina (random del 1 al 5).

    do { // Bucle que permite volver a jugar una partida desde 0.
        // Reiniciando el contador de victorias
        victoria[0]=0;
        victoria[1]=0;

        do { // Bucle que repite la partida hasta que alguno gane 3 veces.
            system("cls");
            leeArchivo(1, "menu.txt");
            printf("\n\t\t\tPuntuacion\n");
            printf("\t\t\t   %i | %i\n", victoria[0], victoria[1]);
            printf("\n\t\t\t%cQue eliges %s?", 168, player.uname);
            printf("\n\t\t\t1. Piedra");
            printf("\n\t\t\t2. Papel");
            printf("\n\t\t\t3. Tijeras");
            printf("\n\t\t\t4. Lagarto");
            printf("\n\t\t\t5. Spock");

            printf("\nTu eleccion: ");

            // Valida la opcion elegida.
            do {
                if (opUs<1 || opUs>5)
                    printf("Elige una opcion valida: ");
                scanf("%i", &opUs);
            } while (opUs<1 || opUs>5);

            opMa = rand()%5 + 1; // maquina (random del 1 al 5)

            printf("\nElegiste:\n");
            leeArchivo(opUs, "manos.txt");
            printf("\nEl programa eligio:\n");
            leeArchivo(opMa, "manos.txt");
            
            switch (opUs) { //Switch con todos los casos posibles.
                case 1: // Piedra
                    if (opMa == piedra) {
                        printf ("\t\t\tEmpate!\n\t\tAmbos eligieron Piedra.");
                    } else if (opMa == papel) {
                        printf("\t\t\tPerdiste!\n\t\tPapel cubre Piedra.");
                        victoria[1]++;
                    } else if (opMa == tijera) {
                        printf("\t\t\tGanaste!\n\t\tPiedra aplasta Tijeras.");
                        victoria[0]++;
                    } else if (opMa == lagarto) {
                        printf("\t\t\tGanaste!\n\t\tPiedra aplasta Lagarto.");
                        victoria[0]++;
                    } else if (opMa == spock) {
                        printf("\t\t\tPerdiste!\n\t\tSpock vaporiza piedra.");
                        victoria[1]++;
                    }
                    break;

                case 2: // Papel
                    if (opMa == piedra) {
                        printf("\t\t\tGanaste!\n\t\tPapel cubre Piedra.");
                        victoria[0]++;
                    } else if (opMa == papel) {
                        printf ("\t\t\tEmpate!\n\t\tAmbos eligieron Papel.");
                    } else if (opMa == tijera) {
                        printf("\t\t\tPerdiste!\n\t\tTijeras cortan papel.");
                        victoria[1]++;
                    } else if (opMa == lagarto) {
                        printf("\t\t\tPerdiste!\n\t\tLagarto come Papel.");
                        victoria[1]++;
                    } else if (opMa == spock) {
                        printf("\t\t\tGanaste!\n\t\tPapel desaprueba Spock.");
                        victoria[0]++;
                    }
                    break;

                case 3: // Tijera
                    if(opMa == piedra) {
                        printf("\t\t\tPerdiste!\n\t\tPiedra aplasta tijeras.");
                        victoria[1]++;
                    } else if(opMa == papel) {
                        printf("\t\t\tGanaste!\n\t\tTijeras cortan Papel.");
                        victoria[0]++;
                    } else if(opMa == tijera) {
                        printf("\t\t\tEmpate!\n\t\tAmbos eligieron Tijeras.");
                    } else if(opMa == lagarto) {
                        printf("\t\t\tGanaste!\n\t\tTijeras decapitan Lagarto.");
                        victoria[0]++;
                    } else if(opMa == spock) {
                        printf("\t\t\tPerdiste!\n\t\tSpock destruye Tijeras.");
                        victoria[1]++;
                    }
                    break;

                case 4: // Lagarto
                    if(opMa == piedra) {
                        printf("\t\t\tPerdiste!\n\t\tPiedra aplasta Lagarto.");
                        victoria[1]++;
                    } else if(opMa == papel) {
                        printf("\t\t\tGanaste!\n\t\tLagarto come Papel.");
                        victoria[0]++;
                    } else if(opMa == tijera) {
                        printf("\t\t\tPerdiste!\n\t\tTijeras decapitan Lagarto.");
                        victoria[1]++;
                    } else if(opMa == lagarto) {
                        printf("\t\t\tEmpate!\n\t\tAmbos eligieron Lagarto.");
                    } else if(opMa == spock) {
                        printf("\t\t\tGanaste!\n\t\tLagarto envenena Spock.");
                        victoria[0]++;
                    }
                    break;

                case 5: // Spock
                    if (opMa == piedra) {
                        printf("\t\t\tGanaste!\n\t\tSpock vaporiza Piedra.");
                        victoria[0]++;
                    } else if (opMa == papel) {
                        printf ("\t\t\tPerdiste!\n\t\tPapel desaprueba Spock.");
                        victoria[1]++;
                    } else if (opMa == tijera) {
                        printf ("\t\t\tGanaste!\n\t\tSpock destruye Tijeras.");
                        victoria[0]++;
                    } else if (opMa == lagarto) {
                        printf ("\t\t\tPerdiste!\n\t\tLagarto envenena Spock.");
                        victoria[1]++;
                    } else if (opMa == spock) {
                        printf("\t\t\tEmpate!\n\t\tAmbos eligieron Spock");
                    }
                    break;
            }

            printf("\nPresiona ENTER para continar");
            fflush(stdin);
            getchar();

        } while(victoria[0]<3 && victoria[1]<3);
        
        if(victoria[0]==3) {
            player.pjugadas++;
            player.pganadas++;
            actPuntos();
            system("cls");
            leeArchivo(6, "manos.txt");
        } else{
            player.pjugadas++;
            player.pperdidas++;
            actPuntos();
            system("cls");
            leeArchivo(7, "manos.txt");
        }
        
        printf("\n\t\t1. Jugar de nuevo\t2. Salir\n\n");
        printf("\t\t: ");

        do { // Validacion de opcion.
            if (conti!=1 && conti!=2)
                printf("\n\t\tIntroduce una opcion valida: ");
            scanf("%i", &conti);
        } while (conti!=1 && conti!=2);

    } while(conti==1);

    if (conti==2) {
        system("cls");
        menuJuego();
    }
}