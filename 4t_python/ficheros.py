import numpy as np
import math as mt

#Calculamos distancia ingresando 2 vertices casteados en enteros y la lista lnodos
def cal_dist(v1,v2,lnodos):
	dist=mt.sqrt(((float(lnodos[v1][1])-float(lnodos[v2][1]))*(float(lnodos[v1][1])-float(lnodos[v2][1])))+((float(lnodos[v1][2])-float(lnodos[v2][2]))*(float(lnodos[v1][2])-float(lnodos[v2][2]))))
	return dist
#Calculamos los angulos con arcoseno ingresando 3 distancias
def angulos(a,b, c):
	lista= [None] * 3
	lista[0]=(mt.acos((c*c-a*a-b*b)/(-2*a*b)))*180/3.1415
	lista[1]=(mt.acos((a*a-b*b-c*c)/(-2*b*c)))*180/3.1415
	lista[2]=(mt.acos((b*b-a*a-c*c)/(-2*a*c)))*180/3.1415
	return lista

#Genera los 3 angulos a todos los triangulos de toda la malla y se los agrega a la lista lelementos
def cal_ang(lnodos,lelementos):
	lista=[]
	for i in range(1,len(lelementos)):
		lista=angulos(cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos),cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos),cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos))
		lelementos[i].append(lista[0])
		lelementos[i].append(lista[1])
		lelementos[i].append(lista[2])

#Criterio de refinamiento, si algun angulo del un triangulo es menor al angulo critico se le asigna un 1 de refinar en contraparte 0 de no refinar
def crit_ref(lelementos, crit_ang):
	cant_ref=0
	for i in range(1,len(lelementos)):
		if lelementos[i][4] < crit_ang or lelementos[i][5] < crit_ang or lelementos[i][6] < crit_ang:
			cant_ref=cant_ref+1
			lelementos[i].append(1)
		else:
			lelementos[i].append(0)
	return cant_ref				

#En esta funcion determinamos las distancias mayores y asignaermos los vertices a esa distancia mayor
def arista_larga(lelementos):
	for i in range(1,len(lelementos)):
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

#Calcula el punto medio			
def pto_mdo(v1, v2, lnodos):
	lista=[None] * 2
	lista[0]=(float(lnodos[v1][1])+float(lnodos[v2][1]))/2
	lista[1]=(float(lnodos[v1][2])+float(lnodos[v2][2]))/2
	return lista

#Se le sacara punto medio a todos los triangulos, pero se analizara despues si es necesario sacar punto medio a la arista mayor de todos los T
def asig_pto_mdo(lelementos):
	lista=[None] * 2
	for i in range(1,len(lelementos)):
		lista=pto_mdo(int(lelementos[i][8][1]),int(lelementos[i][8][2]),lnodos)
		lelementos[i].append(lista)

#Lee el fichero .node y lo asigna a la lista lnodos
lineas = open("mesh.node").readlines()
lnodos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]

#Lee el fichero .ele y lo asigna a la lista lelementos
lineas = open("mesh.ele").readlines()
lelementos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]

#lelementos[1].append(5)

#ele(lelementos)

"""print cal_dist(1,2,lnodos)
lista=[]

lista=angulos(0.999668445,1.4186599311,1.0469407815)

print lista
"""
cal_ang(lnodos,lelementos)
#print lelementos

cant_r=crit_ref(lelementos,30)
print cant_r

arista_larga(lelementos)

asig_pto_mdo(lelementos)
#print lelementos[1][8][2], lelementos[1][8][1]
for elem in lelementos: # ciclo que imprime la lista de todos los triangulos
	#print elem[0:4] #imprimer solo el indice de triangulo y sus 3 vertices
	print elem # imprime el triangulo y todas sus variables asociadas
##print lista
#print (lelementos[14][2])*2