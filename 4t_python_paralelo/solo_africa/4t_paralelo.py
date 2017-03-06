import numpy as np
import math as mt
from time import time
from mpi4py import MPI

#Calculamos distancia ingresando 2 vertices casteados en enteros y la lista lnodos
def cal_dist(v1,v2,lnodos):
	dist=mt.sqrt(((float(lnodos[v1][1])-float(lnodos[v2][1]))*(float(lnodos[v1][1])-float(lnodos[v2][1])))+((float(lnodos[v1][2])-float(lnodos[v2][2]))*(float(lnodos[v1][2])-float(lnodos[v2][2]))))
	return dist
#Calculamos los angulos con arcoseno ingresando 3 distancias
def angulos(a,b, c):
	lista= [None] * 3
	lista[0]=(mt.acos((c*c-a*a-b*b)/(-2*a*b)))*180/mt.pi
	lista[1]=(mt.acos((a*a-b*b-c*c)/(-2*b*c)))*180/mt.pi
	lista[2]=(mt.acos((b*b-a*a-c*c)/(-2*a*c)))*180/mt.pi
	return lista

#Genera los 3 angulos a todos los triangulos de toda la malla y se los agrega a la lista lelementos
def cal_ang(lnodos,lelementos):
	lista=[None] *3
	for i in range(1,int(lelementos[0][0])+1):
			lista=angulos(cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos),cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos),cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos))
			lelementos[i].append(lista[0])
			lelementos[i].append(lista[1])
			lelementos[i].append(lista[2])

#Calculamos el angulo de un triangulo unicamente, del generado por una biseccion
def cal_ang_solo(lnodos, lelementos):
	lista=[]
	lista=angulos(cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos),cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos),cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos))
	lelementos[-1].append(lista[0])
	lelementos[-1].append(lista[1])
	lelementos[-1].append(lista[2])

#Criterio de refinamiento, si algun angulo del un triangulo es menor al angulo critico se le asigna un 1 de refinar en contraparte 0 de no refinar
def crit_ref(lelementos, crit_ang):
	cant_ref=0
	for i in range(1,int(lelementos[0][0])+1):
		if lelementos[i][4] < crit_ang or lelementos[i][5] < crit_ang or lelementos[i][6] < crit_ang:
			cant_ref=cant_ref+1
			lelementos[i].append(1)
		else:
			lelementos[i].append(0)
	return cant_ref				

#En esta funcion determinamos las distancias mayores y asignaermos los vertices a esa distancia mayor
def arista_larga(lelementos):
	for i in range(1,int(lelementos[0][0])+1):
		lista=[None] * 3
		if (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][2]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][2]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)

