#include <stdio.h>
#include <time.h>

typedef struct bola_numero bola;
typedef struct carton carton_bingo;

int no_repetir_numero_bolas(int numero_aleatorio, int tamano_vector,bola lista[]){
	for(int i=0;i < tamano_vector;i++){
		if(numero_aleatorio == (lista[i].numero-1)){
			return 0;
		}
	}	
	return 1;
}

int no_repetir_numero_carton(int numero_aleatorio, int p, int q,carton_bingo (*matriz)[5]){
	for(int i=0;i < p;i++){
		if(i==(p-1)){
			for(int j=0;j < q;j++){
				if(numero_aleatorio == (matriz[i][j].numero-1)){
					return 0;
				}
			}
		}else{
			for(int j=0;j < 5;j++){
				if(numero_aleatorio == (matriz[i][j].numero-1)){
					return 0;
				}
			}
		}
		
	}	
	return 1;
}

void llenar_vector_bolas(bola vector_bolas[60]){
	for(int i=0;i<60;i++){
		//1 al 14 amarillas
		if(i<14){
			vector_bolas[i].color='y';
			vector_bolas[i].numero=i;
		}else{
			//15 al 29 azules
			if(i<29){
				vector_bolas[i].color='b';
				vector_bolas[i].numero=i;
			}else{
				//30 al 44 rojo
				if(i<44){
					vector_bolas[i].color='r';
					vector_bolas[i].numero=i;
				}else{
					//45 al 60 verde
					if(i<60){
						vector_bolas[i].color='g';
						vector_bolas[i].numero=i;
					}
				}
			}
		}
	}
}

void llenar_distribucion_bolas(bola lista[]){
	srand(time(0));
	int numero_aleatorio;
	for(int i=0;i < 30; i++){
		numero_aleatorio=rand()%59;
		while(no_repetir_numero_bolas(numero_aleatorio,i,lista)==0){
			numero_aleatorio=rand()%59;
		}
		if(numero_aleatorio < 14){
			lista[i].numero=numero_aleatorio+1;
			lista[i].color='y';
		}else{
			if(numero_aleatorio < 29){
				lista[i].numero=numero_aleatorio+1;
				lista[i].color='b';
			}else{
				if(numero_aleatorio < 44){
					lista[i].numero=numero_aleatorio+1;
					lista[i].color='r';
				}else{
					if(numero_aleatorio < 60){
						lista[i].numero=numero_aleatorio+1;
						lista[i].color='g';
					}
				}
			}
		}
	}
}

void crear_carton(carton_bingo (*m)[5], int num_carton, carton_bingo lista[]){
	srand(time(0)*num_carton+num_carton);
	int numero_aleatorio;
	int contador=0;
	if(num_carton==1){
		contador=0;
	}else{
		if(num_carton==2){
			contador=15;
		}else{
			if(num_carton==3){
				contador=30;
			}else{
				if(num_carton=4){
					contador=45;
				}
			}
		}
	}
	for(int i=0;i < 3;i++){
		for(int j=0; j < 5;j++){
			numero_aleatorio=rand()%59;
			while(no_repetir_numero_carton(numero_aleatorio,(i+1),(j+1),m)==0){
				numero_aleatorio=rand()%59;
			}

			m[i][j].numero=numero_aleatorio+1;
			m[i][j].marcado='n';
			m[i][j].numero_carton=num_carton;

			//Llenamos el vector
			lista[contador].numero=numero_aleatorio+1;
			lista[contador].marcado='n';
			lista[contador].numero_carton=num_carton;

			contador=contador+1;
		}
	}
}
