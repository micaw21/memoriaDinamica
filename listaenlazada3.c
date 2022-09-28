#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Definicion de Tipos
typedef char tString[50];

typedef struct{
	int LU;
	tString nombre;
}tDatosAlumno;

typedef struct nodo{
	tDatosAlumno alumno;
	struct nodo * siguiente;
}tLista;

//Variables Globales
tLista * lista;
tDatosAlumno datosAlumno;
int contador = 0;

//Prototipo de Funciones
void inicializarLista();
void ingresarDatos();
bool listaVacia(tLista*);
void insertarElemento(tDatosAlumno);
void insertarPrimero(tDatosAlumno);
void insertarAdelante(tDatosAlumno);
void insertarK(int, tDatosAlumno);
void eliminarAlumno();
void eliminarPrimero();
void eliminarK(int);
void visualizarLista(tLista*);
void menu();
void menuOpciones(int);
void mostrarCantAlumnos(int);

//Funcion Prinpal
int main() {
	inicializarLista();
	menu();
	return 0;
}

//Implementacion
void inicializarLista(){
	lista = NULL;
}

void menu(){
	int respuesta = 0;
	printf("Elija una opcion\n");
	printf("1-Ingresar alumno\n");
	printf("2-Eliminar alumno\n");
	printf("3-Visualizar lista\n");
	printf("4-Conocer cantidad de alumnos\n");
	printf("5-Salir: ");
	scanf("%d",&respuesta);
	menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
	switch(pRespuesta){
		case 1:
			ingresarDatos();
			menu();
		break;
		case 2:
			eliminarAlumno();
			menu();
		break;
		case 3:
			visualizarLista(lista);
			menu();
		break;
		case 4:
			mostrarCantAlumnos(contador);
			menu();
		break;
		default:
			printf("Programa terminado!\n");
		break;	
	}
}

void ingresarDatos(){
	printf("Ingrese la libreta universitaria: ");
	scanf("%d",&datosAlumno.LU);
	printf("Ingrese el nombre del alumno: ");
	fflush(stdin);
	gets(datosAlumno.nombre);
	insertarElemento(datosAlumno);
}

void insertarElemento(tDatosAlumno pDatos){
	int respuesta = 0;
	int k = 0;
	
	contador++;
	
	if(listaVacia(lista)){
		insertarPrimero(pDatos);
	}else {
		printf("Desea insertar adelante? 1-Si, 2-No: ");
		scanf("%d",&respuesta);
		if(respuesta == 1){
			insertarAdelante(pDatos);
		} else {
			printf("En que posicion desea insertar?");
			scanf("%d",&k);
			insertarK(k, pDatos);
		}
		
	}
}

bool listaVacia(tLista * pLista){
	return(pLista == NULL);
}

void insertarPrimero(tDatosAlumno pDatos){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->alumno = pDatos;
	nodo->siguiente = NULL;
	lista = nodo;
	printf("Primer elemento insertado!\n");
}

void insertarAdelante(tDatosAlumno pDatos){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->alumno = pDatos;
	nodo->siguiente = lista;
	lista = nodo;
	printf("Elemento insertado!\n");
}

void insertarK(int pK, tDatosAlumno pDatos){
	int i;
	tLista * aux;
	tLista * nodo;
	aux = lista;
	
	for(i=1;i<(pK-1);i++){
		aux = aux->siguiente;
	}
	
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->alumno = pDatos;
	nodo->siguiente = aux->siguiente;
	aux->siguiente = nodo;
	printf("Elemento insertado en la posicion %d\n",pK);
}

void eliminarAlumno(){
	int k = 0;
	int respuesta = 0;
	
	contador--;
	
	if(listaVacia(lista)){
		printf("No hay elementos por eliminar!\n");
	}else{
		printf("Desea eliminar el primero? 1-Si 2-No: ");
		scanf("%d",&respuesta);
		if (respuesta == 1){
			eliminarPrimero();
		} else {
			printf("Que elemento desea eliminar?: ");
			scanf("%d",&k);
			eliminarK(k);
		}
	}
}

void eliminarPrimero(){
	tLista * nodo;
	nodo = lista;
	lista = lista->siguiente;
	free(nodo);
	nodo = NULL;
	printf("Primer elemento eliminado!\n");	
}

void eliminarK(int pK){
	tLista * nodo;
	tLista * aux;
	int i;
	aux = lista;
	for(i=1;i<(pK-1);i++){
		aux = aux->siguiente;
	}
	nodo = aux->siguiente;
	aux->siguiente = nodo->siguiente;
	free(nodo);
	nodo = NULL;
	printf("Elemento de la posicion %d eliminado!\n",pK);	
}

void mostrarCantAlumnos(int pContador){
	printf("Cantidad de alumnos en lista: %d\n",pContador);
}

void visualizarLista(tLista * pLista){
	tLista * aux;
	aux = lista;
	if(listaVacia(lista)){
		printf("No hay elementos por mostrar!\n");
	}else{
		printf("Listado de Alumnos\n");
		while(aux != NULL){
			printf("LU: %d - Nombre: %s\n",aux->alumno.LU,aux->alumno.nombre);
			aux = aux->siguiente;
		}
	}
	
}