#Calculamos la arista larga para un unico elemento, el cual e genera unicamente en la biseccion
def arista_larga_solo(lelementos):
		lista=[None] * 3
		if (cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos) > cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos)) and (cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos) > cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos)
			lista[1]=lelementos[-1][1]
			lista[2]=lelementos[-1][2]
			lelementos[-1].append(lista)
		elif (cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos) > cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos)) and (cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos) > cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos)
			lista[1]=lelementos[-1][1]
			lista[2]=lelementos[-1][3]
			lelementos[-1].append(lista)
		elif (cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos) > cal_dist(int(lelementos[-1][1]),int(lelementos[-1][2]),lnodos)) and (cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos) > cal_dist(int(lelementos[-1][1]),int(lelementos[-1][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[-1][2]),int(lelementos[-1][3]),lnodos)
			lista[1]=lelementos[-1][2]
			lista[2]=lelementos[-1][3]
			lelementos[-1].append(lista)

#Con esto limitamos que el punto medio se agregue a lnodos SI Y SOLO SI ESTE CONSTRUYA UN TRIANGULO NUEVO
def agregar_vertice_lnodos(v1,v2,lnodos):
	a=int(lnodos[0][0])+1
	lnodos[0][0]=a
	lnodos.append([a])
	lnodos[a].append(v1)
	lnodos[a].append(v2)

#Calcula el punto medio			
def pto_mdo(v1, v2):
	v1=int(v1)
	v2=int(v2)
	lista=[None] * 2
	lista[0]=(float(lnodos[v1][1])+float(lnodos[v2][1]))/2
	lista[1]=(float(lnodos[v1][2])+float(lnodos[v2][2]))/2
	return lista

#Se le sacara punto medio a todos los triangulos, pero se analizara despues si es necesario sacar punto medio a la arista mayor de todos los T
def asig_pto_mdo(lelementos):
	lista=[None] * 2
	for i in range(1,int(lelementos[0][0])+1):
		lista=pto_mdo(int(lelementos[i][8][1]),int(lelementos[i][8][2]))
		lelementos[i].append(lista)

def pto_mdoa_ele(lelements,indice,lnodes):
	i=0
	while (lelementos[indice][9][0] == lnodos[i][1] and lelementos[indice][9][1] == lnodos[i][2]) or (i==lnode[0][0]):
		return int(lnodos[i][0])

def crear_indice(lelementos):
	
	ult_crea=int(lelementos[-1][0])+1
	lelementos[0][0]=int(lelementos[0][0])+1
	lelementos.append([ult_crea])
def crear_triangulo(v1, v2, v3,lelementos):
	#Esta lista genera los tres vertices y el numero del triangulo si es refinable 1 y 0
	lista=[None] * 3
	#Genera 3 angulos
	#genera la distancia mas larga y los vertices asociados
	lista3=[None] * 3
	#Genera el punto medio de la arista mayor
	lista4=[None] * 2

	lista[0]=v1
	lista[1]=v2
	lista[2]=v3

	crear_indice(lelementos)
	#se agregaran los 3 vertices en las casillas de la fila nueva -lista[0]-

	lelementos[-1].append(lista[0])
	lelementos[-1].append(lista[1])
	lelementos[-1].append(lista[2])

	cal_ang_solo(lnodos,lelementos)

	#No entra al criterio de refinamiento, pero si al de conformidad
	lelementos[-1].append(0)
	lista3=arista_larga_solo(lelementos)
	#se llena la casilla 8 con la distancia mayor y los dos vertices que contienen la arista mayor
	#Se genera 
	lista4=pto_mdo(lelementos[-1][8][1],lelementos[-1][8][2])
	lelementos[-1].append(lista4)

	pto_opuesto_solo(lelementos)

#Recorremos la matriz de triangulos y preguntamos el primer elemento de cada fila, este nos comparara el num
# de triangulo que buscamos, para luego borrarlo	
def return_indice_ele(lelementos, num_triangulo):
	for i in range(1,int(lelementos[0][0])+1):
		if int(lelementos[i][0]) == num_triangulo:
			return i
	return 0


#REVISAR PUNTO MEDIO, el i es el indice al triangulo que se encontro a refinar -valor 1 a refinar-
def cuatro_t(lelementos, i):
	agregar_vertice_lnodos(lelementos[i][9][0],lelementos[i][9][1],lnodos)
	pto_mdo_uno=pto_mdo(lelementos[i][10],lelementos[i][8][1])
	pto_mdo_dos=pto_mdo(lelementos[i][10],lelementos[i][8][2])
	pto_mdo_mayor=int(lnodos[-1][0])

	agregar_vertice_lnodos(pto_mdo_uno[0],pto_mdo_uno[1],lnodos)
	vertice_pto_mdo_uno=int(lnodos[-1][0])
	
	agregar_vertice_lnodos(pto_mdo_dos[0],pto_mdo_dos[1],lnodos)
	vertice_pto_mdo_dos=int(lnodos[-1][0])

	crear_triangulo(pto_mdo_mayor,lelementos[i][8][1],vertice_pto_mdo_uno,lelementos)
	crear_triangulo(pto_mdo_mayor,lelementos[i][8][2],vertice_pto_mdo_dos,lelementos)
	crear_triangulo(pto_mdo_mayor,lelementos[i][10],vertice_pto_mdo_uno,lelementos)
	crear_triangulo(pto_mdo_mayor,lelementos[i][10],vertice_pto_mdo_dos,lelementos)
	lelementos.pop(i)
	lelementos[0][0]=lelementos[0][0]-1

def pto_opuesto_solo(lelementos):
	if (lelementos[-1][1] != lelementos[-1][8][1]) and (lelementos[-1][1] != lelementos[-1][8][2]):
		lelementos[-1].append(lelementos[-1][1])
	elif (lelementos[-1][2] != lelementos[-1][8][1]) and (lelementos[-1][2] != lelementos[-1][8][2]):
		lelementos[-1].append(lelementos[-1][2])
	elif (lelementos[-1][3] != lelementos[-1][8][1]) and (lelementos[-1][3] != lelementos[-1][8][2]):
		lelementos[-1].append(lelementos[-1][3])
#Calculamos punto opuesto a la arista mayor

def pto_opuesto(lelementos):
	for i in range(1,int(lelementos[0][0])+1):
		if (lelementos[i][1] != lelementos[i][8][1]) and (lelementos[i][1] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][1])
		elif (lelementos[i][2] != lelementos[i][8][1]) and (lelementos[i][2] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][2])
		elif (lelementos[i][3] != lelementos[i][8][1]) and (lelementos[i][3] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][3])

