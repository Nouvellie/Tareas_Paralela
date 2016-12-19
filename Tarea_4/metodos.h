#include <stdio.h>

typedef struct bola_numero bola;
typedef struct carton carton_bingo;

int no_repetir_numero(int numero_aleatorio, int tamano_vector,bola lista[]){
	for(int i=0;i < tamano_vector;i++){
		if(numero_aleatorio == lista[i].numero-1){
			return 0;
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

int *llenar_distribucion_bolas(){
	int numero_aleatorio;
	bola *lista=malloc(30*sizeof(int));
	for(int i;i < 30; i++){
		numero_aleatorio=rand()%59;
		while(no_repetir_numero(numero_aleatorio,i,lista)==0){
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
	return lista;
}
