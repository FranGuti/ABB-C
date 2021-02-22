#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pila.h"

typedef struct abb_nodo{
	char* clave;
	void* valor;
	struct abb_nodo* hijo_izq;
	struct abb_nodo* hijo_der;
}abb_nodo_t;

struct abb{
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};

/*--------------------------------------- FUNCIONES AUXILIARES DE ABB_NODO --------------------------------*/

abb_nodo_t* abb_nodo_crear(const char* clave, void* valor, abb_nodo_t* hijo_izq, abb_nodo_t* hijo_der){
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if(!nodo){
		return NULL;
	}
	char* clave_cpy = strdup(clave);
	nodo->clave = clave_cpy;
	nodo->valor = valor;
	nodo->hijo_izq = hijo_izq;
	nodo->hijo_der = hijo_der;
	return nodo;
}


/*------------------------------------------- FUNCIONES AUXILIARES DEL ABB ---------------------------------*/

abb_nodo_t* abb_buscar_nodo(const abb_t* arbol, abb_nodo_t* nodo, const char* clave){
	
	if(!nodo) return NULL;
	int comparacion = arbol->cmp(clave, nodo->clave);
	if(comparacion == 0){
		return nodo;
	}
	else if(comparacion < 0){
		return abb_buscar_nodo(arbol, nodo->hijo_izq, clave);
	}
	return abb_buscar_nodo(arbol, nodo->hijo_der, clave);
}

abb_nodo_t* abb_buscar_padre(abb_t* arbol, abb_nodo_t* nodo, abb_nodo_t* padre, const char* clave){

	if(nodo == NULL){
		return padre;
	}

	int comparacion = arbol->cmp(clave, nodo->clave);

	if(comparacion == 0){
		return padre;
	}
	else if(comparacion < 0){
		return abb_buscar_padre(arbol, nodo->hijo_izq, nodo, clave);
	}
	return abb_buscar_padre(arbol, nodo->hijo_der, nodo, clave);
}


abb_nodo_t* ultimo_hijo_derecha(abb_nodo_t* nodo){
	if(!nodo->hijo_der)return nodo;
	return ultimo_hijo_derecha(nodo->hijo_der);
}

void abb_borrar_nodo(abb_t* arbol, abb_nodo_t* nodo, abb_nodo_t* padre, abb_nodo_t* reemplazante){
	if(!padre){
		arbol->raiz = reemplazante;
		return;
	}
	int comparacion = strcmp(nodo->clave, padre->clave);
	if(comparacion < 0){
		padre->hijo_izq = reemplazante;
	}
	else{
		padre->hijo_der = reemplazante;
	}
}

void _destruir_nodos(abb_nodo_t* nodo, abb_t* arbol){
	if(!nodo) return;
	_destruir_nodos(nodo->hijo_izq,arbol);
	_destruir_nodos(nodo->hijo_der,arbol);
	if(arbol->destruir_dato){
		arbol->destruir_dato(nodo->valor);
	}
	free(nodo->clave);
	free(nodo);
}

