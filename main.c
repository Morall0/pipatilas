#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auth.c>

FILE *usuarios; // Declara apuntador tipo FILE

int existeUsuario(char user[]);
int registrar();
int iniciarSesion();

int main(void) {
    iniciarSesion();
    // registrar();
    
	return 0;
}

int existeUsuario(char user[]) { // Revisa si existe dentro del archivo el usuario proporcionado.
    char usArch[10];
    int existe=0;

    usuarios=fopen("users.txt", "r");
    
    if(!usuarios) {
        printf("No existe el archivo \"users.txt\""); // Imprime mensaje en pantalla si el archivo no existe
        return 0;
    }
    
    while(!feof(usuarios)) { // Mientras no sea el final del archivo, comparará el usuario proporcionado con los usuarios del archivo
        fscanf(usuarios,"%s", usArch);
        if(!strcmp(user, usArch))
            existe++;
    }

    fclose(usuarios);
    return existe;
}

int registrar() { // Registrar un usuario.
    char user[10], pass[10];

    printf("CREAR USUARIO\n\n");

    do {
        if (existeUsuario(user)) // Ejecuta la funcion existeUsuario, mientras la funcion existe usuario sea verdadera
            printf("\nEl usuario \"%s\" ya se encuentra registrado\n", user);
        printf("Escribe tu nombre de usuario: ");
        scanf("%10s", user);
    }
    while (existeUsuario(user));

    if (existeUsuario(user)) // Si la funcion existeUsuario es verdadera solicita la contraseña
        printf("El usuario ya está registrado");
    printf("Escribe tu contraseña (max 10 caracteres): ");
    scanf("%10s", pass);

	usuarios=fopen("users.txt", "a");
	fprintf(usuarios,"%s\t%s\n", user, pass); // Si la funcion exusuario es falsa, imprime el nombre de usuario y contraseña dentro del archivo
    printf("El usuario \"%s\" ha creado exitosamente con la contraseña \"%s\".\n\n", user, pass);
    fclose(usuarios);

    iniciarSesion();

	return 1;
}

int iniciarSesion(){
    char pass[10], user[10], usArch[10], passArch[10];
    int correcto=0;

    printf("INICIO DE SESION\n\n");
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", &user);
    printf("Introduce tu contraseña: ");
    scanf("%s", &pass);

    if (existeUsuario(user)) { // Si el usuario introducido exite.
        usuarios=fopen("users.txt", "r");

        while (!feof(usuarios) && !correcto) { // Mientras no se llegue al final del archivo y no coincidan los datos del usuario.
            fscanf(usuarios, "%s\t%s", usArch, passArch); // Lee usuario y contraseña.
            if (!strcmp(usArch, user) && !strcmp(passArch, pass)) { // Revisa que coincidan el usuario y su contraseña.
                printf("Has iniciado sesion");
                correcto=1;
            }
        }
        
        if (!correcto) { // Si no coincidio la contraseña.
            printf("La contraseña no coincide.\nInténtalo de nuevo.\n\n");
            iniciarSesion();
        }
        
    } else { // En caso de que no exista el usuario.
        printf("El usuario \"%s\" no existe, registrate\n\n", user);
        registrar(); // Se da la opcion de iniciar sesion.
    }
    
    fclose(usuarios);
}