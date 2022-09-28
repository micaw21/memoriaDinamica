#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Definicion de Tipos
typedef char tString[50];

typedef struct{
	int codProducto;
	tString descripcion;
	float precioUnitario;
}tListaProductos;

typedef struct nodo{
	tListaProductos productos;
	struct nodo * siguiente;
}tLista;

//Variables Globales
tLista * lista;
tListaProductos datosProducto;

//Prototipo de Funciones
void inicializarLista();
void ingresarDatos();
void insertarPrimerElemento(tListaProductos);
bool listaVacia(tLista*);
void visualizarElementos(tLista*);


//Funcion Principal
int main() {
	inicializarLista();
	ingresarDatos();
	insertarPrimerElemento(datosProducto);
	visualizarElementos(lista);
	return 0;
}

//Implementacion
bool listaVacia(tLista * pLista){
	return(pLista == NULL);
}

void inicializarLista(){
	lista = NULL;
}

void ingresarDatos() {
	printf("Ingrese el codigo del producto: ");
	scanf("%d",&datosProducto.codProducto);
	printf("Ingrese la descripcion del producto: ");
	fflush(stdin);
	gets(datosProducto.descripcion);
	printf("Ingrese el precio unitario: ");
	scanf("%f",&datosProducto.precioUnitario);
}

void insertarPrimerElemento(tListaProductos pProducto){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->productos = pProducto;
	nodo->siguiente = NULL;
	lista = nodo;
	printf("Primer elemento insertado!\n");
}

void visualizarElementos(tLista * pLista){
	tLista * aux;
	aux = lista;
	if(listaVacia(lista)){
		printf("No hay elementos por mostrar!\n");
	} else {
		printf("ELEMENTOS EN LA LISTA\n");
		while(aux != NULL){
			printf("%d - %s - %.2f\n",aux->productos.codProducto,aux->productos.descripcion,aux->productos.precioUnitario);
			aux = aux->siguiente;
		}
	}
}



















