#include <stdio.h>

typedef struct bola_numero bola;
typedef struct carton carton_bingo;

int una_linea(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y' && m[0][1].marcado=='y' && m[0][2].marcado=='y' && m[0][3].marcado=='y' && m[0][4].marcado=='y'){
		return 1;
	}else{
		if(m[1][0].marcado=='y' && m[1][1].marcado=='y' && m[1][2].marcado=='y' && m[1][3].marcado=='y' && m[1][4].marcado=='y'){
			return 1;
		}else{
			if(m[2][0].marcado=='y' && m[2][1].marcado=='y' && m[2][2].marcado=='y' && m[2][3].marcado=='y' && m[2][4].marcado=='y'){
				return 1;
			}else{
				return 0;
			}
		}
	}
}

int dos_lineas(carton_bingo (*m)[5]){
	if((m[0][0].marcado=='y' && m[0][1].marcado=='y' && m[0][2].marcado=='y' && m[0][3].marcado=='y' && m[0][4].marcado=='y') && (m[1][0].marcado=='y' && m[1][1].marcado=='y' && m[1][2].marcado=='y' && m[1][3].marcado=='y' && m[1][4].marcado=='y')){
		return 1;
	}else{
		if((m[0][0].marcado=='y' && m[0][1].marcado=='y' && m[0][2].marcado=='y' && m[0][3].marcado=='y' && m[0][4].marcado=='y') && (m[2][0].marcado=='y' && m[2][1].marcado=='y' && m[2][2].marcado=='y' && m[2][3].marcado=='y' && m[2][4].marcado=='y')){
			return 1;
		}else{
			if((m[1][0].marcado=='y' && m[1][1].marcado=='y' && m[1][2].marcado=='y' && m[1][3].marcado=='y' && m[1][4].marcado=='y') && (m[2][0].marcado=='y' && m[2][1].marcado=='y' && m[2][2].marcado=='y' && m[2][3].marcado=='y' && m[2][4].marcado=='y')){
				return 1;
			}else{
				return 0;
			}
		}
	}
}

//Techo
int fig_uno(carton_bingo (*m)[5]){
	if(m[2][0].marcado=='y' && m[1][1].marcado=='y' && m[0][2].marcado=='y' && m[1][3].marcado=='y' && m[2][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Copa
int fig_dos(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y' && m[1][1].marcado=='y' && m[2][2].marcado=='y' && m[1][3].marcado=='y' && m[0][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Cruz
int fig_tres(carton_bingo (*m)[5]){
	if(m[0][2].marcado=='y' && m[1][2].marcado=='y' && m[2][2].marcado=='y' && m[1][0].marcado=='y' && m[1][1].marcado=='y' && m[1][2].marcado=='y' && m[1][3].marcado=='y' && m[1][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

int fig_cuatro(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y' && m[0][1].marcado=='y' && m[0][2].marcado=='y' && m[0][3].marcado=='y' && m[0][4].marcado=='y' && m[1][1].marcado=='y' && m[1][3].marcado=='y' && m[2][2].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

int fig_cinco(carton_bingo (*m)[5]){
	if(m[2][0].marcado=='y' && m[2][1].marcado=='y' && m[2][2].marcado=='y' && m[2][3].marcado=='y' && m[2][4].marcado=='y' && m[1][1].marcado=='y' && m[1][3].marcado=='y' && m[0][2].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Cuadrado
int fig_seis(carton_bingo (*m)[5]){
	if(m[0][1].marcado=='y' && m[0][2].marcado=='y' && m[0][3].marcado=='y' && m[1][1].marcado=='y' && m[1][3].marcado=='y' && m[2][1].marcado=='y' && m[2][2].marcado=='y' && m[2][3].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Ajedrez
int fig_siete(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[0][2].marcado=='y' && m[0][4].marcado=='y' && m[1][1].marcado=='y' && m[1][3].marcado=='y' && m[2][0].marcado=='y' && m[2][2].marcado=='y' && m[2][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Corona
int fig_ocho(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[1][0].marcado=='y'&& m[2][0].marcado=='y'&& m[0][4].marcado=='y'&& m[1][4].marcado=='y'&& m[2][4].marcado=='y'&& m[1][1].marcado=='y'&& m[0][2].marcado=='y'&& m[1][3].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Corona sin cacho
int fig_nueve(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[1][0].marcado=='y'&& m[2][0].marcado=='y'&& m[0][4].marcado=='y'&& m[1][4].marcado=='y'&& m[2][4].marcado=='y'&& m[1][1].marcado=='y'&& m[1][3].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

//Cofre
int fig_diez(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[1][0].marcado=='y'&& m[2][0].marcado=='y'&& m[0][4].marcado=='y'&& m[1][4].marcado=='y'&& m[2][4].marcado=='y'&& m[1][1].marcado=='y'&& m[0][2].marcado=='y'&& m[1][3].marcado=='y' && m[2][2].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

int fig_once(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[0][1].marcado=='y'&& m[0][2].marcado=='y'&& m[0][3].marcado=='y'&& m[0][4].marcado=='y'&& m[2][0].marcado=='y'&& m[2][1].marcado=='y'&& m[2][2].marcado=='y'&& m[2][3].marcado=='y'&& m[2][4].marcado=='y'&& m[1][1].marcado=='y'&& m[1][3].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

int fig_bonus(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[0][1].marcado=='y'&& m[0][2].marcado=='y'&& m[0][3].marcado=='y'&& m[0][4].marcado=='y'&& m[2][0].marcado=='y'&& m[2][1].marcado=='y'&& m[2][2].marcado=='y'&& m[2][3].marcado=='y'&& m[2][4].marcado=='y'&& m[1][0].marcado=='y'&& m[1][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}

int fig_bingo(carton_bingo (*m)[5]){
	if(m[0][0].marcado=='y'&& m[0][1].marcado=='y'&& m[0][2].marcado=='y'&& m[0][3].marcado=='y'&& m[0][4].marcado=='y'&& m[2][0].marcado=='y'&& m[2][1].marcado=='y'&& m[2][2].marcado=='y'&& m[2][3].marcado=='y'&& m[2][4].marcado=='y'&& m[1][0].marcado=='y'&& m[1][1].marcado=='y'&& m[1][2].marcado=='y'&& m[1][3].marcado=='y'&& m[1][4].marcado=='y'){
		return 1;
	}else{
		return 0;
	}
}