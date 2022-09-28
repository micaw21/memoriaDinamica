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
void menu();
void menuOpciones(int);
void ingresarDatos();

//Funciones Basicas
void inicializarLista();

bool listaVacia(tLista *);

void insertarElemento(tListaProductos);
void insertarPrimero(tListaProductos);
void insertarAdelante(tListaProductos);
void insertarK(int, tListaProductos);

void eliminarElemento();
void eliminarPrimero();
void eliminarK(int);

void visualizarElementos(tLista *);


//Funcion Principal
int main(){
	inicializarLista();
	menu();
}

//Implementacion
void inicializarLista(){
	lista = NULL;
}

void menu(){
	int respuesta = 0;
	printf("Ingrese una opcion: \n");
	printf("1-Insertar elemento\n");
	printf("2-Eliminar elemento\n");
	printf("3-Lista vacia?\n");
	printf("4-Visualizar los elementos\n");
	printf("5-Salir \n");
	scanf("%d",&respuesta);
	menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
	switch(pRespuesta){
		case 1:
			ingresarDatos();
			insertarElemento(datosProducto);
			menu();
		break;
		case 2:
			eliminarElemento();
			menu();
		break;
		case 3:
			if(listaVacia(lista)){
				printf("La lista esta vacia!\n");
			} else{
				printf("La lista no esta vacia!\n");
			}
			menu();
		break;
		case 4:
			visualizarElementos(lista);
			menu();
		break;
		default:
			printf("Fin de programa!\n");
		break;	
	}
}

bool listaVacia(tLista * pLista){
	return(pLista == NULL);
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

void insertarElemento(tListaProductos pProducto){
	int respuesta = 0;
	int k = 0;
	if(listaVacia(lista)){
		insertarPrimero(pProducto);
	}else{
		insertarAdelante(pProducto);
		
	}
}

void insertarK(int pK, tListaProductos pProducto){
	tLista * nodo;
	tLista * aux;
	int i;
	aux = lista;
	
	for(i=1;i<pK-1;i++){
		aux = aux->siguiente;
	}
	
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->productos = pProducto;
	nodo->siguiente = aux->siguiente;
	aux->siguiente = nodo;
	printf("Elemento insertado en la posicion %d!\n",pK);
}


void insertarPrimero(tListaProductos pProducto){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->productos=pProducto;
	nodo->siguiente = NULL;
	lista = nodo;
	printf("Primer elemento insertado! %d\n",datosProducto.codProducto);
}

void insertarAdelante(tListaProductos pProducto){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->productos = pProducto;
	nodo->siguiente = lista;
	lista = nodo;
	printf("Elemento insertado! %d\n",datosProducto.codProducto);
}

void eliminarElemento(){
	int respuesta = 0;
	int k = -1;
	if(listaVacia(lista)) {
		printf("No hay elementos por eliminar!\n");
	} else {
		printf("Desea eliminar el primero? 1-Si 2-No: \n");
		scanf("%d",&respuesta);
		if(respuesta == 1){
			eliminarPrimero();
		} else {
			printf("En que posicion desea eliminar? ");
			scanf("%d",&k);
			eliminarK(k);
		}	
	}
}

void eliminarPrimero(){
	tLista * nodoSuprimir;
	nodoSuprimir = lista;
	lista = lista->siguiente;
	free(nodoSuprimir);
	nodoSuprimir = NULL;
	printf("Primer elemento eliminado! \n");
}

void eliminarK(int pK){
	tLista * nodoSuprimir;
	tLista * aux;
	int i;
	aux = lista;
	
	for(i=1;i<pK-1;i++){
		aux = aux->siguiente;
	}
	
	nodoSuprimir = aux->siguiente;
	
	aux->siguiente = nodoSuprimir->siguiente;
	
	free(nodoSuprimir);
	
	nodoSuprimir = NULL;
	
	printf("Elemento de la posicion %d eliminado!\n",pK);
}

void visualizarElementos(tLista * pLista){
	tLista * aux;
	aux = pLista;
	if(listaVacia(lista)){
		printf("La lista esta vacia!\n");
	}else{
		printf("***Elementos de la lista***\n");
		while(aux != NULL){
			printf("Codigo de Producto: %d - Precio Unitario: $%.2f -",aux->productos.codProducto,aux->productos.precioUnitario);
			printf("Descripcion: %s\n",aux->productos.descripcion);
			aux = aux->siguiente;
		}
	}
}