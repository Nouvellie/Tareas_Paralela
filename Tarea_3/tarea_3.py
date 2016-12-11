from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

root=0
varianza=0.0
varianza_total=0.0
media=0
promedio_lista=0
if rank == root:
	#Tamaño de la muestra
	n=100

	#no viene de la libreria numpy, genera una lista de numeros random y uniformes de tamaño n -muestra-	
	rand = np.random.uniform(0,1,n)

	#np.mean saca el promedio de la lista rand creada anteriormente
	promedio_lista=np.mean(rand)

	#subdividimos las listas en listas mas pequeñas, para enviarlas por scatter
	data = np.array_split(rand, size)
else:
	#este caso deja vacia nula la subdivision de las listas
	data=None

#aca distribuimos los arreglos a los distintos nodos
data_distribuida = comm.scatter(data, root=root)

#Les entregamos la informacion del promedio de la lista general a los nodos, para que puedan calcular la varianza
promedio_lista=comm.bcast(promedio_lista, root=root)

#Sacamos la varianza parcial de las listas, len nos sirve para determinar el largo de nuestro arreglo, ya que el tamaño lo genera el array_split
for i in range(len(data_distribuida)):
	varianza=((promedio_lista-data_distribuida[i])**2)+varianza

varianza = comm.gather(varianza, root=root)

if rank == root:
	#Sumamos las varianzas parciales y llegando a nuesto resultado
	for i in range(size):
		varianza_total=varianza[i]+varianza_total
	varianza_total=varianza_total/n
	print "La varianza es", varianza_total
	print "La media es", promedio_lista