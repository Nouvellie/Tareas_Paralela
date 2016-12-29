#include <stdio.h>
#include <math.h> 
#include <ficheros.h>

int main(){
	int size=tamano_ele();
	int m[size][4];
	int size_ele;
	size_ele=lectura_ele(m,size_ele);
	printf("%d\n",size_ele );

	size_ele=eliminar_triangulo_ele(15,m,size_ele);

	size_ele=lectura_ele(m,size_ele);

	for(int i=0;i<size_ele;i++){
		printf("%d %d %d %d\n", m[i][0],m[i][1],m[i][2],m[i][3]);
	}
	return 0;
}