#Leemos el fichero de inicio de los vertices
def leer_node():
	#Lee el fichero .node y lo asigna a la lista lnodos
	#lineas = open("espiral.node").readlines()
	lineas = open("africa473.node").readlines()
	lnodos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]
	return lnodos

#Retornamos el ultimo indice de los vertices, para aplicar la optimizacion antes mencionada	
def ultimo_indice_fijo(lnodes):
	ult_indice = lnodes[-1][0]
	return int(ult_indice)

#Leemos el fichero de inicio de los triangulos
def leer_ele():	
	#Lee el fichero .ele y lo asigna a la lista lelementos
	#lineas = open("espiral.ele").readlines()
	lineas = open("africa473.ele").readlines()
	lelementos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]
	return lelementos

def anadir_linea_ele(lelementos):
	#fp=open('espiral.ele','a')
	fp=open('africa473.ele','a')
	fp.write('\n1')
	fp.close()

#llenamos el fichero en el cual ingresamos los triangulos refinados
def ele_a_pc(lelementos):
	#fp = open("espiralrf.ele","w+")
	fp = open("africarf473_paralelo.ele","w+")
	#contenido = archivo.read()
	#indice = [lelementos[0][0]]

	fp.write(str(lelementos[0][0]))
	fp.write(" ")
	fp.write(str(3))
	for i in range(1,int(lelementos[0][0])+1):
		fp.write(str("\n"))
		fp.write(str(lelementos[i][0]))
		fp.write(" ")
		fp.write(str(lelementos[i][1]))
		fp.write(" ")
		fp.write(str(lelementos[i][2]))
		fp.write(" ")
		fp.write(str(lelementos[i][3]))
	fp.close()

#pasamos al fichero los datos del nodo, sus respectivos vertices
def node_a_pc(lnodos):
	#fp = open("espiralrf.node","w+")
	fp = open("africarf473_paralelo.node","w+")
	#contenido = archivo.read()
#	indice = []
	fp.write(str(lnodos[0][0]))
	fp.write(" ")
	fp.write(str(2))
	for i in range(1,int(lnodos[0][0])+1):
		fp.write("\n")
		fp.write(str(lnodos[i][0]))
		fp.write(" ")
		fp.write(str(lnodos[i][1]))
		fp.write(" ")
		fp.write(str(lnodos[i][2]))
	fp.close()

