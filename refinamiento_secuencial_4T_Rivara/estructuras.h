#include <stdio.h>

struct punto{
	float coordenadas[2];
};

struct triangulo{
	struct punto puntos[3];
	float angulos[3];
	int numero_triangulo;
	int aristas[3];
};