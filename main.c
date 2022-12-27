#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auth.c>

FILE *usuarios;

int existeUsuario(char user[]) { // Checa si existe un usuario.
    char usArch[10];
    int existe=0;

    usuarios=fopen("users.txt", "r");
    
    if(!usuarios) {
        printf("No existe el archivo \"users.txt\"");
        return 0;
    }
    
    while(!feof(usuarios)) {
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
        if (existeUsuario(user))
            printf("\nEl usuario \"%s\" ya se encuentra registrado\n", user);
        printf("Escribe tu nombre de usuario: ");
        scanf("%10s", user);
    }
    while (existeUsuario(user));

    if (existeUsuario(user))
        printf("El usuario ya está registrado");
    printf("Escribe tu contraseña (max 10 caracteres): ");
    scanf("%10s", pass);

	usuarios=fopen("users.txt", "a");
	fprintf(usuarios,"%s\t%s\n", user, pass);
    fclose(usuarios);

	return 1;
}

int main(void) {
    registrar();
	return 0;
}
