from mpi4py import MPI
import random
import math
from time import time
import numpy as np

#Definimos la funcion, para verificar que el numero aleatorio no se repita
def no_repetir_numero(numero_aleatorio, tamano_vector,lista):
	for i in range(tamano_vector):
		if numero_aleatorio == lista[i].numero_bola-1:
			return 0
	return 1		

#Creamos una clase, para definir el numero y color de la bola
class bola_numero:
	def __init__(self, numero, color):
		self.numero_bola = numero
		self.color_bola = color

#Rellenamos el vector con numero y color
def rellenar_bolas():
	lista=[0] *60
	for i in range(60):
		if i < 14:
			lista[i]=bola_numero(i+1,'amarillo')	
		elif i < 29:
			lista[i]=bola_numero(i+1,'azul')
		elif i < 44:
			lista[i]=bola_numero(i+1,'rojo')
		elif i < 60:
			lista[i]=bola_numero(i+1,'verde')		
	return lista

def rellenar_distribucion_bolas():
	lista=[0] *30
	for i in range(30):
		numero=np.random.random_integers(60)-1
		while no_repetir_numero(numero,i,lista) == 0:
			numero=np.random.random_integers(60)-1
		if numero < 14:
			lista[i]=bola_numero(numero+1,'amarillo')
		elif numero < 29:
			lista[i]=bola_numero(numero+1,'azul')
		elif numero < 44:
			lista[i]=bola_numero(numero+1,'rojo')
		elif numero < 60:
			lista[i]=bola_numero(numero+1,'verde')
	return lista

comm = MPI.COMM_WORLD

#Conocemos el numero de nodos totales
size = comm.Get_size()
rank = comm.Get_rank()

root=0
bolas=[]
distribucion_bolas=[]
if rank==root:
	#bolas=rellenar_bolas()
	#for i in range(60):
	#	print bolas[i].numero_bola,bolas[i].color_bola
	distribucion_bolas=rellenar_distribucion_bolas()
	for i in range(30):
		print distribucion_bolas[i].numero_bola,distribucion_bolas[i].color_bola, i+1
