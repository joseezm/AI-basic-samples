#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define KEY_ESC 27
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56

#define PI 3.1416

using namespace std;

int index;
int ganador = 24;
bool win = 0;
int nJugadas = 0;
int dificultad = 0;
char empezador = ' ';
vector<int> posiciones;




///////////////// MINIMAX y ALFABETA ////////////////////////

struct tablero {
	vector<char> m_tablero;
	tablero() {
		this->m_tablero.push_back('b'); this->m_tablero.push_back('b'); this->m_tablero.push_back('b');
		this->m_tablero.push_back('b'); this->m_tablero.push_back('b'); this->m_tablero.push_back('b');
		this->m_tablero.push_back('b'); this->m_tablero.push_back('b'); this->m_tablero.push_back('b');
	}
};



class Node {
public:
	bool hoja = 0;
	int peso;
	Node* padre;
	vector<Node*> hijos;
	tablero m_te;
	int nuevoLugar;
	int indicePosicion;

	Node() {
		peso = 0;
	}
	Node(Node* p) {
		padre = p;
	}
};
bool gameOver(tablero a) {
	//caso1
	if (a.m_tablero[0] == 'x') {
		if (a.m_tablero[1] == 'x') {
			if (a.m_tablero[2] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[0] == 'o') {
		if (a.m_tablero[1] == 'o') {
			if (a.m_tablero[2] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso2
	if (a.m_tablero[0] == 'x') {
		if (a.m_tablero[3] == 'x') {
			if (a.m_tablero[6] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[0] == 'o') {
		if (a.m_tablero[3] == 'o') {
			if (a.m_tablero[6] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso3
	if (a.m_tablero[0] == 'x') {
		if (a.m_tablero[4] == 'x') {
			if (a.m_tablero[8] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[0] == 'o') {
		if (a.m_tablero[4] == 'o') {
			if (a.m_tablero[8] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso4
	if (a.m_tablero[1] == 'x') {
		if (a.m_tablero[4] == 'x') {
			if (a.m_tablero[7] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[1] == 'o') {
		if (a.m_tablero[4] == 'o') {
			if (a.m_tablero[7] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso5
	if (a.m_tablero[2] == 'x') {
		if (a.m_tablero[4] == 'x') {
			if (a.m_tablero[6] == 'x')
			{
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[2] == 'o') {
		if (a.m_tablero[4] == 'o') {
			if (a.m_tablero[6] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso6
	if (a.m_tablero[2] == 'x') {
		if (a.m_tablero[5] == 'x') {
			if (a.m_tablero[8] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[2] == 'o') {
		if (a.m_tablero[5] == 'o') {
			if (a.m_tablero[8] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso7
	if (a.m_tablero[3] == 'x') {
		if (a.m_tablero[4] == 'x') {
			if (a.m_tablero[5] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[3] == 'o') {
		if (a.m_tablero[4] == 'o') {
			if (a.m_tablero[5] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	//caso8
	if (a.m_tablero[6] == 'x') {
		if (a.m_tablero[7] == 'x') {
			if (a.m_tablero[8] == 'x') {
				ganador = 1;
				return true;
			}
		}
	}
	if (a.m_tablero[6] == 'o') {
		if (a.m_tablero[7] == 'o') {
			if (a.m_tablero[8] == 'o') {
				ganador = 0;
				return true;
			}
		}
	}
	for (int i = 0; i < a.m_tablero.size(); i++) {
		if (a.m_tablero[i] == 'b') {
			return false;
		}
	}
	ganador = 24;
	return true;
}
void printTablero(tablero m_t) {
	cout << "imprimiendo tablero\n";
	for (int i = 0; i < 3; i++) {
		cout << m_t.m_tablero[i] << " ";
	}
	cout << endl;
	for (int i = 3; i < 6; i++) {
		cout << m_t.m_tablero[i] << " ";
	}
	cout << endl;
	for (int i = 6; i < 9; i++) {
		cout << m_t.m_tablero[i] << " ";
	}
	cout << endl;
}

class Arbol {
public:
	Node* root;
	int altura;
	tablero m_p_t;
	bool flag = 1;
	char op = 'o';
	Arbol() {
		root = new Node;
	}
	void setTablero(tablero m_o, Node* nodoo, int pro, bool flag) {
		//cout << "haciendo arbol con profundidad: " << pro << endl;
		vector<int> indices;
		m_p_t = m_o;
		int p = 0;
		if (pro > dificultad) {
			return;
		}
		for (int i = 0; i < m_o.m_tablero.size(); i++) {
			if (m_o.m_tablero[i] == 'b') {
				indices.push_back(i);
				p++;
			}
		}
		tablero m_h = m_o;
		for (int i = 0; i < indices.size(); i++) {
			if (pro % 2 == 0)
				m_h.m_tablero[indices[i]] = 'x';
			else
				m_h.m_tablero[indices[i]] = 'o';
			Node* k = new Node(nodoo);
			k->m_te = m_h;
			k->indicePosicion = indices[i];
			nodoo->hijos.push_back(k);
			m_h = m_o;
		}
		for (int i = 0; i < nodoo->hijos.size(); i++) {
			setTablero(nodoo->hijos[i]->m_te, nodoo->hijos[i], pro + 1, flag);
		}
	}
	int staticEvaluation(Node* m_n) {
		//cout << "haciendo casos\n";
		int contMe = 0, contYou = 0;
		//caso 1.1
		if (m_n->m_te.m_tablero[0] == 'x' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[1] == 'x' || m_n->m_te.m_tablero[1] == 'b') {
				if (m_n->m_te.m_tablero[2] == 'x' || m_n->m_te.m_tablero[2] == 'b')
					contMe++;
			}
		}
		//caso1.2
		if (m_n->m_te.m_tablero[0] == 'o' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[1] == 'o' || m_n->m_te.m_tablero[1] == 'b') {
				if (m_n->m_te.m_tablero[2] == 'o' || m_n->m_te.m_tablero[2] == 'b')
					contYou++;
			}
		}
		//caso 2.1
		if (m_n->m_te.m_tablero[0] == 'x' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[3] == 'x' || m_n->m_te.m_tablero[3] == 'b') {
				if (m_n->m_te.m_tablero[6] == 'x' || m_n->m_te.m_tablero[6] == 'b')
					contMe++;
			}
		}
		//caso 2.2
		if (m_n->m_te.m_tablero[0] == 'o' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[3] == 'o' || m_n->m_te.m_tablero[3] == 'b') {
				if (m_n->m_te.m_tablero[6] == 'o' || m_n->m_te.m_tablero[6] == 'b')
					contYou++;
			}
		}
		//caso 3.1
		if (m_n->m_te.m_tablero[0] == 'x' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'x' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'x' || m_n->m_te.m_tablero[8] == 'b')
					contMe++;
			}
		}
		//caso 3.2
		if (m_n->m_te.m_tablero[0] == 'o' || m_n->m_te.m_tablero[0] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'o' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'o' || m_n->m_te.m_tablero[8] == 'b')
					contYou++;
			}
		}
		//caso 4.1
		if (m_n->m_te.m_tablero[1] == 'x' || m_n->m_te.m_tablero[1] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'x' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[7] == 'x' || m_n->m_te.m_tablero[7] == 'b')
					contMe++;
			}
		}
		//caso 4.2
		if (m_n->m_te.m_tablero[1] == 'o' || m_n->m_te.m_tablero[1] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'o' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[7] == 'o' || m_n->m_te.m_tablero[7] == 'b')
					contYou++;
			}
		}
		//caso 5.1
		if (m_n->m_te.m_tablero[2] == 'x' || m_n->m_te.m_tablero[2] == 'b') {
			if (m_n->m_te.m_tablero[5] == 'x' || m_n->m_te.m_tablero[5] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'x' || m_n->m_te.m_tablero[8] == 'b')
					contMe++;
			}
		}
		//caso 5.2
		if (m_n->m_te.m_tablero[2] == 'o' || m_n->m_te.m_tablero[2] == 'b') {
			if (m_n->m_te.m_tablero[5] == 'o' || m_n->m_te.m_tablero[5] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'o' || m_n->m_te.m_tablero[8] == 'b')
					contYou++;
			}
		}
		//caso 6.1
		if (m_n->m_te.m_tablero[2] == 'x' || m_n->m_te.m_tablero[2] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'x' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[6] == 'x' || m_n->m_te.m_tablero[6] == 'b')
					contMe++;
			}
		}
		//caso 6.2
		if (m_n->m_te.m_tablero[2] == 'o' || m_n->m_te.m_tablero[2] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'o' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[6] == 'o' || m_n->m_te.m_tablero[6] == 'b')
					contYou++;
			}
		}
		//caso 7.1
		if (m_n->m_te.m_tablero[3] == 'x' || m_n->m_te.m_tablero[3] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'x' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[5] == 'x' || m_n->m_te.m_tablero[5] == 'b')
					contMe++;
			}
		}
		//caso 7.2
		if (m_n->m_te.m_tablero[3] == 'o' || m_n->m_te.m_tablero[3] == 'b') {
			if (m_n->m_te.m_tablero[4] == 'o' || m_n->m_te.m_tablero[4] == 'b') {
				if (m_n->m_te.m_tablero[5] == 'o' || m_n->m_te.m_tablero[5] == 'b')
					contYou++;
			}
		}
		//caso 8.1
		if (m_n->m_te.m_tablero[6] == 'x' || m_n->m_te.m_tablero[6] == 'b') {
			if (m_n->m_te.m_tablero[7] == 'x' || m_n->m_te.m_tablero[7] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'x' || m_n->m_te.m_tablero[8] == 'b')
					contMe++;
			}
		}
		//caso 8.2
		if (m_n->m_te.m_tablero[6] == 'o' || m_n->m_te.m_tablero[6] == 'b') {
			if (m_n->m_te.m_tablero[7] == 'o' || m_n->m_te.m_tablero[7] == 'b') {
				if (m_n->m_te.m_tablero[8] == 'o' || m_n->m_te.m_tablero[8] == 'b')
					contYou++;
			}
		}
		return contMe - contYou;
	}
	int minimax(Node* m_r, int profundidad, bool maxomin) {
		if (profundidad == 0 || gameOver(m_p_t))
			return staticEvaluation(m_r);
		if (maxomin) {
			int maxE = -999999;
			for (int i = 0; i < m_r->hijos.size() - 1; i++) {
				int eval = minimax(m_r->hijos[i], profundidad - 1, false);
				maxE = max(maxE, eval);
			}
			return maxE;
		}
		else {
			int minE = 999999;
			for (int i = 0; i < m_r->hijos.size() - 1; i++) {
				int eval = minimax(m_r->hijos[i], profundidad - 1, true);
				minE = min(minE, eval);
			}
			return minE;
		}
	}


	int alphaBeta(Node* m_r, int profundidad, int alpha, int beta, bool maxomin, int& gg) {
		//cout << "pensando\n";
		if (profundidad == 0 || gameOver(m_r->m_te)) {
			gg = m_r->indicePosicion;
			return staticEvaluation(m_r);
		}
		if (maxomin) {
			int maxE = -999999;
			for (int i = 0; i < m_r->hijos.size(); i++) {
				int eval = alphaBeta(m_r->hijos[i], profundidad - 1, alpha, beta, false, gg);
				if (maxE < eval) {
					maxE = eval;
					index = m_r->hijos[i]->indicePosicion;
				}

				alpha = max(alpha, eval);
				if (beta <= alpha) {

					break;
				}
			}
			return maxE;
		}
		else {
			int minE = 999999;
			for (int i = 0; i < m_r->hijos.size(); i++) {
				int eval = alphaBeta(m_r->hijos[i], profundidad - 1, alpha, beta, true, gg);
				minE = min(minE, eval);
				if (minE > eval) {
					minE = eval;
					index = m_r->hijos[i]->indicePosicion;
				}
				beta = min(beta, eval);
				if (beta <= alpha) {
					break;
				}
			}
			return minE;
		}
	}
};

class juego {
public:
	tablero m_t;
	Arbol m_posibilidades;
	int jugador, maquina;
	bool fin = 0;

	//el simbolo que define al jugador siempre es la x
	juego(int jInicio) { //se define quien empieza la partida y asi sucesivamente
		if (jInicio == 1) {
			empezador = 'h';
			jugador = 1; maquina = 2;
		}
		else {
			empezador = 'm';
			jugador = 2; maquina = 1;
		}
	}
	void jugada(int j) {
		m_t.m_tablero[j] = 'x';
		return;
	}

	void respuesta(int prof) {
		int n;
		//minimax
		//m_t.m_tablero[m_posibilidades.minimax(m_posibilidades.root, prof, 1)] = 'o';
		//n = m_posibilidades.minimax(m_posibilidades.root, prof, 1);
		//alphabeta
		int gg = 0;
		int xxx = m_posibilidades.alphaBeta(m_posibilidades.root, prof, -99999, +99999, 1, gg);
		m_t.m_tablero[gg] = 'o';
		cout << gg << endl;
		//n = m_posibilidades.minimax(m_posibilidades.root, prof, 1);
		/*n = m_posibilidades.alphaBeta(m_posibilidades.root, prof, -99999, +99999, 1);*/
		nJugadas++;
		posiciones.push_back(gg);
		return;
	}
	void beginGame() {

	}
};



juego* j;

///////////////// PARTE GRAFICA ////////////////////////


void dibujarTablero()
{
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3d(255, 255, 0);
	glVertex2d(-125, 400);
	glVertex2d(-125, -400);
	glVertex2d(125, 400);
	glVertex2d(125, -400);
	glVertex2d(-400, 125);
	glVertex2d(400, 125);
	glVertex2d(-400, -125);
	glVertex2d(400, -125);
	glEnd();
}

void dibujarCirculo(int x, int y) {
	glBegin(GL_LINE_LOOP);
	glColor3d(255, 255, 255);
	for (int i = 0; i <= 100; i++) {
		glVertex2f(
			x + (50 * cos(i * 2.0f * PI / 100)),
			y + (50 * sin(i * 2.0f * PI / 100))
		);
	}
	glEnd();
}

void dibujarX(int x, int y) {
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex2d(x + (-45), y + 45);
	glVertex2d(x + 45, y + (-45));
	glVertex2d(x + 45, y + 45);
	glVertex2d(x + (-45), y + (-45));
	glEnd();
}

void dibujarJugada(bool simb, int pos) {
	switch (pos) {
	case 0:
		if (simb) dibujarX(-250, 250);
		else dibujarCirculo(-250, 250);
		break;
	case 1:
		if (simb) dibujarX(0, 250);
		else dibujarCirculo(0, 250);
		break;
	case 2:
		if (simb) dibujarX(250, 250);
		else dibujarCirculo(250, 250);
		break;
	case 3:
		if (simb) dibujarX(-250, 0);
		else dibujarCirculo(-250, 0);
		break;
	case 4:
		if (simb) dibujarX(0, 0);
		else dibujarCirculo(0, 0);
		break;
	case 5:
		if (simb) dibujarX(250, 0);
		else dibujarCirculo(250, 0);
		break;
	case 6:
		if (simb) dibujarX(-250, -250);
		else dibujarCirculo(-250, -250);
		break;
	case 7:
		if (simb) dibujarX(0, -250);
		else dibujarCirculo(0, -250);
		break;
	case 8:
		if (simb) dibujarX(250, -250);
		else dibujarCirculo(250, -250);
		break;

	}
}

void dibujarGanador(int g) {
	glClear(GL_COLOR_BUFFER_BIT);
	char pc[17] = "Gano Computadora";
	char j[13] = "Gano Jugador";
	char empate[7] = "Empate";

	glRasterPos2i(-200, 0);
	if (g == 0)
		for (int i = 0; i < 17; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pc[i]);
	else if (g == 1)
		for (int i = 0; i < 13; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, j[i]);
	else
		for (int i = 0; i < 7; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, empate[i]);


}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "x: " << x << "  y: " << y << endl;
	}
}

void OnMouseMotion(int x, int y)
{
	//opcional 
	//hacer algo x,z cuando se mueve el mouse
}

void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(-500.0f, 500.0f, -500.0f, 500.0f, -1.0f, 1.0f);

	win = gameOver(j->m_t);
	if (!win) {
		dibujarTablero();

		switch (nJugadas) {
		case 1:
			dibujarJugada(1, posiciones[0]);
			break;
		case 2:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			break;
		case 3:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			break;
		case 4:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			break;
		case 5:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			dibujarJugada(1, posiciones[4]);
			break;
		case 6:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			dibujarJugada(1, posiciones[4]);
			dibujarJugada(0, posiciones[5]);
			break;
		case 7:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			dibujarJugada(1, posiciones[4]);
			dibujarJugada(0, posiciones[5]);
			dibujarJugada(1, posiciones[6]);
			break;
		case 8:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			dibujarJugada(1, posiciones[4]);
			dibujarJugada(0, posiciones[5]);
			dibujarJugada(1, posiciones[6]);
			dibujarJugada(0, posiciones[7]);
			break;
		case 9:
			dibujarJugada(1, posiciones[0]);
			dibujarJugada(0, posiciones[1]);
			dibujarJugada(1, posiciones[2]);
			dibujarJugada(0, posiciones[3]);
			dibujarJugada(1, posiciones[4]);
			dibujarJugada(0, posiciones[5]);
			dibujarJugada(1, posiciones[6]);
			dibujarJugada(0, posiciones[7]);
			dibujarJugada(1, posiciones[8]);
			break;
		default:
			break;
		}
	}
	else
		dibujarGanador(ganador);


	glutSwapBuffers();
}

void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	case KEY_0:
		j->jugada(0);
		nJugadas++;
		posiciones.push_back(0);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);
		break;
	case KEY_1:
		j->jugada(1);
		nJugadas++;
		posiciones.push_back(1);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_2:
		j->jugada(2);
		nJugadas++;
		posiciones.push_back(2);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_3:
		j->jugada(3);
		nJugadas++;
		posiciones.push_back(3);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_4:
		j->jugada(4);
		nJugadas++;
		posiciones.push_back(4);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_5:
		j->jugada(5);
		nJugadas++;
		posiciones.push_back(5);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_6:
		j->jugada(6);
		nJugadas++;
		posiciones.push_back(6);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_7:
		j->jugada(7);
		nJugadas++;
		posiciones.push_back(7);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);

		break;
	case KEY_8:
		j->jugada(8);
		nJugadas++;
		posiciones.push_back(8);
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);
		break;
	default:
		break;
	}

}

///////////////// MAIN ////////////////////////



int main(int argc, char** argv) {
	cout << "Quien empieza el juego? \n 1: empiezas tu \n 2: empieza la maquina \n";
	int n;
	cin >> n;
	cout << "Escoje la dificultad del juego\n A un mayor numero mayor dificultad.\n";
	cin >> dificultad;

	j = new juego(n);
	if (n == 2) {
		j->m_posibilidades.setTablero(j->m_t, j->m_posibilidades.root, 1, 1);
		j->respuesta(dificultad);
	}

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500); //tama�o de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("3 en RAYA "); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);



	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}