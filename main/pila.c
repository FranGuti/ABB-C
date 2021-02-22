#include "pila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define TAMANO_INICIAL 10
#define FACTOR_INCREMENTO 2
#define FACTOR_DECRECIMIENTO 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t* pila_crear(void){
	
	pila_t* pila = malloc(sizeof(pila_t));
	
	if (pila == NULL){
		return NULL;
	}

	pila->datos = malloc(TAMANO_INICIAL * sizeof(void*));

	if (pila->datos == NULL){
		return NULL;
	}

	pila->capacidad = TAMANO_INICIAL;
	pila->cantidad = 0;

	return pila;
}

bool redimensionar(pila_t *pila, size_t nueva_cap){

	void*nuevos_datos = realloc(pila->datos,nueva_cap * sizeof(void*));

	if(nuevos_datos == NULL){
		return false;
	}

	pila->datos = nuevos_datos;
	pila->capacidad = nueva_cap;

	return true;
}

void pila_destruir(pila_t *pila){

	free(pila->datos);
	free(pila);

}

bool pila_esta_vacia(const pila_t *pila){
	
	return pila->cantidad == 0;

}

bool pila_apilar(pila_t *pila, void* valor){
	
	size_t pos = pila->cantidad;
	
	pila->datos[pos] = valor;

	pila->cantidad = pos + 1;

	if(pila->cantidad > (pila->capacidad / FACTOR_INCREMENTO)){
		redimensionar(pila,pila->capacidad * FACTOR_INCREMENTO);
	}

	return true;
}


void* pila_ver_tope(const pila_t *pila){

	size_t pos = pila->cantidad;

	if(pila_esta_vacia(pila)){
		return NULL;
	}

	void* valor = pila->datos[pos - 1];
	return valor;
}

void* pila_desapilar(pila_t *pila){
	size_t pos = pila->cantidad;

	if(pila_esta_vacia(pila)){
		return NULL;
	}

	pila->cantidad = pos - 1;

	if(pila->cantidad < (pila->capacidad / FACTOR_DECRECIMIENTO)){
		redimensionar(pila,pila->capacidad / FACTOR_DECRECIMIENTO);
	}

	return pila->datos[pila->cantidad];
}

