#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//Definicion de Tipos
typedef char tString[25];

typedef struct{
	char sexo; 
	int rangoEdad;
	float peso;
	float altura;
}tDatos;

typedef struct nodo{
	tDatos paciente;
	float IMC;
	struct nodo * siguiente;
}tLista;

//Variables Globales
tLista * lista;
tDatos pacientes;
//int contador = 0;

//Prototipo de Funciones
void inicializarLista();
bool listaVacia(tLista*);
void menu();
void menuOpciones(int);
void ingresarDatos();
float calcularIMC();
void insertarElemento(tDatos);
void insertarPrimero(tDatos);
void insertarAdelante(tDatos);
void insertarK(int, tDatos);
void eliminarElemento();
void eliminarPrimero();
void eliminarK(int);
int contarEncuestados();
void totalEncuestados();
int contarBajoPeso();
float acumularBajoPeso();
float calcularPromedio();
void promedioMenoresBajoPeso();
void listarSobrepeso();
void visualizarElementos(tLista *);


//Funcion Principal
int main(){
	inicializarLista();
	menu();	
	return 0;
}

//Implementacion
void inicializarLista(){
	lista = NULL;
}

bool listaVacia(tLista * pLista){
	return(pLista == NULL);
}

void menu() {
	int respuesta = 0;
	printf("Elija una opcion\n");
	printf("1-Ingresar un paciente\n");
	printf("2-Eliminar un paciente\n");
	printf("3-Cantidad total de encuestados\n");
	printf("4-Promedio de personas menores de 15 con Bajo Peso\n");
	printf("5-Listar personas con Sobrepeso\n");
	printf("6-Visualizar lista\n");
	printf("7-Salir: ");
	scanf("%d",&respuesta);
	menuOpciones(respuesta);
}

void menuOpciones(int pRespuesta){
	switch(pRespuesta){
		case 1:
			ingresarDatos();
			insertarElemento(pacientes);
			menu();
		break;
		case 2:
			eliminarElemento();
			menu();
		break;
		case 3:
			totalEncuestados();
			menu();
		break;
		case 4:
			promedioMenoresBajoPeso();
			menu();
		break;
		case 5:
			listarSobrepeso();
			menu();
		break;
		case 6:
			visualizarElementos(lista);
			menu();
		break;
		default:
			printf("Programa terminado!\n");
		break;
	}
}

void ingresarDatos() {
	printf("Ingrese su sexo (F o M): ");
	fflush(stdin);
	scanf("%c",&pacientes.sexo);
	printf("Ingrese su rango de edad (1-menor de 15, 2-Entre 15 y 30, 3-Mas de 30): ");
	scanf("%d",&pacientes.rangoEdad);
	printf("Ingrese su peso: ");
	scanf("%f",&pacientes.peso);
	printf("Ingrese su altura: ");
	scanf("%f",&pacientes.altura);
}

void insertarElemento(tDatos pPaciente){
	int respuesta = 0;
	int k = 0;
	if(listaVacia(lista)){
		insertarPrimero(pPaciente);
		//contador++;
	} else {
		printf("Desea insertar adelante? 1-Si 2-No: ");
		scanf("%d",&respuesta);
		if(respuesta == 1){
			insertarAdelante(pPaciente);
			//contador++;
		} else{
			printf("En que posicion desea insertar? (distinta de 1)");
			scanf("%d",&k);
			insertarK(k, pPaciente);
			//contador++;
		}
	}
}

void insertarPrimero(tDatos pDatos){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->paciente = pDatos;
	nodo->IMC = calcularIMC();
	nodo->siguiente =  NULL;
	lista = nodo;
	printf("Primer paciente agregado!\n");
}

float calcularIMC() {
	float kg = pacientes.peso;
	float altura = pacientes.altura;
	float IMC = 0;
	IMC = kg / (altura * 2);
	return IMC;
}

void insertarAdelante(tDatos pPaciente){
	tLista * nodo;
	nodo = (tLista*)malloc(sizeof(tLista));
	nodo->paciente = pPaciente;
	nodo->IMC = calcularIMC();
	nodo->siguiente = lista;
	lista = nodo;
	printf("Paciente agregado!\n");
}

void insertarK(int pK, tDatos pDatos){
	tLista * nodo;
	tLista * aux;
	int i;

	aux = lista;

	for(i=1;i<(pK - 1);i++){
		aux = aux->siguiente;
	}

	nodo = (tLista*)malloc(sizeof(tLista));

	nodo->paciente = pDatos;
	nodo->IMC = calcularIMC();

	nodo->siguiente = aux->siguiente;
	aux->siguiente = nodo;

	printf("Paciente agregado en la posicion %d\n",pK);
}

