#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef struct stArco *adyunto;

typedef struct stNodo{
	char nombre;
	stNodo *siguiente;
	stArco *adyunto;
}nodo;

typedef struct stArco{
	int peso;
	stNodo *destino;
	stArco *siguiente;
}arco;

nodo *crearNodo(char x){
	nodo *p;
	
	p = (nodo*)malloc(sizeof(nodo));
	if(p != NULL){
		p -> nombre = x;
		p -> siguiente = NULL;
		p -> adyunto = NULL;
	}else{
		printf("No se pudo reservar memoria\n");
	}
	
	return p;
}

arco *crearArco(int x){
	arco* p;
	
	p = (arco*)malloc(sizeof(arco));
	if(p != NULL){
		p -> peso = x;
		p -> siguiente = NULL;
		p -> destino = NULL;
	}else{
		printf("No se pudo reservar memoria\n");
	}
	
	return p;
}

nodo *ultimoNodo(nodo *cabeza){
	nodo *u;
	
	if(cabeza -> siguiente != NULL){
		u = ultimoNodo(cabeza -> siguiente);
	}else{
		u = cabeza;
	}
	
	return u;
}

void insertarNodo(nodo **cabeza, char x){
	nodo *p, *i;
	
	p = crearNodo(x);
	if(*cabeza == NULL){
		*cabeza = p;
	}else{
		i = ultimoNodo(*cabeza);
		i -> siguiente = p;
	}
}

nodo *buscarNodo(nodo *cabeza, char x){
	nodo *b;
	
	if(cabeza == NULL){
		b = NULL;
	}else{
		if(cabeza -> nombre == x){
			b = cabeza;
		}else{
			b = buscarNodo(cabeza -> siguiente, x);
		}
		
	}
	return b;
}

arco *ultimoArco(arco *arista){
	arco *u;
	
	if(arista -> siguiente != NULL){
		u = ultimoArco(arista -> siguiente);
	}else{
		u = arista;
	}
	
	return u;
}

void insertarArco(nodo **cabeza, int x, char y, char z){
	nodo *a, *b;
	arco *d, *j;
	
	a = buscarNodo(*cabeza, y);
	b = buscarNodo(*cabeza, z);
	if(a != NULL && b != NULL){
		d = crearArco(x);
		if(a -> adyunto == NULL){
			a -> adyunto = d;
			d -> destino = b;
		}else{
			j = ultimoArco(a -> adyunto);
			j -> siguiente = d;
			d -> destino = b; 
		}
	}
}

void mostrarArco(arco *arista){
	
	if(arista == NULL){
		return;
	}else{
		printf("[ %d ]-> ", arista -> peso);
		mostrarArco(arista -> siguiente);
	}
}

void mostrar(nodo *cabeza){
	
	if(cabeza == NULL){
		printf("[ NULL ]\n");
	}else{
		printf("[ %c ]-> ",cabeza -> nombre);
		mostrarArco(cabeza -> adyunto);
		printf("\n");
		mostrar(cabeza -> siguiente);
	}
}

arco *buscarArco(arco *arista, int p){
	arco *b;
	
	if(arista != NULL){
		if(p == arista -> peso){
			b = arista;
		}else{
			b = buscarArco(arista -> siguiente, p);
		}
	}else{
		b = NULL;
	}
	
	return b;
}

arco *anteriorArco(arco *arista, arco *e){
	arco *a;
	
	if(e != NULL){
		if(arista != NULL){
			if(arista -> siguiente == e){
				a = arista;
			}else{
				a = anteriorArco(arista -> siguiente, e);
			}
		}else{
			a = NULL;
		}
	}else{
		a = NULL;
	}
	
	return a;
}

