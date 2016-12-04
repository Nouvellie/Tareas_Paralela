from mpi4py import MPI
import random
import math

#Generamos una funcion para crear una lista con numeros aleatorios que toman valor de 0 a 1
def lista_aleatorios(n):
	lista=[0] *n
	for i in range(n):
		lista[i]=random.random()
	return lista

def reajuste_asignacion(num_operaciones, num_procesos):
	a=num_operaciones//num_procesos
	b=a*num_procesos
	if b==num_operaciones:
		return 0
	else:
		return num_operaciones-b

comm = MPI.COMM_WORLD

#Conocemos el numero de nodos totales
size = comm.Get_size()
rank = comm.Get_rank()

root = 0

#Este es el promedio de la lista completa
promedio=0

#La Esta variable "sumatoria", es el argumento de la sumatoria de la varianza de la muestra
sumatoria=0
varianza=0
sumas_reajuste=0.0

#Generamos numeros aleatorios entre 0 y 1, el tamanho de la muestra es 100
l=lista_aleatorios(100)

#Calculamos el tamanho total por subdivision de la lista, en el caso de tamanho 100 la subdivision es de 25 
div_tamano = 100 / size

reajuste=reajuste_asignacion(100,size)

#Nos ubicamos en el nodo maestro rank=0
if rank == root:
	#sacamos el promedio total en el nodo maestro
	for i in range(100):
		promedio=promedio+l[i]
	promedio=promedio / 100

#Enviamos el promedio a todos los nodos con bcast
promedio = comm.bcast(promedio, root=root)

#Enviamos la lista generada a todos los nodos (no es necesario ya que la lista la generamos afuera del nodo maestro)
l = comm.bcast(l,root=root)

#Hacemos la sumatoria, pero en forma paralela, definiendo los limites, en el caso de la lista 1, rank=0 recorrera de 0 a 24 tomando esos valores de la lista y restando el promedio total ya calculado. En el rank=1 parte de 25 y llegaria hasta 49 y asi sucesivamente
for i in range(div_tamano*rank, div_tamano*(rank+1)):
	#Seria la resta al cuadrado del valor de esa posicion con el promedio
	sumatoria=((l[i]-promedio)*(l[i]-promedio))+sumatoria

#Aca enviamos todas las sumatorias calculadas en cada nodo al nodo maestro o rank=0
sumatoria = comm.gather(sumatoria, root=root)

if rank == root:

	#Sumamos las sumatorias calculadas paralelamente en cada nodo y con esto podemos conocer la varianza
	if reajuste != 0:
		for i in range(100-reajuste,100):
			sumas_reajuste=((l[i]-promedio)*(l[i]-promedio))+sumas_reajuste
	varianza=sumas_reajuste
	for i in range(size):
		varianza=sumatoria[i]+varianza
	varianza=varianza/100
	
	#La desviacion estandar seria la raiz de la varianza
	desviacion_estandar=math.sqrt(varianza)
	
	print "La varianza es", varianza
	print "La desviacion estandar es", desviacion_estandar
	print "Desea ver la muestra? (S/N)"
	respuesta=raw_input()
	if respuesta == "S":
		print "La muestra es la siguiente:", l
	elif respuesta == "s":
		print "La muestra es la siguiente:", l
