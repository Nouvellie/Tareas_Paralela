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

    bola vector_bolas[60];
    bola distribucion_bolas[30];
    carton_bingo carton_uno[3][5];
    llenar_vector_bolas(&vector_bolas);
    llenar_distribucion_bolas(&distribucion_bolas);
    crear_carton(&carton_uno);
    
    if(rank==root){
        for(int i=0;i < 3;i++){
            for(int j=0; j < 5;j++){
                printf(" %d %c",carton_uno[i][j].numero,carton_uno[i][j].marcado);
            }
            printf("\n");
        }
    }
    MPI_Scatter(datos,TAMA,MPI_INT,mis_datos,TAMA,MPI_INT,root,MPI_COMM_WORLD);
     MPI_Finalize();
     return 0;

 }
