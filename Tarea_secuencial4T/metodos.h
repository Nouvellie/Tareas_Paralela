#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length(x) (sizeof(x)-sizeof(x[0]))

typedef struct triangulo t;
typedef struct punto p;
typedef struct arista arist;
typedef struct triangulos_afectados ta;
ta lista_tafectados;

int triangulo_afectado(t t1){
	for(int i=0;i<lista_tafectados.size;i++){
		if(t1.numero_triangulo==lista_tafectados.t_afectados[i]){
			return 1;
		}
	}
	return 0;
}

int ecuacion_recta(p x, p y, p z){
	//y-y0=m(x-x0)
	//m=(y1-y0)/(x1-x0)
	float pendiente=(y.coordenadas[1]-x.coordenadas[1])/(y.coordenadas[0]-x.coordenadas[0]);
	if(z.coordenadas[1]-x.coordenadas[1]==pendiente*(z.coordenadas[0]-x.coordenadas[0])){
		return 1;
	}else{
		return 0;
	}
}

void angulo(float a, float b, float c,float *A, float *B, float *C)  {
    *C=acos((c*c-a*a-b*b)/(-2*a*b))*180;
    *A=acos((a*a-b*b-c*c)/(-2*b*c))*180;
    *B=acos((b*b-a*a-c*c)/(-2*a*c))*180;
}

//Saco la distancia entre dos puntos
float distancia( p x, p y) {
    float dist;
    dist=sqrt( (y.coordenadas[0]-x.coordenadas[0])*(y.coordenadas[0]-x.coordenadas[0])+(y.coordenadas[1]-x.coordenadas[1])*(y.coordenadas[1]-x.coordenadas[1]));
    return dist;
}

float *punto_medio( p x, p y){
	float *coordenadas=malloc(2*sizeof(int));
	coordenadas[0]=(float)((x.coordenadas[0]+y.coordenadas[0]))/2;
	coordenadas[1]=(float)((x.coordenadas[1]+y.coordenadas[1]))/2;
	return coordenadas;
}

void generar_angulos(t t1){
	float m1=(t1.vertices[0].nodos.coordenadas[1]-t1.vertices[1].nodos.coordenadas[1])/(t1.vertices[0].nodos.coordenadas[0]-t1.vertices[1].nodos.coordenadas[0]);
	float m2=(t1.vertices[0].nodos.coordenadas[1]-t1.vertices[2].nodos.coordenadas[1])/(t1.vertices[0].nodos.coordenadas[0]-t1.vertices[2].nodos.coordenadas[0]);
	float m3=(t1.vertices[1].nodos.coordenadas[1]-t1.vertices[2].nodos.coordenadas[1])/(t1.vertices[1].nodos.coordenadas[0]-t1.vertices[2].nodos.coordenadas[0]);
	
	//Verificamos que los angulos sean positivos debe haber un peque;o error de angulos
	if(atan((m2-m1)/(1+m2*m1))<0){
		t1.angulos[0].grados=-1*atan((m2-m1)/(1+m2*m1));
		t1.angulos[0].vertice_angulo.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
		t1.angulos[0].vertice_angulo.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
		t1.angulos[0].vertice_angulo.numero=t1.vertices[2].numero;
	}else{
		t1.angulos[0].grados=atan((m2-m1)/(1+m2*m1));
		t1.angulos[0].vertice_angulo.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
		t1.angulos[0].vertice_angulo.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
		t1.angulos[0].vertice_angulo.numero=t1.vertices[2].numero;
	}
	
	if(atan((m3-m1)/(1+m3*m1))<0){
		t1.angulos[1].grados=-1*atan((m3-m1)/(1+m3*m1));
		t1.angulos[1].vertice_angulo.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
		t1.angulos[1].vertice_angulo.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
		t1.angulos[1].vertice_angulo.numero=t1.vertices[1].numero;
	}else{
		t1.angulos[1].grados=atan((m3-m1)/(1+m3*m1));
		t1.angulos[1].vertice_angulo.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
		t1.angulos[1].vertice_angulo.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
		t1.angulos[1].vertice_angulo.numero=t1.vertices[1].numero;
	}	
	//El pequeño error de aproximacion lo resolvemos dandole esos pequeños diferenciales de angulo al ultimo angulo
	t1.angulos[2].grados=180-(t1.angulos[1].grados+t1.angulos[0].grados);
	
	t1.angulos[2].vertice_angulo.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.angulos[2].vertice_angulo.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.angulos[2].vertice_angulo.numero=t1.vertices[0].numero;
}

