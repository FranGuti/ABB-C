#define _XOPEN_SOURCE 500
#include "abb.h"
#include "testing.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void abb_pruebas_vacio(){
	printf("\n\nPruebas con el ABB vacío\n\n");

	abb_t* arbol = abb_crear(strcmp, NULL);
	char* uno = strdup("1");

	print_test("La cantidad es 0", abb_cantidad(arbol)==0);
	print_test("No se puede borrar 1 del ABB", !abb_borrar(arbol, uno));
	print_test("Uno no pertenece al ABB", !abb_pertenece(arbol, uno));
	print_test("No se puede obtener uno del ABB", !abb_obtener(arbol, uno));
	
	abb_destruir(arbol);
	free(uno);
}

void abb_pruebas_unitarias(){
	printf("\nPruebas unitarias\n\n");

	abb_t* arbol = abb_crear(strcmp, NULL);
	char* uno = strdup("1");

	print_test("Inserto 1", abb_guardar(arbol, uno, uno));
	print_test("La cantidad es 1", abb_cantidad(arbol) == 1);
	print_test("Obtener 1 es igual a 1", abb_obtener(arbol, uno) == uno);
	print_test("1 pertenece al ABB", abb_pertenece(arbol, uno));
	print_test("Borrar 1 devuelve 1", abb_borrar(arbol, uno) == uno);
	print_test("La cantidad es 0",abb_cantidad(arbol) == 0);
	print_test("No se puede obtener 1", !abb_obtener(arbol, uno));
	print_test("1 No pertenece al ABB", !abb_pertenece(arbol, uno));
	
	abb_destruir(arbol);
	free(uno);
}

void abb_pruebas_algunos_elementos(){
	printf("\nPRUEBAS ALGUNOS ELEMENTOS\n\n");

	char* uno = strdup("1");
	char* dos = strdup("2");
	char* tres = strdup("3");

	abb_t* arbol = abb_crear(strcmp, free);

	print_test("Guardo dos", abb_guardar(arbol, dos, dos));
	print_test("Cantidad es igual a 1", abb_cantidad(arbol) == 1);
	print_test("Dos pertenece al ABB", abb_pertenece(arbol, dos));
	print_test("Obtener dos es dos", abb_obtener(arbol, dos) == dos);

	print_test("Guardo uno", abb_guardar(arbol, uno, uno));
	print_test("La cantidad es igual a 2", abb_cantidad(arbol) == 2);
	print_test("Uno pertenece al ABB", abb_pertenece(arbol, uno));
	print_test("Obtener uno es uno", abb_obtener(arbol, uno) == uno);

	print_test("Guardo tres", abb_guardar(arbol , tres, tres));
	print_test("La cantidad es igual a 3", abb_cantidad(arbol) == 3);
	print_test("Tres pertenece al ABB",abb_pertenece(arbol, tres));
	print_test("Obtener tres es igual a tres", abb_obtener(arbol, tres) == tres);

	abb_destruir(arbol);
}


void abb_borrar_raiz(){
	printf("\nPrueba borrar ABB con unico elemento\n\n");
	
	char* uno = strdup("1");
	abb_t* arbol = abb_crear(strcmp, NULL);
	
	print_test("Guardo uno", abb_guardar(arbol, uno, uno));
	print_test("Borrar uno es igual a uno", abb_borrar(arbol, uno) == uno);
	print_test("La cantidad es igual a 0", abb_cantidad(arbol) == 0);
	print_test("Uno no pertenece", !abb_pertenece(arbol, uno));
	print_test("No se puede obtener uno", !abb_obtener(arbol, uno));

	abb_destruir(arbol);
	free(uno);
}

void abb_borrar_raiz_un_hijo(){
	printf("\nPrueba borrando raiz con un hijo\n\n");
	
	char* uno = strdup("1");
	char* dos = strdup("2");
	abb_t* arbol = abb_crear(strcmp, NULL);
	
	print_test("Guardo 1", abb_guardar(arbol, uno, uno));
	print_test("Guardo 2", abb_guardar(arbol, dos, dos));
	print_test("La cantidad es igual a ", abb_cantidad(arbol) == 2);

	print_test("Borrar 1 devuelve 1", abb_borrar(arbol, uno) == uno);
	print_test("1 no pertence al ABB", !abb_pertenece(arbol, uno));
	print_test("No se puede obtener 1", !abb_obtener(arbol, uno));
	print_test("La cantidad es 1", abb_cantidad(arbol) == 1);

	print_test("Borrar dos devuelve dos", abb_borrar(arbol, dos) == dos);
	print_test("La cantidad es 0", abb_cantidad(arbol) == 0);
	
	abb_destruir(arbol);
	free(uno);
	free(dos);
}