void eliminarArco(nodo **cabeza, int x, char y){
	arco *e;
	arco *a;
	nodo *j;
	
	if(cabeza != NULL){
		j = buscarNodo(*cabeza, y);
		if(j != NULL){
			e = buscarArco(j -> adyunto, x);
			if(e != NULL){
				if(e == j -> adyunto){
					j -> adyunto = (j -> adyunto) -> siguiente;
				}else{
					a = anteriorArco(j -> adyunto, e);
					a -> siguiente = e -> siguiente;
				}
				free(e);
				printf("Arco %d eliminado exitosamente\n",x);
			}else{
				printf("Nodo %c con Arco %d no se encuentra en la lista\n", y, x);
			}
		}else{
			printf("Lista vacia, no se puede eliminar el Arco %d\n",x);
		}
	}else{
		printf("El grafo esta vacio\n");
	}
	
	
}

void mostrarArcoX(nodo *a, arco *arista){
	
	if(arista == NULL || a == NULL){
		return;
	}else{
		printf("\n[ %c%c ]-[ %d ]", a -> nombre, (arista -> destino) -> nombre, arista -> peso);
		mostrarArcoX(a, arista -> siguiente);
	}
} 

void mostrarX(nodo *cabeza, char x){
	
	if(cabeza == NULL){
		return;
	}else{
		if(cabeza -> nombre == x){
			printf("Conecciones del Nodo %c:",cabeza -> nombre);
			mostrarArcoX(cabeza, cabeza -> adyunto);
		}else{
			mostrarX(cabeza -> siguiente, x);
		}
	}
}

arco *buscarArcoX(arco *arista, nodo *x){
	arco *b;
	
	if(arista == NULL || x == NULL){
		b = NULL;
	}else{
		if(arista -> destino == x){
			b = arista;
		}else{
			b = buscarArcoX(arista -> siguiente, x);
		}
	}
	
	return b;
}

void eliminarArcoX(nodo **cabeza, char x, char y){
	arco *e;
	arco *a;
	nodo *j;
	nodo *k;
	
	if(*cabeza != NULL){
		j = buscarNodo(*cabeza, x);
		k = buscarNodo(*cabeza, y);
		if(j != NULL && k != NULL){
			e = buscarArcoX(j -> adyunto, k);
			if(e != NULL){
				if(e == j -> adyunto){
					j -> adyunto = e -> siguiente; 
				}else{
					a = anteriorArco(j -> adyunto, e);
					a -> siguiente = e -> siguiente;
				}
				free(e);
				printf("Arco %c%c eliminado exitosamente\n", x, y);
			}else{
				printf("No existe el Arco %c%c\n",x, y);
			}
		}else{
			printf("No existe al menos uno de los nodos\n");
		}
	}else{
		printf("El grafo esta vacio\n");
	}	
	
	
}

nodo *anteriorNodo(nodo *cabeza, nodo *b){
	nodo *a;
	
	if(cabeza != NULL){
		if(cabeza -> siguiente == b){
			a = cabeza;
		}else{
			a = anteriorNodo(cabeza -> siguiente, b);
		}
	}
	
	return a;
}

void eliminarNodo(nodo **cabeza, char x){
	nodo *e;
	nodo *a;
	
	if(*cabeza != NULL){
		e = buscarNodo(*cabeza, x);
		if(e != NULL){
			if(e == *cabeza){
				*cabeza = (*cabeza) -> siguiente;
			}else{
				a = anteriorNodo(*cabeza, e);
				a -> siguiente = e -> siguiente;
			}
			free(e);
			printf("\nNodo %c eliminado exitosamente\n",x);
		}else{
			printf("\nNodo %c no se encuentra en la lista\n",x);
		}
	}else{
		printf("Grafo vacio, no se puede eliminar el Nodo %c\n",x);
	}
}

int gradoSalida(arco *arista){
	int g;
	
	if(arista == NULL){
		g = 0;
	}else{
		g = 1 + gradoSalida(arista -> siguiente);
	}
	
	return g;
}

