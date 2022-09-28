#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Definicion de Tipos
typedef char tString[25];

typedef struct{
    int nroTurno;
    tString nombre;
    int motivo;
}tPersona;

typedef struct nodo{
    tPersona persona;
    struct nodo * siguiente;
}tNodo;

typedef struct{
    tNodo * frente;
    tNodo * final;
}tCola;
//Variables Globales
tCola cola;
tPersona persona;
tString vMotivos[2] = {"Transaccion","Consulta"};

//Prototipo de Funciones
void inicializarCola();
bool colaVacia(tCola);
void menu();
void menuOpciones(int);
void ingresarDatos();
void insertarPersona(tPersona);
void eliminarPersona();
void visualizarCola(tCola);
int cantPersonasTransaccion();
void mostrarCantTransaccion();
int cantPersonasConsulta();
void mostrarCantConsulta();

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

bool colaVacia(tCola pCola){
    return (pCola.frente == NULL);
}

void menu() {
    int respuesta = 0;
    printf("Elija una opcion\n");
    printf("1-Ingresar persona al sistema\n");
    printf("2-Eliminar persona del sistema\n");
    printf("3-Visualizar personas en sistema\n");
    printf("4-Visualizar cantidad de personas con motivo de transaccion\n");
    printf("5-Visualizar cantidad de personas con motivo de consulta\n");
    printf("6-Salir: ");
    scanf("%d",&respuesta);
    menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
    switch(pRespuesta) {
        case 1:
            ingresarDatos();
            insertarPersona(persona);
            menu();
        break;
        case 2:
            eliminarPersona();
            menu();
        break;
        case 3:
            visualizarCola(cola);
            menu();
        break;
        case 4:
            mostrarCantTransaccion();
            menu();
        break;
        case 5:
            mostrarCantConsulta();
            menu();
        break;
        default: 
            printf("Programa finalizado!\n");
        break;
    }
}

void ingresarDatos() {
    printf("Ingrese su numero de turno: ");
    scanf("%d",&persona.nroTurno);
    printf("Ingrese su nombre: ");
    fflush(stdin);
    gets(persona.nombre);
    printf("Ingrese su motivo (1-Transaccion, 2-Consulta): ");
    scanf("%d",&persona.motivo);
}

void insertarPersona(tPersona pPersona){
    tNodo * nodo;
    nodo = (tNodo*)malloc(sizeof(tNodo));
    nodo->persona = pPersona;
    nodo->siguiente = NULL;
    if(colaVacia(cola)){
        cola.final = nodo;
        cola.frente = nodo;
        printf("Persona agregada!\n");
    } else {
        cola.final->siguiente = nodo;
        cola.final = nodo;
        printf("Persona agregada!\n");
    }
}

void eliminarPersona() {
    tNodo * nodoSuprimir;
    if(colaVacia(cola)) {
        printf("La cola esta vacia!\n");
    } else {
        nodoSuprimir = cola.frente;
        if(cola.frente == cola.final){
            cola.final = NULL;
            cola.frente = NULL;
        } else {
            cola.frente = nodoSuprimir->siguiente;
        }
        free(nodoSuprimir);
        nodoSuprimir = NULL;
        printf("Persona eliminada de la cola!\n");
    }
}

void visualizarCola(tCola pCola){
    tNodo * aux;
    aux = cola.frente;
    if(colaVacia(cola)){
        printf("La cola esta vacia!\n");
    } else {
        printf("Personas en cola\n");
        while(aux != NULL){
            printf("Turno: %d - Nombre: %s - Motivo: %s\n",aux->persona.nroTurno,aux->persona.nombre,vMotivos[aux->persona.motivo - 1]);
            aux = aux->siguiente;
        }
    }
}

int cantPersonasTransaccion() {
    tNodo * aux;
    int contador = 0;
    aux = cola.frente;
    while(aux != NULL){
        if(aux->persona.motivo == 1){
            contador = contador + 1;
        }
        aux = aux->siguiente;
    }
    return contador;
}

void mostrarCantTransaccion() {
    int cantidad  = cantPersonasTransaccion();
    printf("Cantidad de personas con motivo de transaccion: %d\n",cantidad);
}

int cantPersonasConsulta() {
    int contador = 0;
    tNodo * aux;
    aux = cola.frente;
    while(aux != NULL){
        if(aux->persona.motivo == 2){
            contador = contador + 1;
        }
        aux = aux->siguiente;
    }
    return contador;
}

void mostrarCantConsulta(){
    int cantidad = cantPersonasConsulta();
    printf("Cantidad de personas con motivo de consulta: %d\n",cantidad);
}
