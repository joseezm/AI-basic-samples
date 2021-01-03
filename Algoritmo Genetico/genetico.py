#X² -2xy + y²
#X € [0,127] 
#Y € [0,255]
#Funcion de maximización
from math import *
import random
def funcion(x,y):
    aux = x**2 - 2*x*y + y**2
    return aux

def tamBit(a):
    cont = 1
    aux = 2
    while a >= aux:
        aux = aux * 2
        cont = cont + 1
    return cont

def genAleatorio(a,b):
    aux = []
    for i in range(b):
        aux.append(random.randint(0,1))
    return aux

def binToInt(arr):
    aux = 0
    for i in range(len(arr)-1,-1,-1):
        aux = aux + arr[i]*(2**(len(arr)-i-1))
    return aux

def media(arr):
    aux = 0
    for i in arr:
        aux = aux + i
    return aux/len(arr)

def seleccion(tamx,tamy,datos):
    datosx = [[],[],[],[],[],[]]
    datosy = [[],[],[],[],[],[]]
    valorx = []
    valory = []
    func = []
    for i in range(6):
        for j in range(tamx):
            datosx[i].append(datos[i][j])
    for i in range(6):
        for j in range(tamx,tamy+tamx):
            datosy[i].append(datos[i][j])
    for i in range(6):
        valorx.append(binToInt(datosx[i]))
        valory.append(binToInt(datosy[i]))
        func.append(funcion(valorx[i],valory[i]))
    print(valorx,valory,func)
    promedio = media(func)
    for i in range(6):
        func[i] = func[i]/promedio
    for i in range(6):
        func[i] = round(func[i])
    aux = 0
    for i in func:
        aux = aux + i
    if aux < 6:
        func[func.index(max(func))] = func[func.index(max(func))] + (6-aux)
    print(func)
    newdata = []
    for i in range(6):
        for j in range(func[i]):
            newdata.append(datos[i])
    return newdata
    
def intercambio(datos,tamx,tamy):
    for i in range(round(tamx/2)):
        aux = datos[0][i] 
        datos[0][i] = datos[1][i]
        datos[1][i] = aux
        aux = datos[2][i] 
        datos[2][i] = datos[3][i]
        datos[3][i] = aux
        aux = datos[4][i] 
        datos[4][i] = datos[5][i]
        datos[5][i] = aux
    for i in range(round((tamx+tamy)/2),round((tamx+tamy)/2)+2):
        aux = datos[0][i] 
        datos[0][i] = datos[1][i]
        datos[1][i] = aux
        aux = datos[2][i] 
        datos[2][i] = datos[3][i]
        datos[3][i] = aux
        aux = datos[4][i] 
        datos[4][i] = datos[5][i]
        datos[5][i] = aux
    for i in range(tamx,tamx+2):
        aux = datos[0][i] 
        datos[0][i] = datos[1][i]
        datos[1][i] = aux
        aux = datos[2][i] 
        datos[2][i] = datos[3][i]
        datos[3][i] = aux
        aux = datos[4][i] 
        datos[4][i] = datos[5][i]
        datos[5][i] = aux
    return datos
def algGen(a,b,c,d):
    tamx = tamBit(b)
    tamy = tamBit(d)
    datos = []    
    for i in range(6):
        datos.append(genAleatorio(a,b))
    for i in range(6):
        datos[i] = datos[i] + genAleatorio(c,d)
    #Primera generacion
    datos = seleccion(tamx,tamy,datos)
    datos = intercambio(datos,tamx,tamy)
    #Segunda generacion
    datos = seleccion(tamx,tamy,datos)
    datos = intercambio(datos,tamx,tamy)
    #Tercera generacion
    datos = seleccion(tamx,tamy,datos)
    datos = intercambio(datos,tamx,tamy)
algGen(0,127,0,255)
#F = [1,1,1,1]
#print(binToInt(F))
    