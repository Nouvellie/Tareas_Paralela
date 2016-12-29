#include <stdio.h>
#include <math.h> 
#include <estructuras.h>
#include <metodos.h>
#include <manejo_ficheros.h>

typedef struct triangulo t;
typedef struct punto p;
//Calculamos los angulos, segun los lados del triangulo

int main(){
	//system("clear");
	int size_ele=tamano_ele();
	t malla[size_ele];

	int triangulos_refinar[size_ele];

	llenado_malla(&malla);
	printf("\n");
	printf("DATOS DEL TRIANGULOS\n");
	for(int i=0;i<size_ele;i++){
		printf("%d %d %d %d\n",malla[i].numero_triangulo,malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);
	}
	printf("\n");
	printf("ANGULOS DE LOS TRIANGULOS\n");
	for(int i=0;i<size_ele;i++){
		printf("%d %f %f %f\n",malla[i].numero_triangulo,malla[i].angulos[0].grados,malla[i].angulos[1].grados, malla[i].angulos[2].grados);
	}
	printf("\n");
	printf("ARISTAS DEL TRIANGULO\n");
	for(int i=0;i<size_ele;i++){
		printf("%d %d %d %d\n",malla[i].numero_triangulo,malla[i].aristas[0].numero, malla[i].aristas[1].numero, malla[i].aristas[2].numero);
	}
	//eliminar_triangulo_ele(3,malla);
	//llenado_malla(malla);
	//refinamiento(18, &malla);

	//criterio_refinamiento(triangulos_refinar,5,malla);


	//printf("%d %f %f %f", malla[0].numero_triangulo, malla[0].angulos[0].grados, malla[0].angulos[1].grados, malla[0].angulos[2].grados);


	/*for(int i=0;i<size_ele;i++){
		printf("%d",triangulos_refinar[i]);
	}*/
	return 0;
}