void abb_borrar_raiz_dos_hijos(){
	printf("\nPrueba borrando raiz con dos hijos\n\n");
	
	char* uno = strdup("1");
	char* dos = strdup("2");
	char* tres = strdup("3");
	abb_t* arbol = abb_crear(strcmp, NULL);

	print_test("Guardo dos", abb_guardar(arbol, dos, dos));
	print_test("Guardo uno", abb_guardar(arbol, uno, uno));
	print_test("Guardo tres", abb_guardar(arbol,tres, tres));
	print_test("La cantidad es igual a 3",abb_cantidad(arbol) == 3);

	print_test("Borrar dos devuelve dos", abb_borrar(arbol, dos) == dos);
	print_test("La cantidad es 2", abb_cantidad(arbol) == 2);
	print_test("Dos no pertenece al ABB", !abb_pertenece(arbol, dos));
	print_test("No se puede obtener dos", !abb_obtener(arbol, dos));

	print_test("Borrar uno devuelve uno", abb_borrar(arbol, uno) == uno);
	print_test("La cantidad es igual a 1", abb_cantidad(arbol) == 1);
	print_test("Borrar tres devuelve tres", abb_borrar(arbol, tres) == tres);
	print_test("La cantidad es 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
	free(uno);
	free(dos);
	free(tres);
}

void abb_borrar_hoja(){
	printf("\nPruebas abb borrar hoja\n\n");
	
	char* uno = strdup("1");
	char* dos = strdup("2");
	char* tres = strdup("3");
	abb_t* arbol = abb_crear(strcmp, NULL);

	print_test("Guardo 2", abb_guardar(arbol, dos, dos));
	print_test("Guardo 1", abb_guardar(arbol, uno, uno));
	print_test("Guardo 3", abb_guardar(arbol, tres, tres));
	print_test("La cantidad es igual a 3", abb_cantidad(arbol) == 3);
	
	print_test("Borrar 3 devuelve 3", abb_borrar(arbol, tres) == tres);
	print_test("3 no pertenece al ABB", !abb_pertenece(arbol, tres));
	print_test("La cantidad es 2", abb_cantidad(arbol) == 2);
	print_test("No se puede obtener 3", !abb_obtener(arbol, tres));

	print_test("Borrar 1 devuelve 1", abb_borrar(arbol, uno) == uno);
	print_test("La cantidad es 1", abb_cantidad(arbol) ==1);
	print_test("1 no pertence al ABB", !abb_pertenece(arbol, uno));
	print_test("No se puede obtener 1", !abb_obtener(arbol, uno));

	print_test("Borrar 2 devuelve 2", abb_borrar(arbol, dos) == dos);
	print_test("La cantidad es 0", abb_cantidad(arbol) == 0);
	print_test("2 no pertenece al ABB", !abb_pertenece(arbol, dos));
	
	abb_destruir(arbol);
	free(uno);
	free(dos);
	free(tres);
}

void abb_borrar_hijo_izq(){
	printf("\nPrueba ABB borrar nodo con hijo izq\n\n");
	
	char* dos = strdup("2");
	char* tres = strdup("3");
	char* cuatro = strdup("4");
	abb_t* arbol = abb_crear(strcmp, NULL);

	print_test("Guardo 4", abb_guardar(arbol, cuatro, cuatro));
	print_test("Guardo 3", abb_guardar(arbol, tres, tres));
	print_test("Guardo 2", abb_guardar(arbol, dos, dos));
	print_test("La cantidad es igual a 3", abb_cantidad(arbol) == 3);

	print_test("Borrar 3 devuelve 3", abb_borrar(arbol, tres) == tres);
	print_test("3 no pertenece al ABB", !abb_pertenece(arbol, tres));
	print_test("No se puede obtener 3", !abb_obtener(arbol, tres));
	print_test("La cantidad es 2", abb_cantidad(arbol) == 2);

	print_test("Borrar 2 devuelve 2", abb_borrar(arbol, dos) == dos);
	print_test("Borrar 4 devuelve 4", abb_borrar(arbol, cuatro) == cuatro);
	print_test("La cantidad es igual a 0", abb_cantidad(arbol) == 0);
	
	abb_destruir(arbol);
	free(dos);
	free(tres);
	free(cuatro);
}

void abb_borrar_hijo_der(){
	printf("\nPruebas ABB borrar nodo con hijo derecho\n\n");

	char* dos = strdup("2");
	char* tres = strdup("3");
	char* cinco = strdup("5");
	abb_t* arbol = abb_crear(strcmp, NULL);

	print_test("Guardo 2", abb_guardar(arbol, dos, dos));
	print_test("Guardo 3", abb_guardar(arbol, tres, tres));
	print_test("Guardo 5", abb_guardar(arbol, cinco, cinco));
	print_test("La cantidad es igual a 3", abb_cantidad(arbol) == 3);

	print_test("Borrar 3 devuelve 3", abb_borrar(arbol, tres) == tres);
	print_test("3 no pertenece al ABB", !abb_pertenece(arbol, tres));
	print_test("No se puede obtener 3", !abb_obtener(arbol, tres));
	print_test("La cantidad es igual a 2", abb_cantidad(arbol) == 2);

	print_test("Borrar 5 devuelve 5", abb_borrar(arbol, cinco) == cinco);
	print_test("borrar 2 devuelve 2", abb_borrar(arbol,dos) == dos);
	print_test("La cantidad es igual a 0", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
	free(dos);
	free(tres);
	free(cinco);
}



void abb_borrar_dos_hijos(){
	printf("\nPruebas ABB borrar nodo con dos hijos\n\n");
	
	char* dos = strdup("2");
	char* tres = strdup("3");
	char* cuatro = strdup("4");
	char* cinco = strdup("5");
	abb_t* arbol = abb_crear(strcmp, NULL);

	print_test("Guardo dos", abb_guardar(arbol, dos, dos));
	print_test("Guardo cuatro", abb_guardar(arbol, cuatro, cuatro));
	print_test("Guardo tres", abb_guardar(arbol, tres, tres));
	print_test("Guardo cinco", abb_guardar(arbol, cinco, cinco));
	print_test("La cantidad es igual a 4", abb_cantidad(arbol) == 4);

	print_test("Borrar cuatro devuelve 4", abb_borrar(arbol, cuatro) == cuatro);
	print_test("4 no pertence al ABB", !abb_pertenece(arbol, cuatro));
	print_test("No se puede obtener 4", !abb_obtener(arbol, cuatro));
	print_test("La cantidad es igual a 3", abb_cantidad(arbol) == 3);

	print_test("Borrar 3 devuelve 3", abb_borrar(arbol, tres) == tres);
	print_test("3 no pertence al ABB", !abb_pertenece(arbol, tres));
	print_test("No se puede obtener 3", !abb_obtener(arbol, tres));
	print_test("La cantidad es igual a 2", abb_cantidad(arbol) == 2);

	print_test("Borrar 2 devuelve 2", abb_borrar(arbol, dos) == dos);
	print_test("2 no pertence al ABB", !abb_pertenece(arbol, dos));
	print_test("No se puede obtener 2", !abb_obtener(arbol, dos));
	print_test("La cantidad es igual a 1", abb_cantidad(arbol) == 1);

	print_test("Borrar 5 devuelve 5", abb_borrar(arbol, cinco) == cinco);
	print_test("5 no pertence al ABB", !abb_pertenece(arbol, cinco));
	print_test("No se puede obtener 5", !abb_obtener(arbol, cinco));
	print_test("La cantidad es igual a 0", abb_cantidad(arbol) == 0);


	abb_destruir(arbol);
	free(dos);
	free(tres);
	free(cuatro);
	free(cinco);
}

bool imprimir_claves(const char* clave,void* dato, void* extra){
	printf("%s\n",clave);
	return true;
}

void abb_pruebas_iter_interno(){
	printf("\nPruebas iterador interno\n\n");
	
	char* uno = strdup("1");
	char* dos = strdup("2");
	char* tres = strdup("3");
	char* cuatro = strdup("4");
	abb_t* arbol = abb_crear(strcmp, free);

	abb_guardar(arbol, uno, uno);
	abb_guardar(arbol, dos, dos);
	abb_guardar(arbol, tres, tres);
	abb_guardar(arbol, cuatro, cuatro);

	abb_in_order(arbol, imprimir_claves, NULL);

	abb_destruir(arbol);
}

void abb_pruebas_iter_externo(){
	printf("\nPruebas iterador externo \n\n");
	
	char* uno = strdup("1");
	char* dos = strdup("2");
	char* tres = strdup("3");
	char* cuatro = strdup("4");
	char* cinco = strdup("5");
	abb_t* arbol = abb_crear(strcmp, free);

	abb_guardar(arbol, uno, uno);
	abb_guardar(arbol, dos, dos);
	abb_guardar(arbol, tres, tres);
	abb_guardar(arbol, cuatro, cuatro);
	abb_guardar(arbol, cinco, cinco);

	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("El iterador se creó correctamente", iter);

	print_test("Ver actual es 1", !strcmp(abb_iter_in_ver_actual(iter),uno)); //strcmp = 0 si son iguales -> !strcmp = true si strcmp = 0
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));

	print_test("Ver actual es 2", !strcmp(abb_iter_in_ver_actual(iter), dos));
	print_test("Avano el iterador", abb_iter_in_avanzar(iter));

	print_test("Ver actual es 3", !strcmp(abb_iter_in_ver_actual(iter), tres));
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));

	print_test("Ver actual es 4", !strcmp(abb_iter_in_ver_actual(iter), cuatro));
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));

	print_test("Ver actual es 5", !strcmp(abb_iter_in_ver_actual(iter), cinco));
	print_test("Avanzo el iterador", abb_iter_in_avanzar(iter));

	print_test("El iterador está al final", abb_iter_in_al_final(iter));
	print_test("No puedo avanzar el iterador", !abb_iter_in_avanzar(iter));
	print_test("Ver actual es NULL", !abb_iter_in_ver_actual(iter));

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
}

