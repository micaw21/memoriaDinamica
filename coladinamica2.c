#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//Definicion de Tipos
typedef char tString[50];

typedef struct{
    tString nombreApellido;
    unsigned long nroTelefono;
    int DNI;
    short codigoProcedencia;
}tPersonas;

typedef struct nodo{
    tPersonas persona;
    struct nodo * siguiente;
}tNodo;

typedef struct{
    tNodo * frente;
    tNodo * final;
}tCola;

//Variables Globales
tCola cola;
tPersonas persona;
//short vProcedencia [2] = {0,0};
tString vLugares [2] = {"Corrientes","Chaco"};

//Prototipo de Funciones
void inicializarCola();
bool colaVacia(tCola);
void ingresarDatos();
void ingresarPersona(tPersonas);
void menu();
void menuOpciones(int);
void eliminarPersona();
void visualizarCola(tCola);
void cantLlamadasPorProcedencia();
int cantLlamadasTotal();
void mostrarCantPorProcedencia(int, int);
void mostrarTotalLlamadas();
void visualizarNrosCorrientes();

//Funcion Principal
int main() {
    inicializarCola();
    menu();
}
//Implementacion
void inicializarCola() {
    cola.final = NULL;
    cola.frente = NULL;
}

bool colaVacia(tCola pCola){
    return(pCola.frente == NULL);
}

void menu() {
    int respuesta = 0;
    printf("Elija una opcion\n");
    printf("1-Ingresar llamada\n");
    printf("2-Eliminar llamada\n");
    printf("3-Visualizar cola de llamadas\n");
    printf("4-Ver cantidad de llamadas por provincia\n");
    printf("5-Ver cantidad total de llamdas en espera\n");
    printf("6-Visualizar numeros en cola provenientes de Corrientes\n");
    printf("7-Salir > ");
    scanf("%d",&respuesta);
    menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
    switch(pRespuesta){
        case 1:
            ingresarDatos();
            ingresarPersona(persona);
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
            cantLlamadasPorProcedencia();
            menu();
        break;
        case 5:
            mostrarTotalLlamadas();
            menu();
        break;
        case 6:
            visualizarNrosCorrientes();
            menu();
        break;
        default:
            printf("Programa finalizado!\n");
        break;
    }
}

void ingresarDatos() {
    printf("Ingrese su nombre y apellido > ");
    fflush(stdin);
    gets(persona.nombreApellido);
    printf("Ingrese su numero de telefono > ");
    scanf("%lu",&persona.nroTelefono);
    printf("Ingrese su DNI > ");
    scanf("%d",&persona.DNI);
    printf("Ingrese su codigo de procedencia (1-Corrienttes, 2-Chaco) > ");
    scanf("%d",&persona.codigoProcedencia);
}

void ingresarPersona(tPersonas pDatos){
    tNodo * nodo;
    nodo = (tNodo*)malloc(sizeof(tNodo));
    nodo->persona = pDatos;
    nodo->siguiente = NULL;
    if(colaVacia(cola)){
        cola.final = nodo;
        cola.frente = nodo;
        printf("Llamada insertada en cola de espera!\n");
    } else {
        cola.final->siguiente = nodo;
        cola.final = nodo;
        printf("Llamada insertada en cola de espera!\n");
    }
}

void eliminarPersona() {
    tNodo * nodoSupr;
    if(colaVacia(cola)){
        printf("No hay llamadas en espera!\n");
    } else {
        nodoSupr = cola.frente;
        if(cola.frente == cola.final){
            cola.final = NULL;
            cola.frente = NULL; 
        } else {
            cola.frente = nodoSupr->siguiente;
        }
        free(nodoSupr);
        nodoSupr = NULL;
        printf("Llamada eliminada!\n");
    }
}

void cantLlamadasPorProcedencia() {
    tNodo * aux;
    aux = cola.frente;
    int contCorrientes = 0;
    int contChaco = 0;

    while (aux != NULL){
        //vProcedencia[aux->persona.codigoProcedencia - 1] = vProcedencia[aux->persona.codigoProcedencia - 1] + 1;
        if (aux->persona.codigoProcedencia == 1) {
            contCorrientes++;
        } else {
            contChaco++;
        }
        aux = aux->siguiente;
    }

    mostrarCantPorProcedencia(contCorrientes, contChaco);
}

void mostrarCantPorProcedencia(int pContCtes, int pContChaco) {
    printf("\t*** Cantidad de llamadas por procedencia ***\n");
    printf("Corrientes: %d\n",pContCtes);
    printf("Chaco: %d\n",pContChaco);
}

int cantLlamadasTotal() {
    tNodo * aux;
    int contador = 0;
    aux = cola.frente;
    while (aux != NULL){
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

void mostrarTotalLlamadas() {
    int total = cantLlamadasTotal();
    printf("Cantidad de llamadas en cola de espera: %d\n",total);
}

void visualizarNrosCorrientes() {
    tNodo * aux;
    aux = cola.frente;
    if (colaVacia(cola)) {
        printf("No hay llamadas en cola de espera!\n");
    } else {
        printf("\t** Numeros en cola de espera procedentes de Corrientes ***\n");
        while (aux != NULL) {
            if(aux->persona.codigoProcedencia == 1) {
                printf("Nro de Telefono: %lu\n",aux->persona.nroTelefono);
            }
            aux = aux->siguiente;
        }
    }
}

void visualizarCola(tCola pCola) {
    tNodo * aux;
    aux = cola.frente;
    if(colaVacia(cola)) {
        printf("No hay llamadas en cola de espera!\n");
    } else {
        printf("\t*** Llamadas en cola de espera ***\n");
        while (aux != NULL) {
            printf("Nombre y Apellido: %s - Numero de Telefono: %lu - DNI: %d - Lugar de Procedencia: %s\n",aux->persona.nombreApellido, aux->persona.nroTelefono, aux->persona.DNI, vLugares[aux->persona.codigoProcedencia - 1]);
            aux = aux->siguiente;       
        }
    }
}

   