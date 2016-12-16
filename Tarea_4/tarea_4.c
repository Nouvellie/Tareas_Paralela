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

    bola vector_bolas[60];
    llenar_vector_bolas(&vector_bolas);
    if(rank==root){
    	for(int i=0;i<60;i++){
    		printf(" %d %c",vector_bolas[i].numero,vector_bolas[i].color);
    	}
    }
     
     MPI_Finalize();
     return 0;

 }