int sumaCamino(arco *arista, nodo *r){
	int s;
	
	if(arista == NULL || r == NULL){
		s = 0;
	}else{
		if(arista -> destino == r){
			s = 1 + sumaCamino(arista -> siguiente, r);
		}else{
			s = sumaCamino(arista -> siguiente, r);
		}
	}
	
	return s;
}

int gradoEntrada(nodo *cabeza, nodo *r){
	int g;
	
	if(cabeza == NULL || r == NULL){
		g = 0;
	}else{
		g = sumaCamino(cabeza -> adyunto, r) + gradoEntrada(cabeza -> siguiente, r);
	}
	
	return g;
}

int grado(nodo *cabeza, nodo *r){
	int g;
	
	if(cabeza == NULL || r == NULL){
		g = 0;
	}else{
		g = gradoEntrada(cabeza, r) + gradoSalida(r -> adyunto);
	}
	
	return g;
}

int salidaMismo(arco *arista, nodo *a){
	int s;
	
	if(arista == NULL || a == NULL){
		s = 0;
	}else{
		if(arista -> destino == a){
			s = 1 + salidaMismo(arista -> siguiente, a);
		}else{
			s = salidaMismo(arista -> siguiente, a);
		}
	}
	
	return s;
}

int nodosMismo(nodo *cabeza){
	int m;
	
	if(cabeza == NULL){
		m = 0;
	}else{
		m = salidaMismo(cabeza -> adyunto, cabeza) + nodosMismo(cabeza -> siguiente);
	}
	
	return m;
}

bool existeArista(arco *arista, nodo *b){
	bool e;
	
	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino == b){
			e = true;
		}else{
			e = existeArista(arista -> siguiente, b);
		}
	}
	
	return e;
}

bool existeCamino(arco *arista, nodo *b){
	bool e;
	
	if(arista == NULL || b == NULL){
		e = false;
	}else{
		if(arista -> destino != NULL){
			if(arista -> destino == b){
				e = true;
			}else{
				e = existeCamino((arista -> destino) -> adyunto, b);
			}
		}else{
			e = false;
		}
	}
	
	return e;
}

nodo* nodoCamino(arco *arista, nodo *b){
	nodo *n, j;
	
	if(arista == NULL || b == NULL){
		n = NULL;
	}else{
		if(existeCamino(arista, b)){
			n = arista -> destino;
		}else{
			n = nodoCamino(arista -> siguiente, b);
		}
	}
	
	return n;
}

void mostrarCaminoXY(nodo *a, nodo *b, arco *arista){
	
	if(a == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("- > [ %c ]", (arista -> destino) -> nombre);
			mostrarCaminoXY(nodoCamino(arista, b), b, nodoCamino(arista, b) -> adyunto);
		}
	}
}

void mostrarCaminos(nodo *a, nodo *b, arco *arista){
	bool e;
	
	if(a == NULL || b == NULL || arista == NULL){
		return;
	}else{
		if(existeCamino(arista, b)){
			printf("[ %c ] ", a -> nombre);
			mostrarCaminoXY(a, b, arista);
			printf("\n");
			mostrarCaminos(a, b, arista -> siguiente);
		}else{
			mostrarCaminos(a, b, arista -> siguiente);
		}
	}
}

int numeroCaminos(arco *arista, nodo *b){
	int n;
	
	if(arista == NULL || b == NULL){
		n = 0;
	}else{
		if(existeCamino(arista, b)){
			n = 1 + numeroCaminos(arista -> siguiente, b);
		}else{
			n = numeroCaminos(arista -> siguiente, b);
		}
	}
	
	return n;
}

int sumaPesosC(arco *arista, nodo *b){
	int s;
	
	if(arista == NULL || b == NULL ){
		s = 0;
	}else{
		if(existeCamino(arista, b)){
			s = arista -> peso + sumaPesosC((nodoCamino(arista, b)) -> adyunto, b); 
		}else{
			s = 0;
		}
	}
	
	return s;
}

