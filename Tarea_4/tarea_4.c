#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <estructuras.h>
#include <metodos.h>

#define length(x) (sizeof(x)/sizeof(x[0]))

typedef struct bola_numero bola;
typedef struct carton carton_bingo;

int main(int argc, char** argv) {
	int rank;
	int size;
    MPI_Init(&argc, &argv);

	//De aca sacamos el tamaño de los nodos que asignamos con el mpirun
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int root;
    root=0;
    //Creamos el tipo de dato que enviaremos por mpi
    int blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_INT, MPI_CHAR};
    MPI_Datatype MPI_bola_numero;
    MPI_Aint disps[2];
    disps[0] = offsetof( bola, numero );
    disps[1] = offsetof( bola, color );

    MPI_Type_create_struct(2, blocklengths, disps, types, &MPI_bola_numero);
    MPI_Type_commit(&MPI_bola_numero);

    //Defnimos este tipo de dato, para crear las bolas
    
    int cantidad_cartones=4*15;
    int lim_inferior=cantidad_cartones/size;

    bola vector_bolas[60];
    bola distribucion_bolas[30];
    //carton_bingo *datos_carton=malloc(sizeof(int)*cantidad_cartones);
    carton_bingo datos_cartones[cantidad_cartones];
    carton_bingo datos_nodos[array_split(cantidad_cartones,size)[rank]-rank*lim_inferior];
    //Creamos los 4 cartones
    carton_bingo carton_uno[3][5];
    carton_bingo carton_dos[3][5];
    carton_bingo carton_tres[3][5];
    carton_bingo carton_cuatro[3][5];
    
    if(rank==root){
        llenar_vector_bolas(&vector_bolas);
        llenar_distribucion_bolas(&distribucion_bolas);
        crear_carton(&carton_uno,1,&datos_cartones);
        crear_carton(&carton_dos,2,&datos_cartones);
        crear_carton(&carton_tres,3,&datos_cartones);
        crear_carton(&carton_cuatro,4,&datos_cartones);

        /*for(int i=0;i < 30 ;i++){
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
        */
        printf("\n");
        printf("\n");



    }
    MPI_Bcast(&distribucion_bolas,30,MPI_bola_numero,root,MPI_COMM_WORLD);
    MPI_Scatter(&datos_cartones,array_split(cantidad_cartones,size)[rank]-rank*lim_inferior,MPI_INT,&datos_nodos,array_split(cantidad_cartones,size)[rank]-rank*lim_inferior,MPI_INT,root,MPI_COMM_WORLD); 
    
    /*for(int i=0;i< array_split(cantidad_cartones,size)[rank]-rank*lim_inferior;i++){
        printf(" %d %c %d\n",datos_nodos[i].numero,datos_nodos[i].marcado,rank);
    }*/

    for(int i=0;i<30;i++){
        printf("%d %c %d\n",distribucion_bolas[i].numero,distribucion_bolas[i].color,rank);
    }

    MPI_Finalize();
     return 0;

 }