#Particiones, en este caso particular asignamos unicamente una particion
def part_a_pc(lelementos):
	#fp = open("espiralrf.part","w+")
	fp = open("africarf473_paralelo.part","w+")
	#contenido = archivo.read()
	fp.write(str(lelementos[0][0]))
	fp.write(" ")
	fp.write(str(1))
	for i in range(1,int(lelementos[0][0])+1):
		fp.write("\n")
		fp.write(str(lelementos[i][0]))
		fp.write(" ")
		fp.write(str(1))
	fp.close()

def guardar_puntoCentral(lelementos, lnodos):
	for i in range(1,int(lelementos[0][0])+1):
		punto_central= [None]*2
		punto_central[0]=(float(lnodos[int(lelementos[i][1])][1])+float(lnodos[int(lelementos[i][2])][1])+float(lnodos[int(lelementos[i][1])][1]))/3
		punto_central[1]=(float(lnodos[int(lelementos[i][1])][2])+float(lnodos[int(lelementos[i][2])][2])+float(lnodos[int(lelementos[i][1])][2]))/3
		lelementos[i].append(punto_central)

#Verificamos la conformidad analizando los puntos medios de las 3 aristas, si estas se encuentran como vertice al menos uno, este triangulo no es conforme
def conformidad(lelementos,lnodos,vertices_iniciales, ultimo_indice):
	i=1
	while (i < int(lelementos[0][0])):
		#print i
		if comp_pto_mdo(pto_mdo(int(lelementos[i][1]),int(lelementos[i][2])),pto_mdo(int(lelementos[i][1]),int(lelementos[i][3])),pto_mdo(int(lelementos[i][2]),int(lelementos[i][3])),lnodos,vertices_iniciales, ultimo_indice) == 1:
			#print i
			#print lelementos[i][0] 
			agregar_vertice_lnodos(lelementos[i][9][0],lelementos[i][9][1],lnodos)
			pto_mdo_mayor=int(lnodos[-1][0])
			crear_triangulo(pto_mdo_mayor,lelementos[i][8][1],lelementos[i][10],lelementos)
			crear_triangulo(pto_mdo_mayor,lelementos[i][8][2],lelementos[i][10],lelementos)
			lelementos.pop(i)
			lelementos[0][0]=lelementos[0][0]-1
			i=1 
		else:	
			i=i+1
			
#Entran 3 listas las cuales vamos a comprar con los lnodos
def comp_pto_mdo(pmdo_uno, pmdo_dos,pmdo_tres, lnodos,vertices_iniciales, ultimo_indice):
	for i in range(ultimo_indice,int(lnodos[0][0])):
		if (pmdo_uno[0] == lnodos[i][1] and pmdo_uno[1] == lnodos[i][2]) or (pmdo_dos[0] == lnodos[i][1] and pmdo_dos[1] == lnodos[i][2]) or (pmdo_tres[0] == lnodos[i][1] and pmdo_tres[1] == lnodos[i][2]):
			return 1
	return 0

def dividir_vector(lelementos,size):
	a_refinar=[]
	contador=0
	tamano=int(lelementos[0][0])/size
	for contador in range(size):
		for i in range(tamano*contador,tamano*(contador+1)):
			a_refinar[contador].append(lelementos[i])
	return a_refinar		

def agregar_colaNodos(lista,posicion):
	lista2=[None] * (len(lista)-posicion)
	contador=0
	for i in range(posicion,len(lista)):
		lista2[contador]=lista[i]
		contador=contador+1
	return lista2

################################## Funcion en mpi para resolver conformidad ##################################################