/*------------------------------------------ PRIMITIVAS DEL ABB ----------------------------------------------*/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb->raiz = NULL;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cantidad = 0;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

	abb_nodo_t* nodo = abb_buscar_nodo(arbol, arbol->raiz, clave); 
	if(nodo != NULL){
		if(arbol->destruir_dato) arbol->destruir_dato(nodo->valor);
		nodo->valor = dato;
		return true;
	}

	nodo = abb_nodo_crear(clave,dato,NULL,NULL);
	abb_nodo_t* padre = abb_buscar_padre(arbol, arbol->raiz, NULL, clave);

	if(!nodo)return false;

	if(!padre){
		arbol->raiz = nodo;
		arbol->cantidad++;
		return true;
	}

	int comparacion = arbol->cmp(clave, padre->clave);

	if(comparacion < 0){
		padre->hijo_izq = nodo;
	}
	else{
		padre->hijo_der = nodo;                         
	}       

	arbol->cantidad = arbol->cantidad + 1;

	return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){

	if(!arbol->raiz) return NULL;

	abb_nodo_t* padre = abb_buscar_padre(arbol, arbol->raiz, NULL, clave);

	abb_nodo_t* nodo;

	if(!padre){
		nodo = abb_buscar_nodo(arbol, arbol->raiz, clave);
	}
	else{
		if(strcmp(clave, padre->clave) < 0){
			nodo = padre->hijo_izq;
		}
		else{
			nodo = padre->hijo_der;
		}
	}

	if(!nodo){
			return NULL;
		}

	arbol->cantidad--;
	void* dato = nodo->valor;

	//sin hijos
	if(nodo->hijo_der == NULL && nodo->hijo_izq == NULL){
		abb_borrar_nodo(arbol, nodo, padre, NULL);
	}
	//con un hijo
	else if((nodo->hijo_der == NULL && nodo->hijo_izq != NULL) || (nodo->hijo_izq == NULL && nodo->hijo_der != NULL)){
		abb_nodo_t* hijo =	nodo->hijo_izq;
		if(!hijo){
			hijo = nodo->hijo_der;
		}
		abb_borrar_nodo(arbol, nodo, padre, hijo);
	}
	//con dos hijos
	else{
		abb_nodo_t* reemplazante = ultimo_hijo_derecha(nodo->hijo_izq);
		abb_nodo_t* padre_reemplazante = abb_buscar_padre(arbol,arbol->raiz,NULL,reemplazante->clave);
		abb_borrar_nodo(arbol, reemplazante, padre_reemplazante, reemplazante->hijo_izq);
		free(nodo->clave);
		nodo->clave = reemplazante->clave;
		nodo->valor = reemplazante->valor;
		free(reemplazante);
		return dato;
	}
	free(nodo->clave);
	free(nodo);
	return dato;

}

void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_buscar_nodo(arbol,arbol->raiz,clave);
	if(!nodo)return NULL;
	return nodo->valor;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = abb_buscar_nodo(arbol, arbol->raiz, clave);
	if(nodo){
		return true;
	}
	return false;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
	if(!arbol) return;
	_destruir_nodos(arbol->raiz,arbol);
	free(arbol);
}

/*----------------------------------------------- ITERADOR INTERNO --------------------------------------------*/

bool _abb_in_order(abb_nodo_t* nodo, bool visitar(const char* clave, void *dato, void *extra), void* extra){
    if(nodo == NULL){
    	return true;
    }

    if(!_abb_in_order(nodo->hijo_izq, visitar, extra) ||
       !visitar(nodo->clave, nodo->valor, extra)){

		return false;
    }

    return _abb_in_order(nodo->hijo_der, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *clave, void *dato, void *extra), void *extra){
	if(!arbol){
		return;
	}
	_abb_in_order(arbol->raiz, visitar, extra);
}

/*------------------------------------------------ ITERADOR EXTERNO -------------------------------------------*/

struct abb_iter{
	const abb_t* abb;
	pila_t* pila;
};

void apilar_hijos(abb_nodo_t* nodo, pila_t* pila){
	if(!nodo) return;
	pila_apilar(pila,nodo);
	apilar_hijos(nodo->hijo_izq,pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter_abb = malloc(sizeof(abb_iter_t));
  	if(!iter_abb) return NULL;
  	iter_abb->pila = pila_crear();
  	if(!iter_abb->pila){
    	free(iter_abb);
    	return NULL;
  	}

  	if(arbol->raiz){
    	apilar_hijos(arbol->raiz, iter_abb->pila);
  	}

  	iter_abb->abb = arbol;

  	return iter_abb;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)){
		return false;
	}
	abb_nodo_t* nodo = pila_desapilar(iter->pila);
	if(nodo->hijo_der)apilar_hijos(nodo->hijo_der,iter->pila);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)){
		return NULL;
	}
	return ((abb_nodo_t*)pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}