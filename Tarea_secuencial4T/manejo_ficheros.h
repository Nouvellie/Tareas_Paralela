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

void lectura_node(int x1[],float x2[], float x3[]){
	FILE *fichero;
   char nombre[10] = "node";
   unsigned int i, size;

   fichero = fopen( nombre, "r" );
   printf( "Fichero: %s (para lectura) -> ", nombre );
   if( fichero )
      printf( "existe (ABIERTO)\n" );
   else
   {
      printf( "Error (NO ABIERTO)\n" );
      return 1;
   }

   fscanf( fichero, "%d",&size );
   printf( "%d\n", size);
   float x4;
   for( i=0; i< size; i++ )
   {
      fscanf( fichero, "%d\t%f\t%f\t%f\n", &x1[i], &x2[i], &x3[i], &x4 );
      printf( "%d\t%f\t%f\t%f\n", x1[i], x2[i], x3[i], x4 );
   }

   if( !fclose(fichero) )
      printf( "Fichero cerrado\n" );
   else
   {
      printf( "Error: fichero NO CERRADO\n" );
      return 1;
   }

}

void lectura_ele(int x1[],int x2[], int x3[], int x4[]){
	FILE *fichero;
   char nombre[10] = "ele";
   unsigned int i, size;

   fichero = fopen( nombre, "r" );
   printf( "Fichero: %s (para lectura) -> ", nombre );
   if( fichero )
      printf( "existe (ABIERTO)\n" );
   else
   {
      printf( "Error (NO ABIERTO)\n" );
      return 1;
   }

   fscanf( fichero, "%d",&size );
   printf( "%d\n", size);
   for( i=0; i< size; i++ )
   {
      fscanf( fichero, "%d\t%d\t%d\t%d\n", &x1[i], &x2[i], &x3[i], &x4[i] );
      printf( "%d\t%d\t%d\t%d\n", x1[i], x2[i], x3[i], x4[i] );
   }

   if( !fclose(fichero) )
      printf( "Fichero cerrado\n" );
   else
   {
      printf( "Error: fichero NO CERRADO\n" );
      return 1;
   }

}

void sobreescribir_node(){

}

void sobreescribir_ele(t malla[], int aumenta, int numero_triangulo){
	FILE *fp;
	int size_ele=tamano_ele();

   	fp = fopen ( "ele", "w" );
  	 fprintf(fp, "%d\n",size_ele+aumenta);
	for(int i=0;i < size_ele+aumenta;i++){
		if(malla[i].numero_triangulo != numero_triangulo){
			fprintf(fp, "%d %d %d %d\n",malla[i].numero_triangulo, malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);
		}
   	}
   
   
   fclose ( fp );
}

int tamano_node(){

    FILE *fp;
	int res;
	
	fp = fopen("node", "r");
	rewind(fp);	
	fscanf(fp,"%d *\n", &res);    
    fclose(fp);
    
    return res;
    
}

int tamano_ele(){
	FILE *fp;
	int res;
	
	fp = fopen("ele", "r");
	rewind(fp);	
	fscanf(fp,"%d *\n", &res);    
    fclose(fp);
    
    return res;
}