def conformidad_MPI(lelementos,lnodos):
	comm = MPI.COMM_WORLD
	size = comm.Get_size()
	rank = comm.Get_rank()

	root=0

	data=[]
	a_refinar=[]

	lelementos.pop(0)
	lelementos=np.array(lelementos,dtype=object)

	if rank==root:
		a_refinar=np.array_split(lelementos,size)


	data = comm.scatter(a_refinar, root=root)
	lnodos=comm.bcast(lnodos,root=root)

	data2=[None] * (len(data)+1)
	data2[0]=[len(data),3]
	for i in range(1,len(data2)):
		data2[i]=data[i-1]
	#data=np.insert(data,0,1)

	#print data2[-1]
	print "Este es el rank",rank," ",size

	i=1
	while i < int(len(data2)):
		#print i
		if data2[i][7] == 1:
			vertices_iniciale=[None] * 3
			vertices_iniciale[0]=data2[i][1]
			vertices_iniciale[1]=data2[i][2]
			vertices_iniciale[2]=data2[i][3]
			conformidad(data2,lnodos,vertices_iniciale, uif)	
			#contador=contador+1
			i=1
		else:
			i=i+1


	lnodos_xrank=comm.gather(lnodos,root=root)
	lelementos_xrank=comm.gather(data2,root=root)

	if rank==root:
		tamanho_anterior=len(lelementos)
		
		for t in range(0,len(lnodos_xrank)):
			if t != 0:
				lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)
				for j in range(0,len(lnodos_xrank[t])):
					lnodos.append(lnodos_xrank[t][j])
			else:
				lnodos=lnodos_xrank[t]
				lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)

		lnodos[0][0]=len(lnodos)-1
		for t in range(1,len(lnodos)):
			lnodos[t][0]=t

		acumulado=len(lnodos_xrank[0])
		for t in range(0,len(lelementos_xrank)):
			if t!=0:
				for j in range(1,len(lelementos_xrank[t])):
					if int(lelementos_xrank[t][j][1]) > posicion-1:
						lelementos_xrank[t][j][1]=int(lelementos_xrank[t][j][1])+acumulado
					if int(lelementos_xrank[t][j][2]) > posicion-1:
						lelementos_xrank[t][j][2]=int(lelementos_xrank[t][j][2])+acumulado
					if int(lelementos_xrank[t][j][3]) > posicion-1:
						lelementos_xrank[t][j][3]=int(lelementos_xrank[t][j][3])+acumulado
				acumulado=acumulado+len(lnodos_xrank[t])

		lelementos=lelementos_xrank[0]
		for t in range(1,len(lelementos_xrank)):
			for j in range(1,len(lelementos_xrank[t])):
				lelementos.append(lelementos_xrank[t][j])

		lelementos[0][0]=len(lelementos)-1
		for t in range(1,len(lelementos)):
			lelementos[t][0]=t
		for le in lelementos:
			print le
		print "elementos totales refinados"
		print ""

		for ln in lnodos:
			print ln
		print "nodos generados"
		print " "
	comm.Disconnect()
	return tamanho_creado-tamanho_anterior
#####################################################################################################################


################################################ La conformidad despues del 4t ######################################

#Verificamos la conformidad analizando los puntos medios de las 3 aristas, si estas se encuentran como vertice al menos uno, este triangulo no es conforme
def conformidad_post4t(lelementos,lnodos, ultimo_indice):
	i=1
	while i <= int(lelementos[0][0]):
		#print i
		if comp_pto_mdo(i,pto_mdo(int(lelementos[i][1]),int(lelementos[i][2])),pto_mdo(int(lelementos[i][1]),int(lelementos[i][3])),pto_mdo(int(lelementos[i][2]),int(lelementos[i][3])),lnodos, ultimo_indice) == 1:
			print lelementos[i][0] 
			agregar_vertice_lnodos(lelementos[i][9][0],lelementos[i][9][1],lnodos)
			pto_mdo_mayor=int(lnodos[-1][0])
			crear_triangulo(pto_mdo_mayor,lelementos[i][8][1],lelementos[i][10],lelementos)
			crear_triangulo(pto_mdo_mayor,lelementos[i][8][2],lelementos[i][10],lelementos)
			lelementos.pop(i)
			lelementos[0][0]=lelementos[0][0]-1
			i=1 
		else:	
			i=i+1
	#print len(lelementos)

