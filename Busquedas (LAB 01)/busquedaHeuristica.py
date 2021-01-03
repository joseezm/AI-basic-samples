import turtle
import numpy as np
import math

#Global drawers
screen = turtle.Screen()
pen = turtle.Turtle()
pen.ht()

def drawSquare():
    pen.begin_fill()
    for n in range(4):
        pen.forward(5)
        pen.right(90)
    pen.end_fill()

#print Functions
def printGraph():
    #Graficate the graph
    #screen.setup(600,600)
    #Begin drawing
    screen.tracer(0,0) #turns off animation
    for i in range(100):
        for j in range(100):
            pen.penup()
            pen.goto((i-50)*5,(j-50)*5)
            pen.pendown()
            if(grafo[i,j]==0): pen.fillcolor('white')
            elif(grafo[i,j]==1): pen.fillcolor('red')
            elif(grafo[i,j]==-1): pen.fillcolor('black')
            drawSquare()


            
                
    screen.update()
   
def printVisited(visited):
    screen.tracer(500,0) #turns off animation
    start = visited[0]
    s_i = start[0]
    s_j = start[1]
    pen.penup()
    pen.goto((s_i-50)*5,(s_j-50)*5)
    pen.pendown()
    pen.fillcolor('yellow')
    drawSquare()
    visited.pop(0)
    for node in visited:
        i = node[0]
        j = node[1]
        pen.penup()
        pen.goto((i-50)*5,(j-50)*5)
        pen.pendown()
        pen.fillcolor('green')
        drawSquare()

def printPath(path):
    for node in path:
        i = node[0]
        j = node[1]
        pen.penup()
        pen.goto((i-50)*5,(j-50)*5)
        pen.pendown()
        pen.fillcolor('blue')
        drawSquare()
    screen.update()
       


# 0. Crate Matrix size n
n = 100
grafo = np.zeros((n,n))

# 1. Generate Random X and Y coordinates to put 1
x = np.random.randint(n)
y = np.random.randint(n)
grafo[x,y] = 1
print(x,y)

#Delete Nodes
counter = 0
while counter < 2000:
  a = np.random.randint(n)
  b = np.random.randint(n)
  if(grafo[a,b]!=1 and grafo[a,b]!=-1):
    grafo[a,b] = -1
    counter = counter + 1

s_x = 0
s_y = 0
while True:
    s_x = np.random.randint(n)
    s_y = np.random.randint(n)
    if(grafo[s_x,s_y] != 1 or grafo[s_x,s_y] != -1):
        break

print(s_x,s_y)

def EuclidDis(x_0,y_0,x_1,y_1):
    return math.sqrt(((x_1-x_0)**2) + ((y_1-y_0)**2))

def GreedySearch(start_x, start_y, end_x, end_y, visited, path):
    actual_x = start_x
    actual_y = start_y
    visited.append((actual_x, actual_y))
    path.append((actual_x,actual_y))
    while(grafo[actual_x,actual_y]!=1):
        next_x = 10000
        next_y = 10000
        for i in range(actual_x-1,actual_x+2):
            for j in range(actual_y-1,actual_y+2):
                if i<0 or j<0 or i>=100 or j>=100 or (i,j) in visited or grafo[i,j] == -1:
                    continue
                if(EuclidDis(i,j,end_x,end_y) < EuclidDis(next_x,next_y,end_x,end_y)):
                    next_x = i
                    next_y = j
                visited.append((i,j))
                actual_x = next_x
                actual_y = next_y
                path.append((actual_x,actual_y))
            

visited = []
path =[]
printGraph()
GreedySearch(s_x,s_y,x,y,visited,path)
printVisited(visited)
printPath(path)
screen.mainloop()

