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

    //Creamos el tipo de dato que enviaremos por mpi SOLO DE LA ESTRUCTURA BOLA_NUMERO
    int blocklengths_bola[2] = {1,1};
    MPI_Datatype types_bola[2] = {MPI_INT, MPI_CHAR};
    MPI_Datatype MPI_BOLA_NUMERO;
    MPI_Aint disps_bola[2];
    disps_bola[0] = offsetof( bola, numero );
    disps_bola[1] = offsetof( bola, color );

    MPI_Type_create_struct(2, blocklengths_bola, disps_bola, types_bola, &MPI_BOLA_NUMERO);
    MPI_Type_commit(&MPI_BOLA_NUMERO);

    //Creamos el tipo de dato que enviaremos por mpi SOLO DE LA ESTRUCTURA CARTON
    int blocklengths_carton[3] = {1,1,1};
    MPI_Datatype types_carton[3] = {MPI_INT,MPI_INT, MPI_CHAR};
    MPI_Datatype MPI_CARTON;
    MPI_Aint disps_carton[3];
    disps_carton[0] = offsetof( carton_bingo, numero );
    disps_carton[1] = offsetof( carton_bingo, numero_carton );
    disps_carton[2] = offsetof( carton_bingo, marcado );

    MPI_Type_create_struct(3, blocklengths_carton, disps_carton, types_carton, &MPI_CARTON);
    MPI_Type_commit(&MPI_CARTON);

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

        for(int i=0;i < 30 ;i++){
            printf(" %d",distribucion_bolas[i].numero);
        }
        printf("\n");
        printf("\n");
        printf("Carton 1\n");
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d",carton_uno[i][j].numero);
            }
            printf("\n");
        }
        printf("\n");
        printf("Carton 2\n");

        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d",carton_dos[i][j].numero);
            }
            printf("\n");
        }
        printf("\n");
        printf("Carton 3\n");
        
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d",carton_tres[i][j].numero);
            }
            printf("\n");
        }
        printf("\n");
        printf("Carton 4\n");
        
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d",carton_cuatro[i][j].numero);
            }
            printf("\n");
        }
        
        printf("\n");
        printf("\n");



    }

    // Enviamos una copia a todos los nodos de las 30 bolas al azar que se lanzan en la mesa, para posteriormente marcar los cartones en cada nodo
    MPI_Bcast(&distribucion_bolas,30,MPI_BOLA_NUMERO,root,MPI_COMM_WORLD);
    MPI_Scatter(&datos_cartones,array_split(cantidad_cartones,size)[rank]-rank*lim_inferior,MPI_CARTON,&datos_nodos,array_split(cantidad_cartones,size)[rank]-rank*lim_inferior,MPI_CARTON,root,MPI_COMM_WORLD); 

    MPI_Finalize();
     return 0;

 }