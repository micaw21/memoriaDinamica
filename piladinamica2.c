#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Definicion de Tipos
typedef char tString [50];

typedef struct{
    int DNI;
    tString nombreApellido;
    tString email;
    int categoria;
    float montoAbonado;
}tInscriptos;

typedef struct nodo{
    tInscriptos inscripto;
    struct nodo * siguiente;
}tPila;

//Variables Globales
tPila * pila;
tInscriptos inscriptos;
tString vCategorias [3] = {"Estudiante","Profesional","Publico General"};

//Prototipo de Funciones
void inicializarPila();
bool pilaVacia(tPila *);
void ingresarDatos();
void insertarInscripto(tInscriptos);
void eliminarInscripto();
void visualizarPila(tPila *);
tInscriptos cima(tPila *);
void mostrarCima();
int contarProfesionales();
int contarTotalInscriptos();
float calcularPorcentaje();
void mostrarCantProfesionales();
void mostrarPorcentajeProf();
float totalRecaudoEstudiantes();
void mostrarRecaudacionEstudiantes();
float totalReucaudacion();
void mostrarTotal();
void menu();
void menuOpciones(int);

//Funcion Principal
int main(){
    inicializarPila();
    menu();
}

//Implementacion
void inicializarPila(){
    pila = NULL;
}

bool pilaVacia(tPila * pPila){
    return(pPila == NULL);
}

void menu(){
    int respuesta = 0;
    printf("\t\nElija una opcion\n");
    printf("1-Ingresar inscripcion\n");
    printf("2-Eliminar inscripto\n");
    printf("3-Visualizar pila inscriptos\n");
    printf("4-Visualizar inscripto en cima\n");
    printf("5-Ver cantidad de profesionales inscriptos\n");
    printf("6-Ver pocentaje de profesionales inscriptos\n");
    printf("7-Ver monto recaudado con estudiantes inscriptos\n");
    printf("8-Ver total recaudado con inscripciones\n");
    printf("9-Salir: ");
    scanf("%d",&respuesta);
    menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
    switch (pRespuesta){
        case 1:
            ingresarDatos();
            insertarInscripto(inscriptos);
            menu();
        break;
        case 2:
            eliminarInscripto();
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
            mostrarCantProfesionales();
            menu();
        break;
        case 6:
            mostrarPorcentajeProf();
            menu();
        break;
        case 7:
            mostrarRecaudacionEstudiantes();
            menu();
        break;
        case 8:
            mostrarTotal();
            menu();
        break;
        default:
            printf("Programa finalizado!\n");
        break;
    }
}

void ingresarDatos() {
    printf("\nIngrese su DNI: ");
    scanf("%d",&inscriptos.DNI);
    printf("Ingrese su Nombre y Apellido: ");
    fflush(stdin);
    gets(inscriptos.nombreApellido);
    printf("Ingrese su correo electronico: ");
    fflush(stdin);
    gets(inscriptos.email);
    printf("Ingrese el codigo de su categoria (1-Estudiante, 2-Profesional, 3-General): ");
    scanf("%d",&inscriptos.categoria);
    do {
        printf("Ingrese monto abonado ($200 Estudiantes - $350 Profesionales y General): ");
        scanf("%f",&inscriptos.montoAbonado);
    } while(inscriptos.categoria == 1 && inscriptos.montoAbonado == 350 || inscriptos.categoria == 2 && inscriptos.montoAbonado == 200 || inscriptos.categoria == 3 && inscriptos.montoAbonado == 200);
}

void insertarInscripto(tInscriptos pInscripto){
    tPila * nodo;
    nodo = (tPila*)malloc(sizeof(tPila));
    nodo->inscripto = pInscripto;
    nodo->siguiente = pila;
    pila = nodo;
    printf("\nInscripto agregado!\n");
}

void eliminarInscripto(){
    tPila * nodoSuprimir;
    if(pilaVacia(pila)){
        printf("\nNo hay inscriptos para eliminar!\n");
    } else {
        nodoSuprimir = pila;
        pila = pila->siguiente;
        free(nodoSuprimir);
        nodoSuprimir = NULL;
        printf("\nInscripto eliminado!\n");
    }
}

void visualizarPila(tPila * pPila){
    tPila * aux;
    aux = pPila;
    if(pilaVacia(pPila)){
        printf("\nNo hay inscriptos por visualizar!\n");
    } else {
        printf("\t\n***Inscriptos***\n");
        while(aux != NULL){
            printf("DNI: %d\n",aux->inscripto.DNI);
            printf("Nombre y Apellido: %s\n",aux->inscripto.nombreApellido);
            printf("Correo Electronico: %s\n",aux->inscripto.email);
            printf("Categoria: %s\n",vCategorias[aux->inscripto.categoria-1]);
            printf("Monto abonado: %.2f\n\n",aux->inscripto.montoAbonado);
            aux = aux->siguiente;
        }
    }
}

tInscriptos cima(tPila * pPila){
    return(pPila->inscripto);
}

void mostrarCima() {
    tInscriptos inscripto = cima(pila);
    if(pilaVacia(pila)){
        printf("\nNo hay inscriptos en pila!\n");
    } else {
        printf("\t\n*** Inscripto en cima ***\n");
        printf("DNI: %d\n",inscripto.DNI);
        printf("Nombre y Apellido: %s\n",inscripto.nombreApellido);
        printf("Correo Electronico: %s\n",inscripto.email);
        printf("Categoria: %s\n",vCategorias[inscripto.categoria - 1]);
        printf("Monto abonado: %.2f\n\n",inscripto.montoAbonado);
    }
}

int contarProfesionales() {
    tPila * aux;
    int contador = 0;
    aux = pila;
    while(aux != NULL){
        if(aux->inscripto.categoria == 2){
            contador = contador + 1;
        }
        aux = aux->siguiente;
    }
    return contador;
}

int contarTotalInscriptos(){
    tPila * aux;
    int contador = 0;
    aux = pila; 
    while(aux != NULL){
        contador = contador + 1;
        aux = aux->siguiente;
    }
    return contador;
}

float calcularPorcentaje(){
    float porcentaje = 0;
    int parcial = contarProfesionales();
    int total = contarTotalInscriptos();
    porcentaje = ((float)parcial * 100) / (float)total;
    return porcentaje;
}

void mostrarCantProfesionales(){
    int cantidad = contarProfesionales();
    printf("\nCantidad de profesionales inscriptos: %d\n",cantidad);
}

void mostrarPorcentajeProf(){
    float porcentaje = calcularPorcentaje();
    printf("\nPorcentaje de profesionales sobre el total de inscriptos: %.2f%%\n",porcentaje);
}

float totalRecaudoEstudiantes(){
    tPila * aux;
    aux = pila;
    float acumulador = 0;
    while(aux != NULL){
        if(aux->inscripto.categoria == 1){
            acumulador = acumulador + aux->inscripto.montoAbonado;
        }
        aux = aux->siguiente;
    }
    return acumulador;
}

void mostrarRecaudacionEstudiantes(){
    float recaudacion = totalRecaudoEstudiantes();
    printf("\nTotal recaudado por inscripciones de estudiantes: $%.2f\n",recaudacion);
}

float totalRecaudacion(){
    tPila * aux;
    aux = pila;
    float acumulador = 0;
    while(aux != NULL){
        acumulador = acumulador + aux->inscripto.montoAbonado;
        aux = aux->siguiente;
    }
    return acumulador;
}

void mostrarTotal() {
    float total = totalRecaudacion();
    printf("\nTotal recaudado en concepto de inscripciones: $%.2f\n",total);
}