int *aristas_no_mayores(t t1){
	int *aristas=malloc(2*sizeof(int));
	if(t1.aristas[0].numero == t1.elemento_mayor.arista_mayor.numero){
		//Las dos aristas siguientes no son la de las mayores distancias
		aristas[0]=1;
		aristas[1]=2;
		return aristas;
	}else{
		if(t1.aristas[1].numero==t1.elemento_mayor.arista_mayor.numero){
			aristas[0]=0;
			aristas[1]=2;
			return aristas;
		}else{
			if(t1.aristas[2].numero==t1.elemento_mayor.arista_mayor.numero){
				aristas[0]=0;
				aristas[1]=1;
				return aristas;
			}
		}
	}
}

float *vertices_no_mayores(t t1){
	float *vertices=malloc(4*sizeof(int));
	if(t1.vertices[0].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[0].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
		vertices[0]=t1.vertices[1].nodos.coordenadas[0];
		vertices[1]=t1.vertices[1].nodos.coordenadas[1];
		vertices[2]=t1.vertices[2].nodos.coordenadas[0];
		vertices[3]=t1.vertices[2].nodos.coordenadas[1];
		return vertices;
	}else{
		if(t1.vertices[1].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[1].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
			vertices[0]=t1.vertices[0].nodos.coordenadas[0];
			vertices[1]=t1.vertices[0].nodos.coordenadas[1];
			vertices[2]=t1.vertices[2].nodos.coordenadas[0];
			vertices[3]=t1.vertices[2].nodos.coordenadas[1];
			return vertices;
		}else{
			if(t1.vertices[2].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[2].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
				vertices[0]=t1.vertices[0].nodos.coordenadas[0];
				vertices[1]=t1.vertices[0].nodos.coordenadas[1];
				vertices[2]=t1.vertices[1].nodos.coordenadas[0];
				vertices[3]=t1.vertices[1].nodos.coordenadas[1];
				return vertices;
			}
		}
	}
}

//ELEMENTOS: DISTANCIA MAYOR, VERTICE OPUESTO ARISTA MAYOR, VERTICES QUE PASAN POR LA ARISTA MAYOR, PUNTO MEDIO
void elementos_mayores(t t1){
	//este vector retorna la distancia mayor y el punto opuesto a esta distancia
	//A=0, B=1, C=2
	float distancia_AB=distancia(t1.vertices[0].nodos,t1.vertices[1].nodos);
	float distancia_AC=distancia(t1.vertices[0].nodos,t1.vertices[2].nodos);
	float distancia_BC=distancia(t1.vertices[1].nodos,t1.vertices[2].nodos);
	if(distancia_AB > distancia_AC){
		if(distancia_AB > distancia_BC){
			t1.elemento_mayor.distancia_mayor=distancia_AB;
			//Los primeros son los puntos opuestos
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			//Estos son los dos vertices que pasan por la arista mayor
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[0].nodos,t1.vertices[1].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[0].nodos,t1.vertices[1].nodos)[1];

		}else{
			t1.elemento_mayor.distancia_mayor=distancia_BC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[1];
		}
	}else{
		if(distancia_AC > distancia_BC){
			t1.elemento_mayor.distancia_mayor=distancia_AC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[0].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[0].nodos,t1.vertices[2].nodos)[1];
		}else{
			t1.elemento_mayor.distancia_mayor=distancia_BC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[1];
		}
	}
}

void generar_aristas(t t1){
	t1.aristas[0].numero=1;
	t1.aristas[0].vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.aristas[0].vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.aristas[0].vertices[1].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
	t1.aristas[0].vertices[1].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];

	t1.aristas[1].numero=2;
	t1.aristas[1].vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.aristas[1].vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.aristas[1].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[1].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
	
	t1.aristas[2].numero=3;
	t1.aristas[2].vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
	t1.aristas[2].vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
	t1.aristas[2].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[2].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
}

