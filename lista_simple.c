#include "lista_simple.h"


//Funciones para nodo
Nodo* crearNodo(void *dato, size_t size){
    Nodo*nuevo;
    nuevo=(Nodo*)malloc(sizeof(Nodo));
    if(nuevo!=NULL){
        nuevo->siguiente=NULL;
        nuevo->dato=malloc(size);
        memcpy(nuevo->dato, dato, size);
    }
    return nuevo;
}

void borrarNodo(Nodo*n){
    if(n->siguiente==NULL){
        free(n);
    }
}

bool modificarNodo(Nodo*n, void *d, size_t size){
    if(n!=NULL){
        memcpy(n->dato, d, size);
    }
}

// Crear / estado
Lista* crearLista(){
    Lista *l=(Lista*)malloc(sizeof(Lista));
    if(l!=NULL){
        l->head=NULL;
        l->tail=NULL;
    }
    return l;
}

bool esVacia(Lista* lista){
    return lista->head==NULL;
}

// Inserciones
void insertarInicio(Lista* lista, void* dato, size_t size){
    Nodo*nuevo;
    nuevo=crearNodo(dato, size);
    lista->head=lista->tail=nuevo;      
}

void insertarFinal(Lista* lista, void* dato, size_t size){
    Nodo*nuevo;
    nuevo=crearNodo(dato, size);
    lista->tail->siguiente=nuevo;
    lista->tail=nuevo;
    nuevo->siguiente=NULL;
}

void insertarPorPosicion(Lista* lista, void* dato, size_t size, int pos){
    Nodo*nuevo;
    if(esvacia(lista)){
        return;
    }
    int total=0;
    for(Nodo*tmp=lista->head; tmp!=NULL; tmp=tmp->siguiente){
        total++;
    }
    if(pos==0){
        insertarInicio(lista, dato, size);
    }else if(pos==total){
        insertarFinal(lista, dato, size);        
    }else if(pos>=1 && pos<total){
        Nodo*anterior=lista->head;
        for(int i=0; i<pos-1; i++){
            anterior=anterior->siguiente;
        }
        nuevo->siguiente=anterior->siguiente;
        anterior->siguiente=nuevo;
    }else{
        printf("La posición no es válida\n");
    }
}

// Eliminaciones
void eliminarInicio(Lista* lista){
    Nodo*tmp;
    tmp=lista->head;
    lista->head=lista->head->siguiente;
    tmp->siguiente=NULL;
    borrarNodo(tmp);
}

void eliminarFinal(Lista* lista){
    Nodo*tmp=lista->tail;
    Nodo*tmp2=lista->head;
    for( ;tmp2->siguiente!=lista->tail; tmp2=tmp2->siguiente);
    tmp2->siguiente=NULL;
    lista->tail=tmp2;
}

void eliminarPorPosicion(Lista* lista, int pos){
    if(lista->head==NULL){
        printf("La lista esta vacía\n");
        return;
    }
    if(pos==0){
        eliminarInicio(lista);
        return;
    }
    Nodo* anterior=lista->head;
    Nodo* actual;
    for(int i=0; i<pos-1 && anterior->siguiente!=NULL; i++){
        anterior=anterior->siguiente;
    }
    if(anterior->siguiente==NULL){
        printf("Posición no válida\n");
        return;
    }
    actual=anterior->siguiente;
    anterior->siguiente=actual->siguiente;
    if(actual==lista->tail){
        lista->tail=anterior;
    }
    actual->siguiente=NULL;
    borrarNodo(actual);
}

void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp){
    if(lista->head==NULL){
        return;
    }
    Nodo*actual=lista->head;
    Nodo*anterior=NULL;
    while(actual!=NULL){
        if(cmp(actual->dato, dato)==0){
            if(anterior==NULL){
                lista->head=actual->siguiente;
            }else{
                anterior->siguiente=actual->siguiente;
            }
            if(actual==lista->tail){
                lista->tail=anterior;

            }
            actual->siguiente=NULL;
            borrarNodo(actual);
            return;
        }
        anterior=actual;
        actual=actual->siguiente;
    }
}

void eliminarElementosIguales(Lista* lista, void* dato, CompararFunc cmp){
    Nodo* actual = lista->head;
    Nodo* anterior = NULL;

    while(actual != NULL){
        if(cmp(actual->dato, dato) == 0){

            Nodo* tmp = actual;

            if(anterior == NULL){
                lista->head = actual->siguiente;
                actual = lista->head;
            } else {
                anterior->siguiente = actual->siguiente;
                actual = actual->siguiente;
            }

            if(tmp == lista->tail){
                lista->tail = anterior;
            }

            tmp->siguiente = NULL;
            borrarNodo(tmp);

        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

//Busquedas
void* buscarPorPosicion(Lista* lista, int pos){
    if(lista->head == NULL){
        return NULL;
    }

    Nodo* actual = lista->head;
    int i = 0;

    while(actual != NULL){
        if(i == pos){
            return actual->dato;
        }
        actual = actual->siguiente;
        i++;
    }
    return NULL; 
}

int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp){
    Nodo* actual = lista->head;
    int pos = 0;

    while(actual != NULL){
        if(cmp(actual->dato, dato) == 0){
            return pos;
        }
        actual = actual->siguiente;
        pos++;
    }

    return -1; 
}

//Navegación
Nodo* primero(Lista* lista){
    return lista->head;
}

Nodo* ultimo(Lista* lista){
    return lista->tail;
}

Nodo* siguiente(Nodo* actual){
    if(actual==NULL) return NULL;
    return actual->siguiente;
}

//Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size){
    Nodo* actual=lista->head;
    int i=0;
    while(actual!=NULL){
        if(i==pos){
            memcpy(actual->dato, dato, size);
            return;
        }
        actual=actual->siguiente;
        i++;
    }
    printf("Posición no válida\n");
}

//Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir){
    Nodo* actual = lista->head;

    while(actual != NULL){
        imprimir(actual->dato);
        actual = actual->siguiente;
    }

    printf("\n");
}

void vaciarLista(Lista* lista){
    Nodo* actual = lista->head;

    while(actual != NULL){
        Nodo* tmp = actual;
        actual = actual->siguiente;

        tmp->siguiente = NULL;
        borrarNodo(tmp);
    }

    lista->head = NULL;
    lista->tail = NULL;
}

void borrarLista(Lista* lista){
    vaciarLista(lista);
    free(lista);
}

