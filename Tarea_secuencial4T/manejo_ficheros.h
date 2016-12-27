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

void string_entero(int (*enteros)[100],char (*string)[100]){
	//Linea por linea , viendo los caracteres que tiene
	char *token;
	int j=0;
	for(int i=0;i<18;i++){

	   token = strtok(string[i]," ");
	   
	   while( j < 8 ){

	   		if(token==NULL){
	   			enteros[i][j]=0;
	   		}else{
	   			enteros[i][j]=atoi(token);	
	   		}
	   			
	      	token = strtok(NULL," ");
	      	//printf("%d %d %d\n",enteros[i][j],i,j);
	      	j++;
	    
	   }
	   j=0;
	}
}

