#include <iostream>
#include <vector>

using namespace std;

struct Patron {
	double bayas = 1;
	double f1[5] = { 0 };
	double f2[5] = { 0 };
	double f3[5] = { 0 };
	double f4[5] = { 0 };
	double f5[5] = { 0 };
	double f6[5] = { 0 };
	double f7[5] = { 0 };
	Patron(double _f1[5], double _f2[5], double _f3[5], double _f4[5], double _f5[5], double _f6[5], double _f7[5]) {
		for (int i = 0; i < 5; i++) {
			f1[i] = _f1[i];
			f2[i] = _f2[i];
			f3[i] = _f3[i];
			f4[i] = _f4[i];
			f5[i] = _f5[i];
			f6[i] = _f6[i];
			f7[i] = _f7[i];
		}
	}
};

struct Neurona {
	double p1[5] = { 0 }; double p2[5] = { 0 }; double p3[5] = { 0 }; double p4[5] = { 0 };
	double p5[5] = { 0 }; double p6[5] = { 0 }; double p7[5] = { 0 };
	double pbayas = 0;
	double estadoInterno = 0;
	void calcularEstado(double bayas, double v1[5],double v2[5],double v3[5],double v4[5],double v5[5],double v6[5],double v7[5]) {
		estadoInterno = pbayas * bayas;
		for (int i = 0; i < 5; i++) {
			estadoInterno += p1[i] * v1[i];
			estadoInterno += p2[i] * v2[i];
			estadoInterno += p3[i] * v3[i];
			estadoInterno += p4[i] * v4[i];
			estadoInterno += p5[i] * v5[i];
			estadoInterno += p6[i] * v6[i];
			estadoInterno += p7[i] * v7[i];
		}
	}
	void calcularNuevosPesos(double n, double bayas,double v1[5], double v2[5], double v3[5], double v4[5], double v5[5], double v6[5], double v7[5],double deseado) {
		pbayas = pbayas + n * bayas * (deseado - estadoInterno);
		for (int i = 0; i < 5; i++) {
			p1[i] = p1[i] + n * v1[i] * (deseado - estadoInterno);
			p2[i] = p2[i] + n * v2[i] * (deseado - estadoInterno);
			p3[i] = p3[i] + n * v3[i] * (deseado - estadoInterno);
			p4[i] = p4[i] + n * v4[i] * (deseado - estadoInterno);
			p5[i] = p5[i] + n * v5[i] * (deseado - estadoInterno);
			p6[i] = p6[i] + n * v6[i] * (deseado - estadoInterno);
			p7[i] = p7[i] + n * v7[i] * (deseado - estadoInterno);
		}
	}
	double funcionActivacion(double valor) {
		if (valor > 0)
			return 1;
		else
			return 0;
	}
	void entrenar(double n, double deseado, vector<Patron> m_entradas) {
		//entrena con 1
		if (m_entradas.size() == 1) {
			bool pasa = false,pasa1 = false;
			while (!pasa) {
				if (!pasa1) {
					calcularEstado(m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7, deseado);
					}
					else {
						pasa1 = true;
					}
				}
				if (pasa1)
					pasa = true;
				else {
					pasa1 = false;
					pasa = false;
				}
			}
		}
		//entrena con 2
		else if (m_entradas.size() == 2) {
			bool pasa = false;
			bool pasa1 = false, pasa2 = false;
			while (!pasa) {
				if (!pasa1) {
					calcularEstado(m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7, deseado);
					}
					else {
						pasa1 = true;
					}
				}
				if (!pasa2) {
					calcularEstado(m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7, deseado);
					}
					else {
						pasa2 = true;
					}
				}
				if (pasa1 && pasa2) {
					pasa = true;
				}
				else {
					pasa1 = false;
					pasa2 = false;
					pasa = false;
				}
			}
		}
		//entrena con 3
		else if (m_entradas.size() == 3) {
			bool pasa = false;
			bool pasa1 = false, pasa2 = false,pasa3 = false;
			while (!pasa) {
				if (!pasa1) {
					calcularEstado(m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7, deseado);
					}
					else {
						pasa1 = true;
					}
				}
				if (!pasa2) {
					calcularEstado(m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7, deseado);
					}
					else {
						pasa2 = true;
					}
				}
				if (!pasa3) {
					calcularEstado(m_entradas[2].bayas, m_entradas[2].f1, m_entradas[2].f2, m_entradas[2].f3, m_entradas[2].f4, m_entradas[2].f5, m_entradas[2].f6, m_entradas[2].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[2].bayas, m_entradas[2].f1, m_entradas[2].f2, m_entradas[2].f3, m_entradas[2].f4, m_entradas[2].f5, m_entradas[2].f6, m_entradas[2].f7, deseado);
					}
					else {
						pasa3 = true;
					}
				}
				if (pasa1 && pasa2 && pasa3) {
					pasa = true;
				}
				else {
					pasa1 = false;
					pasa2 = false;
					pasa3 = false;
					pasa = false;
				}
			}
		}
		//entrena con 4
		else if (m_entradas.size() == 4) {
			bool pasa = false;
			bool pasa1 = false, pasa2 = false, pasa3 = false,pasa4 = false;
			while (!pasa) {
				if (!pasa1) {
					calcularEstado(m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[0].bayas, m_entradas[0].f1, m_entradas[0].f2, m_entradas[0].f3, m_entradas[0].f4, m_entradas[0].f5, m_entradas[0].f6, m_entradas[0].f7, deseado);
					}
					else {
						pasa1 = true;
					}
				}
				if (!pasa2) {
					calcularEstado(m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[1].bayas, m_entradas[1].f1, m_entradas[1].f2, m_entradas[1].f3, m_entradas[1].f4, m_entradas[1].f5, m_entradas[1].f6, m_entradas[1].f7, deseado);
					}
					else {
						pasa2 = true;
					}
				}
				if (!pasa3) {
					calcularEstado(m_entradas[2].bayas, m_entradas[2].f1, m_entradas[2].f2, m_entradas[2].f3, m_entradas[2].f4, m_entradas[2].f5, m_entradas[2].f6, m_entradas[2].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[2].bayas, m_entradas[2].f1, m_entradas[2].f2, m_entradas[2].f3, m_entradas[2].f4, m_entradas[2].f5, m_entradas[2].f6, m_entradas[2].f7, deseado);
					}
					else {
						pasa3 = true;
					}
				}
				if (!pasa4) {
					calcularEstado(m_entradas[3].bayas, m_entradas[3].f1, m_entradas[3].f2, m_entradas[3].f3, m_entradas[3].f4, m_entradas[3].f5, m_entradas[3].f6, m_entradas[3].f7);
					estadoInterno = funcionActivacion(estadoInterno);
					if (estadoInterno != deseado) {
						calcularNuevosPesos(n, m_entradas[3].bayas, m_entradas[3].f1, m_entradas[3].f2, m_entradas[3].f3, m_entradas[3].f4, m_entradas[3].f5, m_entradas[3].f6, m_entradas[3].f7, deseado);
					}
					else {
						pasa4 = true;
					}
				}
				if (pasa1 && pasa2 && pasa3 && pasa4) {
					pasa = true;
				}
				else {
					pasa1 = false;
					pasa2 = false;
					pasa3 = false;
					pasa4 = false;
					pasa = false;
				}
			}
		}		
	}
	double probar(Patron m_p) {
		double retorno = 0;
		for (int i = 0; i < 5; i++) {
			retorno += p1[i] * m_p.f1[i];
			retorno += p2[i] * m_p.f2[i];
			retorno += p3[i] * m_p.f3[i];
			retorno += p4[i] * m_p.f4[i];
			retorno += p5[i] * m_p.f5[i];
			retorno += p6[i] * m_p.f6[i];
			retorno += p7[i] * m_p.f7[i];
		}
		return funcionActivacion(retorno);
	}
	void imprimirPesos() {
		for (int i = 0; i < 5; i++) {
			cout << p1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p2[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p3[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p4[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p5[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p6[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << p7[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	//def neuronas
	Neurona a, b, c;
	//def patrones 1 patron
	double p11[5] = {0,0,1,0,0};
	double p12[5] = {0,1,1,0,0};
	double p13[5] = {1,0,1,0,0};
	double p14[5] = {0,0,1,0,0};
	double p15[5] = {0,0,1,0,0};
	double p16[5] = {0,0,1,0,0};
	double p17[5] = {1,1,1,1,1};
	//2 patron
	double p21[5] = { 0,0,1,0,0 };
	double p22[5] = { 0,1,1,0,0 };
	double p23[5] = { 1,0,1,0,0 };
	double p24[5] = { 0,0,1,0,0 };
	double p25[5] = { 0,0,1,0,0 };
	double p26[5] = { 0,0,1,0,0 };
	double p27[5] = { 0,0,1,0,0 };
	//3 patron
	double p31[5] = { 0,0,1,0,0 };
	double p32[5] = { 0,0,1,0,0 };
	double p33[5] = { 0,0,1,0,0 };
	double p34[5] = { 0,0,1,0,0 };
	double p35[5] = { 0,0,1,0,0 };
	double p36[5] = { 0,0,1,0,0 };
	double p37[5] = { 0,0,1,0,0 };
	//4 patron
	double p41[5] = { 0,0,0,0,1 };
	double p42[5] = { 0,0,0,0,1 };
	double p43[5] = { 0,0,0,0,1 };
	double p44[5] = { 0,0,0,0,1 };
	double p45[5] = { 0,0,0,0,1 };
	double p46[5] = { 0,0,0,0,1 };
	double p47[5] = { 0,0,0,0,1 };

	//5 patron los del 0
	double p51[5] = { 1,1,1,1,1};
	double p52[5] = { 1,0,0,0,1 };
	double p53[5] = { 1,0,0,0,1 };
	double p54[5] = { 1,0,0,0,1 };
	double p55[5] = { 1,0,0,0,1 };
	double p56[5] = { 1,0,0,0,1 };
	double p57[5] = { 1,1,1,1,1 };
	//6 patron
	double p61[5] = { 0,1,1,1,0 };
	double p62[5] = { 1,0,0,0,1 };
	double p63[5] = { 1,0,0,0,1 };
	double p64[5] = { 1,0,0,0,1 };
	double p65[5] = { 1,0,0,0,1 };
	double p66[5] = { 1,0,0,0,1 };
	double p67[5] = { 0,1,1,1,0 };
	//7 patron
	double p71[5] = { 0,0,0,0,0 };
	double p72[5] = { 0,1,1,1,0 };
	double p73[5] = { 0,1,0,1,0 };
	double p74[5] = { 0,1,0,1,0 };
	double p75[5] = { 0,1,0,1,0 };
	double p76[5] = { 0,1,1,1,0 };
	double p77[5] = { 0,0,0,0,0 };
	//8 patron
	double p81[5] = { 0,1,1,1,0 };
	double p82[5] = { 0,1,0,1,0 };
	double p83[5] = { 0,1,0,1,0 };
	double p84[5] = { 0,1,0,1,0 };
	double p85[5] = { 0,1,0,1,0 };
	double p86[5] = { 0,1,0,1,0 };
	double p87[5] = { 0,1,1,1,0 };
	//patrones del 2
	double p91[5] = { 0,0,1,0,0 };
	double p92[5] = { 0,1,0,1,0 };
	double p93[5] = { 1,0,0,0,1 };
	double p94[5] = { 0,0,0,1,0 };
	double p95[5] = { 0,0,1,0,0 };
	double p96[5] = { 0,1,0,0,0 };
	double p97[5] = { 1,1,1,1,1 };
	//
	double p101[5] = { 0,0,0,0,0 };
	double p102[5] = { 0,1,1,1,0 };
	double p103[5] = { 1,0,0,0,1 };
	double p104[5] = { 0,0,0,1,0 };
	double p105[5] = { 0,0,1,0,0 };
	double p106[5] = { 0,1,0,0,0 };
	double p107[5] = { 1,1,1,1,1 };
	//
	double p111[5] = { 0,0,1,0,0 };
	double p112[5] = { 0,1,0,1,0 };
	double p113[5] = { 0,0,0,1,0 };
	double p114[5] = { 0,0,1,0,0 };
	double p115[5] = { 0,1,0,0,0 };
	double p116[5] = { 0,1,1,1,0 };
	double p117[5] = { 0,0,0,0,0 };
	//
	double p121[5] = { 0,0,1,1,0 };
	double p122[5] = { 0,1,0,0,1 };
	double p123[5] = { 0,0,0,1,0 };
	double p124[5] = { 0,0,1,0,0 };
	double p125[5] = { 0,1,1,1,1 };
	double p126[5] = { 0,0,0,0,0 };
	double p127[5] = { 0,0,0,0,0 };
	//ir aprendiendo patrones 1 por 1
	//aprende p1
	Patron m_1p(p11,p12,p13,p14,p15,p16,p17);
	vector<Patron> m_patrones_aprendidos1;
	vector<Patron> m_patrones_aprendidos2;
	vector<Patron> m_patrones_aprendidos3;
	m_patrones_aprendidos1.push_back(m_1p);
	a.entrenar(0.02, 1, m_patrones_aprendidos1);
	//aprende p2
	Patron m_2p(p21, p22, p23, p24, p25, p26, p27);
	m_patrones_aprendidos1.push_back(m_2p);
	a.entrenar(0.02, 1, m_patrones_aprendidos1);
	//aprende p3
	Patron m_3p(p31, p32, p33, p34, p35, p36, p37);
	m_patrones_aprendidos1.push_back(m_3p);
	a.entrenar(0.02, 1, m_patrones_aprendidos1);
	//aprende p4
	Patron m_4p(p41, p42, p43, p44, p45, p46, p47);
	m_patrones_aprendidos1.push_back(m_4p);
	a.entrenar(0.02, 1, m_patrones_aprendidos1);
	//comienzan patrones de 0 cambian los valores deseados
	//aprende p5
	Patron m_5p(p51, p52, p53, p54, p55, p56, p57);
	m_patrones_aprendidos2.push_back(m_5p);
	b.entrenar(0.02, 1, m_patrones_aprendidos2);
	//aprende p6
	Patron m_6p(p61, p62, p63, p64, p65, p66, p67);
	m_patrones_aprendidos2.push_back(m_6p);
	b.entrenar(0.02, 1, m_patrones_aprendidos2);
	//aprende p7
	Patron m_7p(p71, p72, p73, p74, p75, p76, p77);
	m_patrones_aprendidos2.push_back(m_7p);
	b.entrenar(0.02, 1, m_patrones_aprendidos2);
	//aprende p8
	Patron m_8p(p81, p82, p83, p84, p85, p86, p87);
	m_patrones_aprendidos2.push_back(m_8p);
	b.entrenar(0.02, 1, m_patrones_aprendidos2);
	//aprende p9
	Patron m_9p(p91, p92, p93, p94, p95, p96, p97);
	m_patrones_aprendidos3.push_back(m_9p);
	c.entrenar(0.02, 1, m_patrones_aprendidos3);
	//aprende p10
	Patron m_10p(p101, p102, p103, p104, p105, p106, p107);
	m_patrones_aprendidos3.push_back(m_10p);
	c.entrenar(0.02, 1, m_patrones_aprendidos3);
	//aprende p11
	Patron m_11p(p111, p112, p113, p114, p115, p116, p117);
	m_patrones_aprendidos3.push_back(m_11p);
	c.entrenar(0.02, 1, m_patrones_aprendidos3);
	//aprende p12
	Patron m_12p(p121, p122, p123, p124, p125, p126, p127);
	m_patrones_aprendidos3.push_back(m_12p);
	c.entrenar(0.02, 1, m_patrones_aprendidos3);
	//testeo del aprendizaje
	/*cout << "////////////" << endl;
	cout << "a: " << a.probar(m_1p) << "\n";	
	cout << "////////////" << endl;
	cout << "a: " << a.probar(m_2p) << "\n";
	cout << "////////////" << endl;
	cout << "a: " << a.probar(m_3p) << "\n";
	cout << "////////////" << endl;
	cout << "a: " << a.probar(m_4p) << "\n";	
	cout << "000000000000" << endl;
	cout << "b: " << b.probar(m_5p) << "\n";
	cout << "////////////" << endl;
	cout << "b: " << b.probar(m_6p) << "\n";
	cout << "////////////" << endl;
	cout << "b: " << b.probar(m_7p) << "\n";
	cout << "////////////" << endl;
	cout << "b: " << b.probar(m_8p) << "\n";
	cout << "222222222222" << endl;
	cout << "c: " << c.probar(m_9p) << "\n";
	cout << "////////////" << endl;
	cout << "c: " << c.probar(m_10p) << "\n";
	cout << "////////////" << endl;
	cout << "c: " << c.probar(m_11p) << "\n";
	cout << "////////////" << endl;
	cout << "c: " << c.probar(m_12p) << "\n";*/

	cout << "TESTEO DE PATRONES\n";
	cout << "0: Probar ceros\n";
	cout << "1: Probar unos\n";
	cout << "2: Probar dos\n";
	int var;
	cin >> var;
	if (var == 1) {
		//NEURONA 1
		cout << "Probaremos un patron,inserte numeros: " << endl;
		double pp1[5] = { 0 };
		double pp2[5] = { 0 };
		double pp3[5] = { 0 };
		double pp4[5] = { 0 };
		double pp5[5] = { 0 };
		double pp6[5] = { 0 };
		double pp7[5] = { 0 };
		cin >> pp1[0] >> pp1[1] >> pp1[2] >> pp1[3] >> pp1[4];
		cin >> pp2[0] >> pp2[1] >> pp2[2] >> pp2[3] >> pp2[4];
		cin >> pp3[0] >> pp3[1] >> pp3[2] >> pp3[3] >> pp3[4];
		cin >> pp4[0] >> pp4[1] >> pp4[2] >> pp4[3] >> pp4[4];
		cin >> pp5[0] >> pp5[1] >> pp5[2] >> pp5[3] >> pp5[4];
		cin >> pp6[0] >> pp6[1] >> pp6[2] >> pp6[3] >> pp6[4];
		cin >> pp7[0] >> pp7[1] >> pp7[2] >> pp7[3] >> pp7[4];
		Patron m_patron(pp1, pp2, pp3, pp4, pp5, pp6, pp7);
		cout << "El patron presentado: \n";
		for (int i = 0; i < 5; i++) {
			cout << pp1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp2[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp3[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp4[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp5[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp6[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp7[i] << " ";
		}
		cout << endl;
		if (a.probar(m_patron)) {
			cout << "Es un 1" << endl;
		}
		else {
			cout << "No es un 1" << endl;
		}
	}
	else if(var == 0){
		//NEURONA 2
		cout << "Probaremos un patron,inserte numeros: " << endl;
		double pp1[5] = { 0 };
		double pp2[5] = { 0 };
		double pp3[5] = { 0 };
		double pp4[5] = { 0 };
		double pp5[5] = { 0 };
		double pp6[5] = { 0 };
		double pp7[5] = { 0 };
		cin >> pp1[0] >> pp1[1] >> pp1[2] >> pp1[3] >> pp1[4];
		cin >> pp2[0] >> pp2[1] >> pp2[2] >> pp2[3] >> pp2[4];
		cin >> pp3[0] >> pp3[1] >> pp3[2] >> pp3[3] >> pp3[4];
		cin >> pp4[0] >> pp4[1] >> pp4[2] >> pp4[3] >> pp4[4];
		cin >> pp5[0] >> pp5[1] >> pp5[2] >> pp5[3] >> pp5[4];
		cin >> pp6[0] >> pp6[1] >> pp6[2] >> pp6[3] >> pp6[4];
		cin >> pp7[0] >> pp7[1] >> pp7[2] >> pp7[3] >> pp7[4];
		Patron m_patron(pp1, pp2, pp3, pp4, pp5, pp6, pp7);
		cout << "El patron presentado: \n";
		for (int i = 0; i < 5; i++) {
			cout << pp1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp2[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp3[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp4[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp5[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp6[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp7[i] << " ";
		}
		cout << endl;
		if (b.probar(m_patron)) {
			cout << "Es un 0" << endl;
		}
		else {
			cout << "No es un 0" << endl;
		}
	}
	else if (var == 2) {
		//NEURONA 3
		cout << "Probaremos un patron,inserte numeros: " << endl;
		double pp1[5] = { 0 };
		double pp2[5] = { 0 };
		double pp3[5] = { 0 };
		double pp4[5] = { 0 };
		double pp5[5] = { 0 };
		double pp6[5] = { 0 };
		double pp7[5] = { 0 };
		cin >> pp1[0] >> pp1[1] >> pp1[2] >> pp1[3] >> pp1[4];
		cin >> pp2[0] >> pp2[1] >> pp2[2] >> pp2[3] >> pp2[4];
		cin >> pp3[0] >> pp3[1] >> pp3[2] >> pp3[3] >> pp3[4];
		cin >> pp4[0] >> pp4[1] >> pp4[2] >> pp4[3] >> pp4[4];
		cin >> pp5[0] >> pp5[1] >> pp5[2] >> pp5[3] >> pp5[4];
		cin >> pp6[0] >> pp6[1] >> pp6[2] >> pp6[3] >> pp6[4];
		cin >> pp7[0] >> pp7[1] >> pp7[2] >> pp7[3] >> pp7[4];
		Patron m_patron(pp1, pp2, pp3, pp4, pp5, pp6, pp7);
		cout << "El patron presentado: \n";
		for (int i = 0; i < 5; i++) {
			cout << pp1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp2[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp3[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp4[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp5[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp6[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << pp7[i] << " ";
		}
		cout << endl;
		if (c.probar(m_patron)) {
			cout << "Es un 2" << endl;
		}
		else {
			cout << "No es un 2" << endl;
		}
	}
	else {
	cout << "No aprendi ese numero :(\n";
	}
	return 0;
}