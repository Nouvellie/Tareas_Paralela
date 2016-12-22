#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <estructuras.h>
#include <metodos.h>

int main(int argc, char** argv) {
	int rank;
	int size;
    MPI_Init(&argc, &argv);

	//De aca sacamos el tamaño de los nodos que asignamos con el mpirun
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int root;
    root=0;

    //Defnimos este tipo de dato, para crear las bolas
    typedef struct bola_numero bola;
    typedef struct carton carton_bingo;
    int cantidad_cartones=4*15;
    int lim_inferior=cantidad_cartones/size;

    bola vector_bolas[60];
    bola distribucion_bolas[30];
    //carton_bingo *datos_carton=malloc(sizeof(int)*cantidad_cartones);
    carton_bingo datos_carton[60];
    //Creamos los 4 cartones
    carton_bingo carton_uno[3][5];
    carton_bingo carton_dos[3][5];
    carton_bingo carton_tres[3][5];
    carton_bingo carton_cuatro[3][5];
    
    if(rank==root){
        llenar_vector_bolas(&vector_bolas);
        llenar_distribucion_bolas(&distribucion_bolas);
        crear_carton(&carton_uno,1,&datos_carton);
        crear_carton(&carton_dos,2,&datos_carton);
        crear_carton(&carton_tres,3,&datos_carton);
        crear_carton(&carton_cuatro,4,&datos_carton);

        for(int i=0;i < 30 ;i++){
            printf(" %d",distribucion_bolas[i].numero);
        }
        printf("\n");
        printf("\n");
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d %c",carton_uno[i][j].numero,carton_uno[i][j].marcado);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");

        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d %c",carton_dos[i][j].numero,carton_dos[i][j].marcado);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d %c",carton_tres[i][j].numero,carton_tres[i][j].marcado);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d %c",carton_cuatro[i][j].numero,carton_cuatro[i][j].marcado);
            }
            printf("\n");
        }

        printf("\n");
        printf("\n");

        for(int i=0;i < 8;i++){
            printf(" %d", array_split(100,8)[i]);
        }
    }
    //MPI_Scatter(&datos_carton,array_split[rank]-rank*lim_inferior,MPI_INT,mis_datos,array_split[rank]-rank*lim_inferior,MPI_INT,root,MPI_COMM_WORLD); 
    MPI_Finalize();
     return 0;

 }
