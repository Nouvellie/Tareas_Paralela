
int lectura_ele(int (*ele)[4], int size_ele){
	FILE *fichero;
   char nombre[10] = "mesh.ele";
   int i, size;
   size_ele=0;

   fichero = fopen( nombre, "r" );
   printf( "Fichero: Elements ");
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
      size_ele++;
      fscanf( fichero, "%d %d %d %d\n", &ele[i][0], &ele[i][1], &ele[i][2], &ele[i][3] );
      printf( "%d %d %d %d\n", ele[i][0], ele[i][1], ele[i][2], ele[i][3] );
   }

   if( !fclose(fichero) )
      printf( "Fichero cerrado\n" );
   else
   {
      printf( "Error: fichero NO CERRADO\n" );
      return 1;
   }

   return size_ele;

}

int eliminar_triangulo_ele(int numero_triangulo,int (*ele)[4], int size_ele){

   FILE *fp;
   size_ele--;
      fp = fopen ( "mesh.ele", "w" );
      fprintf(fp, "%d\n",size_ele);

      for(int i=0;i < size_ele+1;i++){
          if(ele[i][0] != numero_triangulo){
            if(i != size_ele){
                fprintf(fp, "%d %d %d %d\n",ele[i][0], ele[i][1],ele[i][2], ele[i][3]);
            }else{
               fprintf(fp, "%d %d %d %d",ele[i][0], ele[i][1],ele[i][2], ele[i][3]);
            }
          }
      }
   
   
   fclose ( fp );
   return size_ele;

}

int tamano_ele(){
   FILE *fp;
   int res;
   
   fp = fopen("mesh.ele", "r");
   rewind(fp); 
   fscanf(fp,"%d *\n", &res);    
    fclose(fp);
   
    return res;
}