//t1=t2 y t2=t1 por medio de un auxiliar
void asignar_triangulo(t t1, t t2){
	t1.vertices[0].nodos.coordenadas[0]=t2.vertices[0].nodos.coordenadas[0];
	t1.vertices[0].nodos.coordenadas[1]=t2.vertices[0].nodos.coordenadas[1];
	t1.vertices[1].nodos.coordenadas[0]=t2.vertices[1].nodos.coordenadas[0];
	t1.vertices[1].nodos.coordenadas[1]=t2.vertices[1].nodos.coordenadas[1];
	t1.vertices[2].nodos.coordenadas[0]=t2.vertices[2].nodos.coordenadas[0];
	t1.vertices[2].nodos.coordenadas[1]=t2.vertices[2].nodos.coordenadas[1];
	//Los 3 angulos
	t1.angulos[0]=t2.angulos[0];
	t1.angulos[1]=t2.angulos[1];
	t1.angulos[2]=t2.angulos[2];
	//Arista 1
	t1.aristas[0].vertices[0].nodos.coordenadas[0]=t2.aristas[0].vertices[0].nodos.coordenadas[0];
	t1.aristas[0].vertices[0].nodos.coordenadas[1]=t2.aristas[0].vertices[0].nodos.coordenadas[1];
	t1.aristas[0].vertices[1].nodos.coordenadas[0]=t2.aristas[0].vertices[1].nodos.coordenadas[0];
	t1.aristas[0].vertices[1].nodos.coordenadas[1]=t2.aristas[0].vertices[1].nodos.coordenadas[1];
	//Arista 2
	t1.aristas[1].vertices[0].nodos.coordenadas[0]=t2.aristas[1].vertices[0].nodos.coordenadas[0];
	t1.aristas[1].vertices[0].nodos.coordenadas[1]=t2.aristas[1].vertices[0].nodos.coordenadas[1];
	t1.aristas[1].vertices[1].nodos.coordenadas[0]=t2.aristas[1].vertices[1].nodos.coordenadas[0];
	t1.aristas[1].vertices[1].nodos.coordenadas[1]=t2.aristas[1].vertices[1].nodos.coordenadas[1];
	//Arista 3
	t1.aristas[2].vertices[0].nodos.coordenadas[0]=t2.aristas[1].vertices[0].nodos.coordenadas[0];
	t1.aristas[2].vertices[0].nodos.coordenadas[1]=t2.aristas[1].vertices[0].nodos.coordenadas[1];
	t1.aristas[2].vertices[1].nodos.coordenadas[0]=t2.aristas[1].vertices[1].nodos.coordenadas[0];
	t1.aristas[2].vertices[1].nodos.coordenadas[1]=t2.aristas[1].vertices[1].nodos.coordenadas[1];

	t1.numero_triangulo=t2.numero_triangulo;

	t1.aristas[0].numero=t2.aristas[0].numero;
	t1.aristas[1].numero=t2.aristas[1].numero;
	t1.aristas[2].numero=t2.aristas[2].numero;


}
void asignar_arista(arist a1, arist a2){
	//Aca importan los numeros de vertices, pero copiaremos todos los datos de la arista
	a1.numero=a2.numero;
	a1.vertices[0].numero=a2.vertices[0].numero;
	a1.vertices[1].numero=a2.vertices[0].numero;
	a1.vertices[0].nodos.coordenadas[0]=a2.vertices[0].nodos.coordenadas[0];
	a1.vertices[0].nodos.coordenadas[1]=a2.vertices[0].nodos.coordenadas[1];
	a1.vertices[1].nodos.coordenadas[0]=a2.vertices[1].nodos.coordenadas[0];
	a1.vertices[1].nodos.coordenadas[1]=a2.vertices[1].nodos.coordenadas[1];

}

int comparacion_vertices(arist arista_afectada, t t2){
	if(arista_afectada.vertices[0].numero == t2.vertices[0].numero && arista_afectada.vertices[1].numero == t2.vertices[1].numero){
		return 1;
	}else{
		if(arista_afectada.vertices[0].numero == t2.vertices[0].numero && arista_afectada.vertices[2].numero == t2.vertices[2].numero){
			return 1;
		}else{
			if(arista_afectada.vertices[1].numero == t2.vertices[1].numero && arista_afectada.vertices[2].numero == t2.vertices[2].numero){
				return 1;
			}else{
				return 0;
			}
		}
	}
}

