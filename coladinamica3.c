#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//Definicion de Tipos
typedef char tString [30];

typedef struct{
    int IP;
    tString nombre;
    short tipo;
    int tamanio;
}tDocumento;

typedef struct nodo {
    tDocumento documento;
    struct nodo * siguiente;
}tNodo;

typedef struct {
    tNodo * frente;
    tNodo * final;
}tCola;

//Variables Globales
tDocumento documento;
tCola cola;
tString vTipos [5] = {".docx",".pdf",".jpg",".png",".xlsx"};

//Prototipo de Funciones
void menu();
void menuOpciones(int);
void inicializarCola();
bool colaVacia(tCola);
void ingresarDatos();
void insertarDocumento(tDocumento);
void eliminarDocumento();
void visualizarCola(tCola);
int cantImagenes();
void mostrarCantImagenes();
float tamanioTotal();
void mostrarTamanioTotal();
void siguienteImpresion(tCola);

//Funcion Principal
int main() {
    inicializarCola();
    menu();
    return 0;
}

//Implementacion
void inicializarCola() {
    cola.final = NULL;
    cola.frente = NULL;
}

bool colaVacia(tCola pCola) {
    return(pCola.frente == 0);
}

void menu() {
    int respuesta = 0;
    printf("\t\n*** Elija una opcion ***\n");
    printf("1-Ingresar documento\n");
    printf("2-Eliminar documento\n");
    printf("3-Visualizar cola de impresion\n");
    printf("4-Visualizar cantidad de imagenes a imprimir\n");
    printf("5-Visualizar tamanio total de cola de impresion\n");
    printf("6-Visualizar proximo documento a ser impreso\n");
    printf("7-Salir: ");
    scanf("%d",&respuesta);
    menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta) {
    switch(pRespuesta) {
        case 1:
            ingresarDatos();
            insertarDocumento(documento);
            menu();
        break;
        case 2:
            eliminarDocumento();
            menu();
        break;
        case 3:
            visualizarCola(cola);
            menu();
        break;
        case 4:
            mostrarCantImagenes();
            menu();
        break;
        case 5: 
            mostrarTamanioTotal();
            menu();
        break;
        case 6:
            siguienteImpresion(cola);
            menu();
        break;
        default:
            printf("Programa finalizado!\n");
        break;
    }
}

void ingresarDatos() {
    printf("\nIngrese la IP de la PC: ");
    scanf("%d",&documento.IP);
    printf("Ingrese nombre del documento: ");
    fflush(stdin);
    gets(documento.nombre);
    printf("Ingrese tipo de documento (1~.docx 2~.pdf 3~.jpg 4~.png 5~.xlsx): ");
    scanf("%d",&documento.tipo);
    printf("Ingrese su tamanio en bytes: ");
    scanf("%d",&documento.tamanio);
}

void insertarDocumento(tDocumento pDatos) {
    tNodo * nodo;
    nodo = (tNodo*)malloc(sizeof(tNodo));
    nodo->documento = pDatos;
    nodo->siguiente = NULL;
    if(colaVacia(cola)) {
        cola.final = nodo;
        cola.frente = nodo;
        printf("Documento insertado!\n");
    } else {
        cola.final->siguiente = nodo;
        cola.final = nodo;
        printf("Documento insertado!\n");
    }
}

void eliminarDocumento() {
    tNodo * nodo;
    nodo = cola.frente;
    if (colaVacia(cola)) {
        printf("No hay documentos para eliminar!\n");
    } else {
        if (cola.final == cola.frente) {
            cola.final = NULL;
            cola.frente = NULL;
        } else {
            cola.frente =  nodo->siguiente;
        }
        free(nodo);
        nodo = NULL;
    }
}

void visualizarCola(tCola pCola) {
    tNodo * aux;
    aux = cola.frente;
    if(colaVacia(cola)) {
        printf("No hay documentos para visualizar!\n");
    } else {
        printf("\t ***Documentos en Cola de Impresion ***\n");
        while (aux != NULL) {
            printf("IP: %d - Nombre: %s - Tipo Documento: %s - Tamanio en Bytes: %d\n",aux->documento.IP,aux->documento.nombre,vTipos[aux->documento.tipo - 1],aux->documento.tamanio);
            aux = aux->siguiente;
        }
    }
}

int cantImagenes() {
    int contador = 0;
    tNodo * aux;
    aux = cola.frente;
    while (aux != NULL) {
        if(aux->documento.tipo == 3 || aux->documento.tipo == 4) {
            contador++;
        }
        aux = aux->siguiente;
    }
    return contador;
}

void mostrarCantImagenes() {
    int imagenes = cantImagenes();
    printf("Cantidad de imagenes en cola de impresion: %d\n",imagenes);
}

float tamanioTotal() {
    tNodo * aux;
    float acumulador = 0;
    float totalMB = 0;
    aux = cola.frente;
    while (aux != NULL) {
        acumulador = acumulador + aux->documento.tamanio;
        aux = aux->siguiente;
    }
    totalMB = (acumulador / 1048576/*1024 al cuadrado*/);
    return totalMB;
}

void mostrarTamanioTotal() {
    float tamanio = tamanioTotal();
    printf("Tamanio total de documentos en cola de impresion: %f mb\n",tamanio);
}

void siguienteImpresion(tCola pCola) {
    printf("Proximo documento a imprimir: %s\n",cola.frente->documento.nombre);
}