#include <stdio.h>
//#include <metis.h>
#include <math.h> 
#include <estructuras.h>

typedef struct triangulo t;
//Calculamos los angulos, segun los lados del triangulo
void angulo(float a, float b, float c,float *A, float *B, float *C)  {
    *C=acos((c*c-a*a-b*b)/(-2*a*b))*180;
    *A=acos((a*a-b*b-c*c)/(-2*b*c))*180;
    *B=acos((b*b-a*a-c*c)/(-2*a*c))*180;
}

//Saco la distancia entre dos puntos
float distancia(float x0,float y0,float x1,float y1) {
    float dist;
    dist=sqrt( (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    return dist;
}

//Distancia mayor
float *distancia_mayor(t t1){
	//este vector retorna la distancia mayor y el punto opuesto a esta distancia
	float *vector=malloc(3*sizeof(int));
	//A=0, B=1, C=2
	float distancia_AB=distancia(t1.vertices[0].coordenadas[0], t1.vertices[0].coordenadas[1],t1.vertices[1].coordenadas[0], t1.vertices[1].coordenadas[1]);
	float distancia_AC=distancia(t1.vertices[0].coordenadas[0], t1.vertices[0].coordenadas[1],t1.vertices[2].coordenadas[0], t1.vertices[2].coordenadas[1]);
	float distancia_BC=distancia(t1.vertices[1].coordenadas[0], t1.vertices[1].coordenadas[1],t1.vertices[2].coordenadas[0], t1.vertices[2].coordenadas[1]);
	if(distancia_AB > distancia_AC){
		if(distancia_AB > distancia_BC){
			vector[0]=distancia_AB;
			vector[1]=t1.vertices[2].coordenadas[0];
			vector[2]=t1.vertices[2].coordenadas[1];
			return vector;
		}else{
			vector[0]=distancia_BC;
			vector[1]=t1.vertices[0].coordenadas[0];
			vector[2]=t1.vertices[0].coordenadas[1];
			return vector;
		}
	}else{
		if(distancia_AC > distancia_BC){
			vector[0]=distancia_AC;
			vector[1]=t1.vertices[1].coordenadas[0];
			vector[2]=t1.vertices[1].coordenadas[1];
			return vector;
		}else{
			vector[0]=distancia_BC;
			vector[1]=t1.vertices[0].coordenadas[0];
			vector[2]=t1.vertices[0].coordenadas[1];
			return vector;
		}
	}
}

float *punto_medio(float x0, float y0, float x1, float y1){
	float *coordenadas=malloc(2*sizeof(int));
	coordenadas[0]=(float)((x0+x1))/2;
	coordenadas[1]=(float)((y0+y1))/2;
	return coordenadas;
}

void realizar_biseccion_4T(t t1,t malla[]){
	float distancia=distancia_mayor(t1)[0];
	float punto_opuesto[2]={distancia_mayor(t1)[1],distancia_mayor(t1)[2]};
	float puntos_distancia[4];
	float punto_medio_dmayor[2];
	int contador=0;
	
	punto_medio_dmayor[0]=punto_medio(puntos_distancia[0],puntos_distancia[1],puntos_distancia[2],puntos_distancia[3])[0];
	punto_medio_dmayor[1]=punto_medio(puntos_distancia[0],puntos_distancia[1],puntos_distancia[2],puntos_distancia[3])[1];

}
//p0, p1, p2 son vertices del triangulo
void refinamiento_triangulacion(t t1,t malla[]){

}
int main(){
	
	return 0;
}