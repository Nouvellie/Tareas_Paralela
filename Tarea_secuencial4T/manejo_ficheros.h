#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length(x) (sizeof(x)-sizeof(x[0]))

int filas_fichero(char fichero[]){
	FILE *archivo;

	char caracteres[50];
	int contador=-1;
	archivo = fopen(fichero,"r");
 	
 	if (archivo == NULL)
 		exit(1);
 	
 	while (feof(archivo) == 0){
 		fgets(caracteres,50,archivo);
 		contador=contador+1;
 	}
 	 fclose(archivo);
 	 return contador;
}

int equals(char s0[], char s1[]){
	
	for(int i=0;i<length(s1)-1;i++){
		printf("%c %c\n",s0[i],s1[i]);
		if(s0[i]!=s1[i]){
			return 0;
		}
	}
	return 1;
}