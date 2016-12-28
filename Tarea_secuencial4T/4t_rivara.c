#include <stdio.h>
#include <math.h> 
#include <estructuras.h>
#include <metodos.h>
#include <manejo_ficheros.h>

typedef struct triangulo t;
typedef struct punto p;
//Calculamos los angulos, segun los lados del triangulo

void realizar_biseccion_4T(t t1,t malla[]){
	//Se llenan los datos del triangulo a biseccionar
	//Suponiendo que la malla y el triangulo estan con sus respectivos datos
	
}
//p0, p1, p2 son vertices del triangulo
void refinamiento_triangulacion(t t1,t malla[]){

}
int main(){
	//system("clear");
	t malla[30];
	p puntos;
	puntos.coordenadas[0]=-1.5555;
	puntos.coordenadas[1]=2.6666;
	//mostrar_vertices();

	agregar_vertice_node(puntos);
	llenado_malla(malla);

	return 0;
}