int adyacentes_afectados(int num_triangulo,arist arista_afectada, t malla[]){
	for(int i=0; i < length(malla); i++){
		if(malla[i].numero_triangulo != num_triangulo && comparacion_vertices(arista_afectada,malla[i])==1){
			return malla[i].numero_triangulo;
		}
	}
	return 0;;
}

//Conformidad nivel 1
void biseccion_afectados(int num_triangulo,arist arista_afectada ,t malla[]){
	//Verificamos los triangulos que estan adyacentes, ya que la biseccion altero las 3 aristas serian maximo 3 triangulos
	//adyacentes_afectados(t1, malla);	
	int size=0;
	int num_t=num_triangulo;
	arist arist_afectada;
	asignar_arista(arist_afectada,arista_afectada);
	while(adyacentes_afectados(num_t,arist_afectada,malla)!=0){
		//1° Arista afectada, sabes el triangulo afectado adyacente con la funcion "adyacentes_afectados"
		//2° Generamos un vertice PM "punto medio", este se genera en el triangulo afectado y debe ser la arista mayor
		//3° Punto medio afecta una arista. En este punto hacemos el bucle hasta que al generar un PM no afecte ninguna arista
		num_t=adyacentes_afectados(num_triangulo,arista_afectada,malla);
		//Aca genero el punto medio, para luego formar los triangulos
		//¿Sera necesario guardar estos triangulos para luego aplicar a los triangulos necesarios?
		size++;
		//Se guardan los triangulos en la lista, para luego verificar que triangulo se forma con su punto medio
		lista_tafectados.t_afectados[size]=num_triangulo;
		elementos_mayores(malla[num_t-1]);
		asignar_arista(arist_afectada,malla[num_t-1].elemento_mayor.arista_mayor);
	}
	lista_tafectados.size=size;
}

void generar_triangulos_4T(t t1, t malla[]){
	//Agregamos un nuevo triangulo
	t t2,t3,t4,t5;
	p punto_medio_uno, punto_medio_dos;
	arist a1,a2,a3;
	//Generar elementos mayores
	punto_medio_uno.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].nodos)[0];
	punto_medio_uno.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].nodos)[1];
	
	punto_medio_dos.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].nodos)[0];
	punto_medio_dos.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].nodos)[1];

	//Generando vertices primeramente
	t2.vertices[0].nodos.coordenadas[0]=vertices_no_mayores(t1)[0];
	t2.vertices[0].nodos.coordenadas[1]=vertices_no_mayores(t1)[1];
	t2.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t2.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];

	//Que pasa si el punto medio no pertenece a la arista generada por vertice 1 y vertice opuesto a la arista mayor?
	if(ecuacion_recta(t2.vertices[0].nodos, t1.elemento_mayor.vertice_opuesto.nodos, punto_medio_uno)==1){
		t2.vertices[1].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
		t2.vertices[1].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t2.vertices[1].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
		t2.vertices[1].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t5.vertices[0].nodos.coordenadas[0]=vertices_no_mayores(t1)[2];
	t5.vertices[0].nodos.coordenadas[1]=vertices_no_mayores(t1)[3];
	t5.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t5.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];
	if(ecuacion_recta(t5.vertices[0].nodos, t1.elemento_mayor.vertice_opuesto.nodos, punto_medio_uno)==1){
		t5.vertices[1].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
		t5.vertices[1].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t5.vertices[1].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
		t5.vertices[1].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t3.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t3.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t3.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t3.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];
	t3.vertices[2].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
	t3.vertices[2].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];

	t4.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t4.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t4.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t4.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];
	t4.vertices[2].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
	t4.vertices[2].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];

	asignar_arista(a1,t1.elemento_mayor.arista_mayor);
	asignar_arista(a2,t1.aristas[aristas_no_mayores(t1)[0]]);
	asignar_arista(a3,t1.aristas[aristas_no_mayores(t1)[1]]);

	//Genero los puntos medios en las mallas dependiendo que arista este afectada
	biseccion_afectados(t1.numero_triangulo,a1,malla);
	biseccion_afectados(t1.numero_triangulo,a2,malla);
	biseccion_afectados(t1.numero_triangulo,a3,malla);

	//Generamos las angulos
	generar_angulos(t2);
	generar_angulos(t3);
	generar_angulos(t4);
	generar_angulos(t5);

	//Generamos las aristas
	generar_aristas(t2);
	generar_aristas(t3);
	generar_aristas(t4);
	generar_aristas(t5);


	//Generamos los numeros de triangulo y aristas
	//length es el tamaño de la malla, le agregamos los elementos nuevos y le restamos el triangulo que se bisecciono
	//Reajustamos el tamaño del vector dinamico
	malla=realloc(malla,sizeof(int)*(length(malla)+3));
	for(int i=0; i< length(malla)+3;i++){
		malla[i].numero_triangulo=i+1;
		if(malla[i].numero_triangulo == i+1){
			//En esta posicion estaba anteriormente el triangulo que se bisecciono
			asignar_triangulo(malla[i],t2);
			//t3, t4 y t5 se encuentran los triangulos que vienen al que se bisecciono
			malla[i].numero_triangulo=i+1;
			i=i+1;
		}
		if(i == length(malla)){
			asignar_triangulo(malla[i],t3);
			malla[i].numero_triangulo=i+1;
			i=i+1;
		}else{
			if(i == length(malla)+1){
				asignar_triangulo(malla[i],t4);
				malla[i].numero_triangulo=i+1;
				i=i+1;
			}else{
				if(i == length(malla)+2){
					asignar_triangulo(malla[i],t5);
					malla[i].numero_triangulo=i+1;
					i=i+1;
				}
			}
		}
	}

	
}