#####################################################################################################################

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

root=0
#Cargamos los datos necesarios para aplicar los diferentes criterios. Esto es parte del preproceso
#Recopilacion de datos
contador=0

lnodos=leer_node()
uif = ultimo_indice_fijo(lnodos)
#print uif
lelementos=leer_ele()
cal_ang(lnodos,lelementos)
cant_r=crit_ref(lelementos,45)
arista_larga(lelementos)
asig_pto_mdo(lelementos)
pto_opuesto(lelementos)

lelementos.pop(0)
lelementos=np.array(lelementos,dtype=object)

posicion=int(lnodos[0][0])+1

contador_ref = 0
data=[]
a_refinar=[]

#Es importante este tamanho, ya que con esto verificaremos la conformidad de la interseccion de la malla
tamanho_anterior=len(lelementos)
tamanho_creado=0
condicion_conformidad=0

tiempo_inicial=time()
#En el nodo maestro vamos a definir la lista a enviar por Scatter

if rank == root:
	
	#Formas la lista de triangulos a enviar por scatter
	a_refinar=np.array_split(lelementos,size)

data = comm.scatter(a_refinar, root=root)
lnodos=comm.bcast(lnodos,root=root)

data2=[None] * (len(data)+1)
data2[0]=[len(data),3]
for i in range(1,len(data2)):
	data2[i]=data[i-1]
#data=np.insert(data,0,1)

#print data2[-1]

i=1
while i < int(len(data2)):

	if data2[i][7] == 1:
		cuatro_t(data2, return_indice_ele(data2,int(data2[i][0])))
		vertices_iniciale=[None] * 3
		vertices_iniciale[0]=data2[i][1]
		vertices_iniciale[1]=data2[i][2]
		vertices_iniciale[2]=data2[i][3]
		conformidad(data2,lnodos,vertices_iniciale, uif)	
		contador=contador+1
		i=1
	else:
		i=i+1


lnodos_xrank=comm.gather(lnodos,root=root)
lelementos_xrank=comm.gather(data2,root=root)

if rank == root:

	for t in range(0,len(lnodos_xrank)):
		if t != 0:
			lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)
			for j in range(0,len(lnodos_xrank[t])):
				lnodos.append(lnodos_xrank[t][j])
		else:
			lnodos=lnodos_xrank[t]
			lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)
	lnodos[0][0]=len(lnodos)-1
	for t in range(1,len(lnodos)):
		lnodos[t][0]=t

	acumulado=len(lnodos_xrank[0])
	for t in range(0,len(lelementos_xrank)):
		if t!=0:
			for j in range(1,len(lelementos_xrank[t])):
				if int(lelementos_xrank[t][j][1]) > posicion-1:
					lelementos_xrank[t][j][1]=int(lelementos_xrank[t][j][1])+acumulado
				if int(lelementos_xrank[t][j][2]) > posicion-1:
					lelementos_xrank[t][j][2]=int(lelementos_xrank[t][j][2])+acumulado
				if int(lelementos_xrank[t][j][3]) > posicion-1:
					lelementos_xrank[t][j][3]=int(lelementos_xrank[t][j][3])+acumulado
			acumulado=acumulado+len(lnodos_xrank[t])

	lelementos=lelementos_xrank[0]
	for t in range(1,len(lelementos_xrank)):
		for j in range(1,len(lelementos_xrank[t])):
			lelementos.append(lelementos_xrank[t][j])

	lelementos[0][0]=len(lelementos)-1
	for t in range(1,len(lelementos)):
		lelementos[t][0]=t

	for le in lelementos:
		print le
	print "elementos totales refinados"
	print ""

	for ln in lnodos:
		print ln
	print "nodos generados"
	print " "
	ele_a_pc(lelementos)
	node_a_pc(lnodos)
	part_a_pc(lelementos)
