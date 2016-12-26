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

		if(s0[i]!=s1[i]){
			return 0;
		}
	}
	return 1;
}

void asignar_string(char s0[], char s1[]){
	for(int i=0;i<50;i++){
		s0[i]=s1[i];
	}
}

void split_convert(char s[],int vector[]){
	for(int i=0;i<50;i++){
		if(s[i]!=' '){
			vector[i]=s[i];
		}else{
			vector[i]=0;
		}
	}

}

void string_entero(char (*string)[100], int (*enteros)[100]){
	//Linea por linea , viendo los caracteres que tiene
	char caracteres_sin_espacio[6];
	int contador=0;
	int matriz_enteros=0;
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if(string[i][j]==' '){
				enteros[i][matriz_enteros]=atoi(caracteres_sin_espacio);
				matriz_enteros++;
			}
			caracteres_sin_espacio[contador]=string[i][j];
			contador++;
		}
		contador=0;
	}
}