void eliminarElemento(){
	int respuesta = 0;
	int k = 0;
	if(listaVacia(lista)){
		printf("No hay pacientes por eliminar!\n");
	} else {
		printf("Desea eliminar el primer paciente? 1-Si 2-No");
		scanf("%d",&respuesta);
		if(respuesta == 1){
			eliminarPrimero();
		} else {
			printf("Que paciente desea eliminar? (distinto de 1)");
			scanf("%d",&k);
			eliminarK(k);
		}
	}
}

void eliminarPrimero() {
	tLista * nodoSuprimir;
	nodoSuprimir = lista;
	lista = lista->siguiente;
	free(nodoSuprimir);
	nodoSuprimir = NULL;
	printf("Primer paciente eliminado!\n");
}

void eliminarK(int pK){
	int i;
	tLista * nodoSuprimir;
	tLista * aux;

	aux = lista;

	for(i=1;i<(pK - 1);i++){
		aux = aux->siguiente;
	}

	nodoSuprimir = aux->siguiente;
	aux->siguiente = nodoSuprimir->siguiente;
	free(nodoSuprimir);
	nodoSuprimir = NULL;
	printf("Paciente de la posicion %d eliminado!\n",pK);
}


int contarEncuestados() {
	tLista * aux;
	int contador = 0;
	aux = lista;

	while(aux != NULL){
		contador = contador + 1;
		aux = aux->siguiente;
	}

	return contador;
}

void totalEncuestados() {
	int contador = contarEncuestados();
	printf("El total de pacientes encuestados es de: %d!\n",contador);
}

int contarBajoPeso();
float acumularBajoPeso();
float calcularPromedio();
void promedioMenoresBajoPeso();

void promedioMenoresBajoPeso(){
	float promedio = calcularPromedio();
	printf("El promedio de menores de 15 anios con bajo peso es de: %.2f%%\n",promedio);
}

int contarBajoPeso(){
	int contador = 0;
	tLista * aux;
	aux = lista;
	while(aux != NULL) {
		if((aux->IMC <20 && aux->paciente.sexo == 'F' && aux->paciente.rangoEdad == 1) || (aux->IMC <19 && aux->paciente.sexo == 'M' && aux->paciente.rangoEdad == 1)){
			contador = contador + 1;
			aux = aux->siguiente;
		}
	}

	return contador;
}

float acumularBajoPeso() {
	float acumulador = 0;
	tLista * aux;
	aux = lista;
	while(aux != NULL) {
		if((aux->IMC <20 && aux->paciente.sexo == 'F' && aux->paciente.rangoEdad == 1) || (aux->IMC <19 && aux->paciente.sexo == 'M' && aux->paciente.rangoEdad == 1)){
			acumulador = acumulador + aux->paciente.peso;
			aux = aux->siguiente;
		}
	}

	return acumulador;
}

float calcularPromedio() {
	float acumulador = acumularBajoPeso();
	int contador = contarBajoPeso();
	float promedio = 0;
	promedio = acumulador / (float)contador;
	return promedio;
}

void listarSobrepeso() {
	tLista * aux;
	aux = lista;
	if(listaVacia(lista)){
		printf("La lista esta vacia!\n");
	} else {
		while(aux != NULL){
			if((aux->IMC > 25 && aux->paciente.sexo == 'F') || (aux->IMC > 24 && aux->paciente.sexo == 'M')){
				switch(aux->paciente.rangoEdad){
				case 1:
					printf("Rango de edad: Menor de 15 anios - Sexo: %c - Altura: %.2fm - Peso: %.2fkg\n",aux->paciente.sexo, aux->paciente.altura, aux->paciente.peso);
				break;
				case 2:
					printf("Rango de edad: Entre 15 y 30 anios - Sexo: %c - Altura: %.2fm - Peso: %.2fkg\n",aux->paciente.sexo, aux->paciente.altura, aux->paciente.peso);
				break;
				case 3:
					printf("Rango de edad: Mayor de 30 - Sexo: %c - Altura: %.2fm - Peso: %.2fkg\n",aux->paciente.sexo, aux->paciente.altura, aux->paciente.peso);
				break;
				default:
					printf("Rango de edad incorrecto!\n");
				break;
				} 
			} else {
				printf("No hay pacientes con sobrepeso!\n");
			}
			aux = aux->siguiente;
		}
	}
}

void visualizarElementos(tLista * pLista){
	tLista * aux;
	aux = pLista;
	if(listaVacia(lista)){
		printf("No hay pacientes por mostar!\n");
	} else {
		printf("Pacientes en lista\n");
		while(aux != NULL){
			printf("Rango edad: %d - Sexo: %c - Altura: %.2f - Peso: %.2f - IMC: %.2f\n",aux->paciente.rangoEdad,aux->paciente.sexo,aux->paciente.altura,aux->paciente.peso,aux->IMC);
			aux = aux->siguiente;
		}
	}
}






























































