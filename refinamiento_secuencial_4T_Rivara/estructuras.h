#include <stdio.h>

struct punto{
	float coordenadas[2];
};

struct arista{
	int numero;
	struct punto vertices[2];
};

struct arista_mayor{
	float distancia_mayor;
	struct punto vertices_arista_mayor[2];
	struct punto punto_medio;
	struct punto vertice_opuesto;
};

struct elementos_adyacentes{
	struct arista arista_adyacente[3];
	int triangulos_adyacentes[3];
};

struct triangulo{
	struct punto vertices[3];
	float angulos[3];
	int numero_triangulo;
	struct arista aristas[3];
	struct arista_mayor elemento_mayor;
	struct elementos_adyacentes elemento_adyacente;
};

