"""Programa de Python que resuelve el 
problema del agente viajero, utilizando
algoritmos genéticos"""

from math import sqrt
from math import factorial

from random import randint
from random import random

from itertools import islice
from itertools import permutations

import sys

from turtle import Screen, Turtle

from time import sleep


distancias = {}

def generarCiudades(numCdd):
    ciudades = []
    i = 0
    while i < numCdd:
        nuevo = Ciudad(i, randint(-250,251), randint(-250,251))
        if nuevo in ciudades:
            continue
        else:
            i += 1
            ciudades.append(nuevo)

    return ciudades

#Parser del archivo
def leerArchivo(filename):
    file = open(filename, "r")
    datos = file.readlines()
    file.close()
    ciudades = []
    for i, coord in enumerate(datos):
        auxCoord = coord.split()
        ciudades.append( Ciudad(i, float(auxCoord[0]), float(auxCoord[1])) )
    return ciudades


#Clase Ciudad
#Tendra un identificador único 
#y su posición X,Y en el plano
class Ciudad:
    #Constructor de la Clase Ciudad
    def __init__(self, id, posX, posY):
        self.__id = id
        self.__X = posX
        self.__Y = posY

    #Conversión a string de la clase Ciudad
    def __str__(self):
        s = "Ciudad %d  PosX: %f PosY: %f" % (self.__id, self.__X, self.__Y)
        return s
    
    #Destructor de la clase
    def __del__(self):
        del self.__id
        del self.__X
        del self.__Y

    #Clases para obtener los valores de la clase
    def getId(self):
        return self.__id
    
    def getX(self):
        return self.__X

    def getY(self):
        return self.__Y


class Individuo:
    def __init__(self, ciudades = []):
        self.__ciudades = list(ciudades)

    def copy(self):
        return Individuo(self.__ciudades)
    
    def __del__(self):
        while self.__ciudades:
            aux = self.__ciudades.pop()
            del aux
        
    def getCiudades(self):
        return self.__ciudades

    def __str__(self):
        ruta = "["
        for ciudad in self.__ciudades:
            ruta += " %s," % (ciudad.getId())
        ruta += " %s]" % (self.getCiudades()[0].getId())
        return ruta
    
    def distancia(self, ciudad1, ciudad2):
        a, b = (ciudad1, ciudad2) if ciudad1.getId() < ciudad2.getId() else (ciudad2, ciudad1)
        camino = "%d-%d" % (a.getId(), b.getId())
        if camino in distancias:
            dist = distancias[camino]
        else:
            x = b.getX() - a.getX()
            y = b.getY() - a.getY()
            dist = sqrt(x**2 + y**2)
            distancias[camino] = dist
        return dist
    
    def fitness(self):
        fit = 0
        source = self.getCiudades()
        dest = list(source)
        dest.append(dest.pop(0))
        for a,b in zip(source, dest):
            fit += self.distancia(a,b)
        return fit

    def __lt__(self, other):
        return self.fitness() < other.fitness()
    
    def mutar(self):
        cds = self.getCiudades()
        m = len(cds)/2
        ini = randint(0,m)
        fin = randint(m, m*2)
        a, b, c = cds[0:ini], cds[ini:fin], cds[fin:]
        b.reverse()
        del self.__ciudades
        self.__ciudades = a + b + c
        del a
        del b
        del c

    def cruzar(self, other):
        padre1, padre2 = self.getCiudades(), other.getCiudades()
        hijo1, hijo2 = list(padre1), list(padre2)
        ciclo = [0]
        i = 0
        found = False
        while not found:
            cdd = padre2[i]
            i = padre1.index(cdd)
            ciclo.append(i)
            found = padre1[0] is padre2[i]
        
        for i in ciclo:
            hijo1[i], hijo2[i] = hijo2[i], hijo1[i]
        return Individuo(hijo1), Individuo(hijo2)



def mutarPob(poblacion, prob):
    for pob in poblacion:
        if prob > random():
            pob.mutar()

def cruzarPob(poblacion, prob):
    padres = list(poblacion)
    hijos = list()

    if len(padres) % 2:
        padres.append(padres[randint(0,len(padres))])
    
    while padres:
        a = padres.pop(randint(0, len(padres)-1)) 
        b = padres.pop(randint(0, len(padres)-1))
        if prob > random():
            hijos.extend( a.cruzar(b) )
    return hijos