bool abb_insertar_con_propiedad(abb_t* arbol, char** claves, unsigned** valores, int ini, int fin){
	if(ini > fin){
		return true;
	}
	int medio = (ini + fin) / 2;
	if(!abb_guardar(arbol, claves[medio], valores[medio])){
		return false;
	}
	if(!abb_insertar_con_propiedad(arbol, claves, valores, ini, medio - 1)){
		return false;
	}

	return abb_insertar_con_propiedad(arbol, claves, valores, medio + 1, fin);
}

void abb_pruebas_volumen(size_t largo, bool debug){
	abb_t* arbol = abb_crear(strcmp, NULL);
	size_t largo_claves = 10;
    char** claves = malloc(sizeof(char*) * largo);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el ABB */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        claves[i] = malloc(sizeof(char) * largo_claves);
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }

    ok = abb_insertar_con_propiedad(arbol, claves, valores, 0, (int)largo - 1);

    if (debug) print_test("Prueba ABB almacenar muchos elementos", ok);
    if (debug) print_test("Prueba ABB la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(arbol, claves[i]);
        if (!ok) break;
        ok = abb_obtener(arbol, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba ABB pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba ABB la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(arbol, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba ABB borrar muchos elementos", ok);
    if (debug) print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    /* Destruye el ABB y crea uno nuevo que sí libera */
    abb_destruir(arbol);
    arbol = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el ABB */
    ok = true;
    abb_insertar_con_propiedad(arbol, claves, valores, 0, (int)largo - 1);
    for(size_t i = 0; i < largo; i++){
    	free(claves[i]);
    }
    free(claves);

    /* Destruye el ABB - debería liberar los enteros */
    abb_destruir(arbol);

}


void pruebas_abb_alumno(){
	printf("PRUEBAS INSERTAR\n");
	abb_pruebas_vacio();
	abb_pruebas_unitarias();
	abb_pruebas_algunos_elementos();
	printf("PRUEBAS BORRAR\n");
	abb_borrar_raiz();
	abb_borrar_raiz_un_hijo();
	abb_borrar_raiz_dos_hijos();
	abb_borrar_hoja();
	abb_borrar_hijo_izq();
 	abb_borrar_hijo_der();
 	abb_borrar_dos_hijos();
	printf("PRUEBAS ITERADORES\n");
	abb_pruebas_iter_interno();
	abb_pruebas_iter_externo();
	printf("\n\n PRUEBAS DE VOLUMEN\n");
	abb_pruebas_volumen(100000, true);
}
