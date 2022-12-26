#include <stdio.h>
#include <stdlib.h>
//#include <auth.c>


FILE *usuarios;
int registrar() { // Registrar un usuario.

    char user[10], pass[10];

	printf("Escribe tu nombre de usuario: ");
    fgets(usuarios, 20, stdin);

    printf("Escribe tu contraseña: ");
    scanf("%s", pass);

	bd=fopen("users.txt", "a");
	fprintf(bd,"%s\t%s", user,pass);
    fclose(bd);

	return 1;
}

int main(void) {
	registrar();
	return 0;
}
