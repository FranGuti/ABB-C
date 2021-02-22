# TDA ABB
Es un trabajo realizado durante la cursada de Algoritmos y Programación II.
El mismo consta de la implementación y desarrollo del Tipo de Dato Abstracto Árbol Binario de Búsqueda en el lenguaje de programación C. 
Tiene como objetivo la creación del mismo para posterior uso como librería con un correcto manejo de memoria, la implementación de un iterador propio que sea capaz de recorrerlo, y sus métodos :

 - ABB Crear
     > Crea y devuelve un Árbol Binario de Búsqueda vacía

 - ABB Guardar
    >Recibe una clave, un valor y lo guarda en el Árbol, si la clave ya se encuentra en la tabla reemplaza el valor de la misma
    
 - ABB Borrar
    >Borra el elemento del Árbol y devuelve el valor asociado
    
 - ABB Obtener
   > Devuelve el valor asociado a la clave pasada por parámetro siempre que la clave se encuentre en el Árbol
 
 - ABB Pertenece
   > Devuelve True si el elemento está en el Árbol, False en caso contario

 - ABB Cantidad
   > Devuelve la cantidad de elementos que hay en el Árbol

- ABB Destruir
  >Destruye el Árbol Binario de Búsqueda
  

El Árbol Binario de Búsqueda es un tipo de estructura para almacenar datos del tipo clave-valor. La particularidad de estos, a diferencia de cualquier Árbol, es que tienen la capacidad de, al guardar un elemento, ubicarlo de manera tal que los elementos pertenecientes al sub-árbol izquierdo sean menores a su padre y los pertenecientes al sub-árbol derecho sean mayores a su padre como se ve en la imagen (cuando la regla está invertida, es decir, los hijos izquierdos son los mayores y los derechos los menores, el ABB se llama izquierdista)

![enter image description here](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/280px-Binary_search_tree.svg.png)


¿Para que nos sirve?

El interés de los Árboles Binarios de Búsqueda radica en el recorrido InOrden (también incluido como método aparte del TDA en este trabajo) que proporciona los elementos ordenados de forma ascendente. Y en que la búsqueda de algún elemento suele ser muy eficiente.

Recorrido In-Orden se basa en la aplicación del algoritmo:

 

 1. Atravesar el sub-árbol izquierdo
 2. Visitar la raíz
 3. Atravesar el sub-árbol derecho
