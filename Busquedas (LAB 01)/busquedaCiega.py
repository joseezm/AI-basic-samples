import turtle
import numpy as np

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
       


# 0. Crate Matrix size n
n = 100
grafo = np.zeros((n,n))

#Parents
parents = {}
# 1. Generate Random X and Y coordinates to put 1
x = np.random.randint(n)
y = np.random.randint(n)
grafo[x,y] = 1
print(x,y)

#Delete Nodes
counter = 0
while counter < 2000:
  x = np.random.randint(n)
  y = np.random.randint(n)
  if(grafo[x,y]!=1 and grafo[x,y]!=-1):
    grafo[x,y] = -1
    counter = counter + 1


# 2. We are going to start at zero zero 
while True:
    s_x,s_y = np.random.randint(n),np.random.randint(n)
    if(grafo[s_x,s_y] != 1 and grafo[s_x,s_y] != -1 and s_x != x and s_y != y):
        break
  


def DFS(start_x, start_y, visited):
  stack = []
  stack.append((start_x,start_y))
  
  while(len(stack) != 0):
    node = stack.pop()
    #Access tuple elements
    actual_x = node[0]
    actual_y = node[1]   

    if actual_x<0 or actual_y<0 or actual_x>=100 or actual_y>=100 or node in visited or grafo[actual_x,actual_y]==-1: continue

    if grafo[actual_x, actual_y] == 1: return actual_x, actual_y

    visited.append(node)
    for x in range(actual_x-1,actual_x+2):
        for y in range(actual_y-1,actual_y+2):
            stack.append((x,y))
           

def BFS(start_x, start_y, visited):
  queue = []  
  queue.append((start_x, start_y))
  parents[(start_x,start_y)] = (-1,-1)
  while(len(queue) != 0):
      node = queue.pop(0)
      actual_x = node[0]
      actual_y = node[1]
      if actual_x<0 or actual_y<0 or actual_x>=100 or actual_y>=100 or node in visited or grafo[actual_x,actual_y]==-1: continue

      if grafo[actual_x, actual_y] == 1: return actual_x, actual_y

      visited.append(node)
      for x in range(actual_x-1,actual_x+2):
        for y in range(actual_y-1,actual_y+2):
          if not((x,y) in visited):
            queue.append((x,y))
            if 0<=x<100 and 0<=y<100:
               parents[(x,y)] = (actual_x,actual_y)


def printParents(e_x, e_y):
    (x,y) = (e_x,e_y)
    while(parents[(x,y)]!=(-1,-1)):
        pen.penup()
        pen.goto((x-50)*5,(y-50)*5)
        pen.pendown()
        pen.fillcolor('blue')
        drawSquare()
        (x,y) = parents[(x,y)]
    screen.update()

                







visited=[]
printGraph()
results = BFS(s_x,s_y,visited)
print(results)
printVisited(visited)
printParents(*results)
screen.mainloop()