def torneo(poblacion, tamMuestra):
    convocados = list()
    for k in (1,2):
        candidatos = list(poblacion)
        if len(candidatos) % 2:
            candidatos.append(candidatos[randint(0, len(candidatos))])
        while(candidatos):
            a = candidatos.pop(randint(0, len(candidatos)-1))
            b = candidatos.pop(randint(0, len(candidatos)-1))
            ganador = a if a < b else b
            convocados.append(ganador)
    
    convocados.sort()
    return convocados[:tamMuestra]


def generarPoblacion(ciudades, poblacion):
    generacion0 = list()
    dedoDeDios = permutations(ciudades)
    print("permutaciones hechas")
    fin = randint(poblacion, poblacion**2)
    print("Fin calculado")
    inicio = int(fin - poblacion)

    seleccionados = list(islice(dedoDeDios, inicio, fin))
    print("Seleccion poblacion inicial hecha")

    for indiv in seleccionados:
        k = list(indiv)
        generacion0.append(Individuo(k))

    mutarPob(generacion0, 1.0)

    return generacion0


def geneticoTSP(ciudades, TamPob, probCruz, probMut, nIt):
    poblacion = generarPoblacion(ciudades, TamPob)
    seleccion = list()
    poblacion.sort()
    convocado = poblacion[0]
    seleccion.append(convocado.copy())

    nuevosConvocados = torneo(poblacion, TamPob)
    listo = False
    i = 1
    while not listo and i < nIt:
        print("Generacion ", i)
      
        i+=1
        hijosConvocados = cruzarPob(nuevosConvocados, TamPob)
    
        nuevosConvocados.extend(hijosConvocados)
        mutarPob(nuevosConvocados, probMut)
        
        nuevosConvocados = torneo(nuevosConvocados, TamPob)
     
        nuevosConvocados.sort()

        seleccion.append(nuevosConvocados[0].copy())

        if(len(seleccion)>1):
            guardar = list(seleccion)
            guardar.sort()
            n = guardar.count(guardar[0])
            if(len(seleccion) >= 10 and n>len(guardar)/2):
                listo = True
    seleccion.sort()
    return seleccion

def guardarCoord(optimo, archivo):
    file = open(archivo, "w")
    contenido = ""
    for ciudad in optimo.getCiudades():
        contenido += "%f %f\n" % (ciudad.getX(), ciudad.getY())
    file.write(contenido)
    file.close()



def graficar(poblacion):
    pantalla = Screen()
    tortuga = Turtle()
    pantalla.setup(600,600)
    tortuga.penup()
    pantalla.colormode(1)
    for i in range(0, len(poblacion),20):
        pantalla.tracer(0)
        ciudades = poblacion[i].getCiudades()    
        tortuga.pencolor((random(), random(), random()))
        for cdd in ciudades:
            x = cdd.getX()
            y = cdd.getY()
            tortuga.goto(x,y)
            tortuga.pendown()
            tortuga.dot(5)
        tortuga.goto(ciudades[0].getX(), ciudades[0].getY())
        tortuga.penup()    
        pantalla.update()
        sleep(.500)

    ciudades = poblacion[0].getCiudades()
    tortuga.pensize(2)
    tortuga.color("black")
    tortuga.pendown()
    for cdd in ciudades:
        x = cdd.getX()
        y = cdd.getY()
        tortuga.goto(x,y)
        tortuga.pendown()
        tortuga.color("black")
        tortuga.dot(5)
        tortuga.color("black")
    pantalla.update()
    sleep(.500)
   
    
    pantalla.exitonclick()


        

def main():
    #ciudades = leerArchivo("cities.txt")
    ciudades = generarCiudades(50)
    TamPob = 100
    ProbCruz = 0.9
    ProbMut = 0.5
    gen = 250
    seleccion = geneticoTSP(ciudades, TamPob, ProbCruz, ProbMut, gen)
    capitan = seleccion[0]
    print (capitan,"--recorriendo una distancia de: ", capitan.fitness())
    guardarCoord(capitan, "recorrido.txt")
    graficar(seleccion)


if __name__ == "__main__":
    main()