void conformidad(){

}

void generar_triangulos_afectados(t malla[]){
	//El length esta mal utilizado, ya que es un vector dinamico
	for(int i=0;i<length(malla);i++){
		if(triangulo_afectado(malla[i])){
			
		}
	}	
}


//Incompleto, solo he generado una matriz y asignar los elementos 
void llenado_malla(t malla[], char fichero[]){
 	FILE *archivo;;
 	char Elements[100][100];
 	char Nodes[100][100];
 	int Elements_enteros[150][150];
 	int j=0,ze=0,zn=0;
 	double num;
 	//char caracteres[100];
 	char string[50][50];
 	int contador=-1;
 	archivo = fopen(fichero,"r");
 	
 	if (archivo == NULL)
 		exit(1);
 	

 	//Recorremos el archivo
 	while (feof(archivo) == 0){
 		contador++;
 		fgets(string[contador],50,archivo);
 	}

        fclose(archivo);

    //Llenamos el vector caracteres, tiene contenido el fichero msh    
    for(int i=0;i<filas_fichero("malla_triangulacion.msh");i++){
    	if(equals(string[i],"$Elements")){
    		printf("Informacion de los ELEMENTOS vertices que le corresponden a cada triangulo\n");
    		i++;
    		while(equals(string[i],"$EndElements")==0){
    			//La siguiente linea de $Elements
    			while(j<50){
    				Elements[ze][j]=string[i][j];
    				j++;
    			}
    			j=0;
    			i++;
    			ze++;	
    		}
    		//printf("%s",string[i]);
    	}else{
    		if(equals(string[i],"$Nodes")){
    			printf("Informacion de los NODES, corresponde a los vertices enumerados\n");
    			i++;
    			while(equals(string[i],"$EndNodes")==0){
    			//La siguiente linea de $Elements
	    			while(j<50){
	    				Nodes[zn][j]=string[i][j];
	    				j++;
	    			}
	    			j=0;
	    			i++;	
	    			zn++;
	    		}

    		}
    	}
    }

    /*for(int i=0;i<9;i++){
   			printf("%s",Nodes[i]);
   	}*/
   	for(int i=0;i<18;i++){
   		printf("%s",Elements[i]);
   	}

   	string_entero(&Elements_enteros,Elements);

   	for(int i=0;i<17;i++){
   		for(int z=0;z<8;z++){
   			printf(" %d",Elements_enteros[i][z]);
   		}
   		printf("\n");
   	}
   
   
}