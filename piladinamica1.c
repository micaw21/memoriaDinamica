#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Definicion de Tipos
typedef char tString[20];
typedef struct{
    int codigoProd;
    int codigoRubro;
    int cantidad;
    float precioUnitario;
    tString descripcion;
}tProducto;

typedef struct nodo{
    tProducto producto;
    struct nodo * siguiente;
}tPila;

//Variables Globales
tPila * pila;
tProducto producto;

//Prototipo de Funciones
void inicializarPila();
void menu();
void menuOpciones(int);
void ingresarDatos();
void insertarProducto(tProducto);
void eliminarProducto();
void visualizarPila(tPila *);
bool pilaVacia(tPila *);
tProducto productoCima(tPila *);
void mostrarCima();
float calcularTotal();
void mostrarTotal();

//Funcion principal
int main() {
    inicializarPila();
    menu();
    return 0;
}

//Implementacion
void inicializarPila(){
    pila = NULL;
}

void menu() {
    int respuesta = 0;
    printf("Elija una opcion\n");
    printf("1-Ingresar producto\n");
    printf("2-Eliminar producto\n");
    printf("3-Visualizar pila\n");
    printf("4-Visualizar producto en cima\n");
    printf("5-Visualizar monto total recaudado\n");
    printf("6-Salir: ");
    scanf("%d",&respuesta);
    menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
    switch(pRespuesta){
        case 1:
            ingresarDatos();
            insertarProducto(producto);
            menu();
        break;
        case 2:
            eliminarProducto();
            menu();
        break;
        case 3:
            visualizarPila(pila);
            menu();
        break;
        case 4:
            mostrarCima();
            menu();
        break;
        case 5:
            mostrarTotal();
            menu();
        break;
        default:
            printf("Programa finalizado!\n");
        break;
    }
}

bool pilaVacia(tPila * pPila){
    return(pPila == NULL);
}

void ingresarDatos(){
    printf("Ingrese el codigo del producto: ");
    scanf("%d",&producto.codigoProd);
    printf("Ingrese el codigo de rubro: ");
    scanf("%d",&producto.codigoRubro);
    printf("Ingrese la cantidad: ");
    scanf("%d",&producto.cantidad);
    printf("Ingrese el precio unitario: ");
    scanf("%f",&producto.precioUnitario);
    printf("Ingrese la descripcion: ");
    fflush(stdin);
    gets(producto.descripcion);
}

void insertarProducto(tProducto pProducto){
    tPila * nodo;
    nodo = (tPila*)malloc(sizeof(tPila));
    nodo->producto = pProducto;
    nodo->siguiente = pila;
    pila = nodo;
    printf("Producto insertado!\n");
}

void eliminarProducto(){
    tPila * nodoSuprimir;
    if(pilaVacia(pila)){
        printf("La pila esta vacia!\n");
    } else {
        nodoSuprimir = pila;
        pila = pila->siguiente;
        free(nodoSuprimir);
        nodoSuprimir = NULL;
        printf("Producto eliminado!\n");
    }
}

void visualizarPila(tPila * pPila){
    tPila * aux;
    aux = pPila;
    if(pilaVacia(pila)){
        printf("No hay productos por visualizar!\n");
    } else {
        printf("\t***Productos en pila***\n");
        while(aux != NULL){ 
            printf("Codigo del Producto: %d\n",aux->producto.codigoProd);
            printf("Codigo de Rubro: %d\n",aux->producto.codigoRubro);
            printf("Descripcion: %s\n",aux->producto.descripcion);
            printf("Cantidad: %d\n",aux->producto.cantidad);
            printf("Precio Unitario: $%.2f\n\n",aux->producto.precioUnitario);
            aux = aux->siguiente;
        }
    }
}

void mostrarCima(){
    if (pilaVacia(pila)){
        printf("Pila vacia!\n");
    } else {
        tProducto producto = productoCima(pila);
        printf("El producto en cima es:\n");
        printf("Codigo del Producto: %d\n",producto.codigoProd);
        printf("Codigo de Rubro: %d\n",producto.codigoRubro);
        printf("Descripcion: %s\n",producto.descripcion);
        printf("Cantidad: %d\n",producto.cantidad);
        printf("Precio Unitario: $%.2f\n\n",producto.precioUnitario);    
    }
}

tProducto productoCima(tPila * pPila){
    return(pPila->producto);
}

float calcularTotal(){
    float total = 0;
    tPila * aux;
    float acumulador = 0;
    aux = pila;
    while(aux != NULL){
        total = (aux->producto.cantidad * aux->producto.precioUnitario);
        acumulador = acumulador + total;
        aux = aux->siguiente;
    }
    return acumulador;
}

void mostrarTotal(){
    float totalRecaudado = calcularTotal();
    printf("Monto Total Recaudado: $%.2f\n",totalRecaudado);
}