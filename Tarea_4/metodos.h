#include <stdio.h>

typedef struct bola_numero bola;
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