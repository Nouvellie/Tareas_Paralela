#include <stdio.h>

struct punto{
	float coordenadas[2];
};

struct arista{
	int numero;
	struct punto puntos[2];
};

struct triangulo{
	struct punto vertices[3];
	float angulos[3];
	int numero_triangulo;
	int aristas[3];
};