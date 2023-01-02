#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char uname[20];
    char pass[20];
} usu;

FILE *usuarios; // Declara apuntador tipo FILE
FILE *menu;

void leeArchivo();
int existeUsuario(char user[]);
int registrar();
int iniciarSesion();
int inicio();

int main(void) {
    inicio();
	return 0;
}


void leeArchivo(int parte) { // Lee e imprime partes de un archivo.
    char linea[100];
    int stop=0;
    int parteLeida=0;

    menu=fopen("menu.txt", "r");

    if (!menu) {
        printf("No se encuentra el archivo del menú\n");
        return;
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
        return 0;
    }
    
    while(!feof(usuarios)) { // Mientras no sea el final del archivo, comparará el usuario proporcionado con los usuarios del archivo
        fscanf(usuarios,"%s", uArch);
        if(!strcmp(user, uArch))
            existe++;
    }

    fclose(usuarios);
    return existe;
}

int registrar() { // Registra usuarios.
    struct user u;

    leeArchivo(1);

    printf("\n\n\t\t\tCREAR USUARIO\n\n");

    do {
        fflush(stdin); // Limpia el buffer para volver a introducir los datos.
        if (existeUsuario(u.uname)) // Si ya exite el usuario, da el aviso.
            printf("\nEl usuario \"%s\" ya se encuentra registrado\n", u.uname);
        printf("Escribe un nombre de usuario: ");
        scanf("%20s", u.uname);
        printf("Escribe tu contraseña (max 20 caracteres): ");
        scanf("%20s", u.pass);
    }
    while (existeUsuario(u.uname)); // Vuelve a pedir los datos si el usuario ya estaba registrado.

	usuarios=fopen("users.txt", "a");
	fprintf(usuarios,"%s\t%s\n", u.uname, u.pass); // Si la funcion exusuario es falsa, imprime el nombre de usuario y contraseña dentro del archivo
    printf("El usuario \"%s\" se ha creado exitosamente con la contraseña \"%s\".\n", u.uname, u.pass);
    usu=u; // Se asignan los datos del usuario al usuario global.
    fclose(usuarios);

	return 1;
}

int iniciarSesion() { // Permite iniciar sesion.
    struct user u, uArch;
    int correcto=0;

    leeArchivo(1);

    printf("\n\n\t\t\tINICIO DE SESION\n\n");
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", &u.uname);
    printf("Introduce tu contraseña: ");
    scanf("%s", &u.pass);

    if (existeUsuario(u.uname)) { // Si el usuario introducido exite.
        usuarios=fopen("users.txt", "r");

        while (!feof(usuarios) && !correcto) { // Mientras no se llegue al final del archivo y no coincidan los datos del usuario.
            fscanf(usuarios, "%s\t%s", uArch.uname, uArch.pass); // Lee usuario y contraseña.
            if (!strcmp(uArch.uname, u.uname) && !strcmp(uArch.pass, u.pass)) { // Revisa que coincidan el usuario y su contraseña.
                printf("Has iniciado sesion");
                correcto=1;
                usu=u; // Se asignan los datos del usuario al usuario global.
            }
        }
        
        if (!correcto) { // Si no coincidio la contraseña.
            printf("La contraseña no coincide.\n\nPresiona ENTER para volver al inicio.");
            fflush(stdin); // Limpia el buffer para que no haya error con getchar.
            getchar();
            inicio();
        }
        
    } else { // En caso de que no exista el usuario.
        printf("El usuario \"%s\" no existe.\n\nPresiona ENTER para volver al inicio.", u.uname);
        fflush(stdin); // Limpia el buffer para que no haya error con getchar.
        getchar();
        inicio();
    }
    
    fclose(usuarios);
}

int inicio() {
    int op;

    do {
        leeArchivo(1);
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

    return 0;
}