int caminoMenor(arco *arista, nodo *b){
	int c, x;
	
	if(b == NULL || arista == NULL){
		c = 0;
		return c;
	}else{
		if(existeCamino(arista, b)){
			c = sumaPesosC(arista, b);
			x = sumaPesosC(arista -> siguiente, b);
			if(x > c){
				return c;
			}else{
				return x;
			}
		}else{
			x = sumaPesosC(arista -> siguiente, b);
			return x;
		}
	}
}

void mostrarCamino(nodo *a, nodo *b, arco *arista){
	
	if(a == NULL || b == NULL){
		return;
	}else{
		printf("[ %c ]", a -> nombre);
		mostrarCaminoXY(a, b, arista);
	}
}

void caminoOptimo(nodo *a, nodo *b, arco *arista, int x){
	
	if(a == NULL || arista == NULL || b == NULL || x == 0){
		return;
	}else{
		if(existeCamino(arista, b)){
			if(sumaPesosC(arista, b) == x){
				mostrarCamino(a, b, arista);
			}else{
				caminoOptimo(a, b, arista -> siguiente, x);
			}
		}
	}
}


void gotoxy(int x, int y){
    HANDLE hcon;
    COORD dwPos;
 
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos); 
}

void lineas(){
}

void grafoGrafico(nodo *cabeza, int x, int y){
	
	if(cabeza == NULL){
		return;
	}else{
		gotoxy(x, y);
		printf("%c", cabeza -> nombre);
		grafoGrafico(cabeza -> siguiente, x + 4, y);
	}
}

int main(){
	nodo *lista = NULL;
	nodo *a, *b;
	int x;
	bool e;
	
	insertarNodo(&lista, 'a');
	insertarNodo(&lista, 'b');
	insertarNodo(&lista, 'c');
	insertarNodo(&lista, 'd');
	insertarNodo(&lista, 'e');
	insertarNodo(&lista, 'f');
	
	insertarArco(&lista, 5, 'a', 'b');
	insertarArco(&lista, 2, 'a', 'd');
	insertarArco(&lista, 1, 'b', 'c');
	insertarArco(&lista, 22, 'c', 'e');
	insertarArco(&lista, 4, 'd', 'e');
	insertarArco(&lista, 21, 'f', 'e');
	
	/*mostrar(lista);
	
	a = buscarNodo(lista, 'a');
	b = buscarNodo(lista, 'e');
	
	x = gradoEntrada(lista, b);
	printf("Grado Entrada Nodo %c: %d\n", b -> nombre, x);
	x = gradoSalida(b -> adyunto);
	printf("Grado Salida Nodo %c: %d\n", b -> nombre, x);
	x = grado(lista, b);
	printf("Grado Total Nodo %c: %d\n", b -> nombre, x);
	
	mostrarX(lista, 'a');
	
	x = numeroCaminos(a -> adyunto, b);
	printf("\nNumero de Caminos: %d\n", x);
	
	e = existeCamino(a -> adyunto, b);
	if(e){
		printf("\nExiste\n");
		mostrarCaminos(a, b, a -> adyunto);
	}else{
		printf("\nNo existe\n");
	}
	
	x = sumaPesosC(a -> adyunto, b);
	printf("Suma Pesos: %d\n", x);
	
	x = caminoMenor(a -> adyunto, b);
	printf("Camino Menor: %d\n", x);
	
	caminoOptimo(a, b, a -> adyunto, caminoMenor(a -> adyunto, b));
	
	eliminarNodo(&lista, 'l');
	eliminarArco(&lista, 4, 'f');
	eliminarArcoX(&lista, 'a', 'b');
	eliminarArcoX(&lista, 'l', 'w');
	mostrar(lista);
	
	mostrarX(lista, 'a');
	*/
	grafoGrafico(lista, 30, 10);
	printf("\n\n\n");
	
	system("pause");
	return 0;
}
