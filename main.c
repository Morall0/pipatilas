#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auth.c>

FILE *usuarios; // Declara apuntador tipo FILE

int existeUsuario(char user[]);
int registrar();
int iniciarSesion();

int main(void) {
    iniciarSesion;
    registrar();
    
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
    fclose(usuarios);

	return 1;
}

int iniciarSesion(){
    char pass[10], user[10], usArch[10], psArch[10];
    int existe=0;

    usuarios=fopen("users.txt", "r");

    while(!feof(usuarios)) { // Mientras no sea el final del archivo, comparará el usuario proporcionado con los usuarios del archivo
        fscanf(usuarios,"%s", usArch);
        if(!strcmp(user, usArch))
            existe++;
    }

    do{
        while(!feof(usuarios)) { // Mientras no sea el final del archivo, comparará la contraseña proporcionada con las contraeñas del archivo
            fscanf(usuarios,"%s", psArch);
            if(!strcmp(pass, psArch))
                printf("Bienvenido %c",user);
            else
                printf("Contraseña incorrecta");
        }
    }while(strcmp(pass, psArch));

}