"""
comm.Disconnect()
	#Llamamos a la funcion conformidad
	#conformidad_MPI(lelementos,lnodos,lelementos_xrank,lnodos_xrank)
while condicion_conformidad==0:
	condicion_conformidad=conformidad_MPI(lelementos,lnodos)

	#tiempo_final=time()
	#tiempo_ejecucion=tiempo_final-tiempo_inicial
	#ele_a_pc(lelementos)
	#node_a_pc(lnodos)
	#part_a_pc(lelementos)
"""


"""
##################################################### Realizamos la conformidad despues del 4t ###########################################

cal_ang(lnodos,lelementos)
cant_r=crit_ref(lelementos,45)
arista_larga(lelementos)
asig_pto_mdo(lelementos)
pto_opuesto(lelementos)

lelementos.pop(0)
lelementos=np.array(lelementos,dtype=object)

posicion=int(lnodos[0][0])+1

contador_ref = 0
data=[]
a_refinar=[]

#Es importante este tamanho, ya que con esto verificaremos la conformidad de la interseccion de la malla
tamanho_anterior=len(lelementos)
tamanho_creado=0
condicion_conformidad=0

tiempo_inicial=time()
#En el nodo maestro vamos a definir la lista a enviar por Scatter

if rank == root:
	
	#Formas la lista de triangulos a enviar por scatter
	a_refinar=np.array_split(lelementos,size)

data = comm.scatter(a_refinar, root=root)
lnodos=comm.bcast(lnodos,root=root)

data2=[None] * (len(data)+1)
data2[0]=[len(data),3]
for i in range(1,len(data2)):
	data2[i]=data[i-1]
#data=np.insert(data,0,1)

##################################### Aca va el conformidad ###################################

#print data2[-1]
conformidad_post4t(lelementos,lnodos, uif)

lnodos_xrank=comm.gather(lnodos,root=root)
lelementos_xrank=comm.gather(data2,root=root)

if rank == root:

	for t in range(0,len(lnodos_xrank)):
		if t != 0:
			lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)
			for j in range(0,len(lnodos_xrank[t])):
				lnodos.append(lnodos_xrank[t][j])
		else:
			lnodos=lnodos_xrank[t]
			lnodos_xrank[t]=agregar_colaNodos(lnodos_xrank[t],posicion)
	lnodos[0][0]=len(lnodos)-1
	for t in range(1,len(lnodos)):
		lnodos[t][0]=t

	acumulado=len(lnodos_xrank[0])
	for t in range(0,len(lelementos_xrank)):
		if t!=0:
			for j in range(1,len(lelementos_xrank[t])):
				if int(lelementos_xrank[t][j][1]) > posicion-1:
					lelementos_xrank[t][j][1]=int(lelementos_xrank[t][j][1])+acumulado
				if int(lelementos_xrank[t][j][2]) > posicion-1:
					lelementos_xrank[t][j][2]=int(lelementos_xrank[t][j][2])+acumulado
				if int(lelementos_xrank[t][j][3]) > posicion-1:
					lelementos_xrank[t][j][3]=int(lelementos_xrank[t][j][3])+acumulado
			acumulado=acumulado+len(lnodos_xrank[t])

	lelementos=lelementos_xrank[0]
	for t in range(1,len(lelementos_xrank)):
		for j in range(1,len(lelementos_xrank[t])):
			lelementos.append(lelementos_xrank[t][j])

	lelementos[0][0]=len(lelementos)-1
	for t in range(1,len(lelementos)):
		lelementos[t][0]=t

	for le in lelementos:
		print le
	print "elementos totales refinados"
	print ""

	for ln in lnodos:
		print ln
	print "nodos generados"
	print " "
	ele_a_pc(lelementos)
	node_a_pc(lnodos)
	part_a_pc(lelementos)
"""
