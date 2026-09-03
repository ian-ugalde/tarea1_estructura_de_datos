#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"

// coloca un nodo ya creado en su lugar correcto
static void insertarOrdenado(Reserva **lista, Reserva *nuevo) {
    if (*lista == NULL || nuevo->prioridad > (*lista)->prioridad) {
        nuevo->siguiente = *lista;
        *lista = nuevo;
        return;
    } buscamos el lugar correcto recorriendo la lista
    Reserva *actual = *lista;
    while (actual->siguiente != NULL &&
           actual->siguiente->prioridad >= nuevo->prioridad) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

//prioridad es estandar
void registrarGrupo(Reserva **lista, char *id, int personas) {
    Reserva *nuevo = (Reserva *) malloc(sizeof(Reserva));
    if (nuevo == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;
    }

    strncpy(nuevo->id, id, sizeof(nuevo->id) - 1);
    nuevo->id[sizeof(nuevo->id) - 1] = '\0';
    nuevo->personas = personas;
    nuevo->prioridad = ESTANDAR;
    nuevo->hora_registro = time(NULL);
    nuevo->siguiente = NULL;


    //se inserta en su posicion que corresponde
    insertarOrdenado(lista, nuevo);
    printf("Grupo '%s' registrado con exito.\n", id);
}


//cambia la prioridad de un grupo
void asignarPrioridad(Reserva **lista, char *id, Prioridad nuevaPrioridad) {
    Reserva *actual = *lista;
    Reserva *anterior = NULL;

    // buscamos el nodo con ese id
    while (actual != NULL && strcmp(actual->id, id) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Aviso: no se encontro ningun grupo con id '%s'.\n", id);
        return;
    }
    if (anterior == NULL) {
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    actual->prioridad = nuevaPrioridad;
    actual->siguiente = NULL;
    insertarOrdenado(lista, actual);

    printf("Prioridad de '%s' actualizada correctamente.\n", id);
}


void mostrarListaEspera(Reserva *lista) {
    if (lista == NULL) {
        printf("No hay grupos en la lista de espera.\n");
        return;
    }

    printf("----- Lista de espera -----\n");

    Reserva *actual = lista;
    int posicion = 1;


    //ponemos nombre a los casos de prioridad
    while (actual != NULL) {
        char *nombrePrioridad;
        switch (actual->prioridad) {
            case VIP:
                nombrePrioridad = "VIP";
                break;
            case GRUPO_GRANDE:
                nombrePrioridad = "Grupo Grande";
                break;
            default:
                nombrePrioridad = "Estandar";
                break;
        }
        printf("%d. %s | Personas: %d | Prioridad: %s | Hora: %s",
               posicion, actual->id, actual->personas,
               nombrePrioridad, ctime(&actual->hora_registro));

        actual = actual->siguiente;
        posicion++;
    }
}


void asignarMesa(Reserva **lista) {
    if (*lista == NULL) {
        printf("Aviso: no hay grupos pendientes por asignar mesa.\n");
        return;
    }
    Reserva *siguienteGrupo = *lista;
    char *nombrePrioridad;
    switch (siguienteGrupo->prioridad) {
        case VIP:
            nombrePrioridad = "VIP";
            break;
        case GRUPO_GRANDE:
            nombrePrioridad = "Grupo Grande";
            break;
        default:
            nombrePrioridad = "Estandar";
            break;
    }

    printf("----- Mesa asignada -----\n");
    printf("ID/Nombre: %s\n", siguienteGrupo->id);
    printf("Personas: %d\n", siguienteGrupo->personas);
    printf("Prioridad: %s\n", nombrePrioridad);
    printf("Hora de registro: %s", ctime(&siguienteGrupo->hora_registro));

    *lista = siguienteGrupo->siguiente;
    free(siguienteGrupo);
}


//busca una reserva por id y muestra sus datos si existe
void buscarReserva(Reserva *lista, char *id) {
    Reserva *actual = lista;

    while (actual != NULL && strcmp(actual->id, id) != 0) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Error: no existe ninguna reserva con id '%s'.\n", id);
        return;
    }

    char *nombrePrioridad;
    switch (actual->prioridad) {
        case VIP:
            nombrePrioridad = "VIP";
            break;
        case GRUPO_GRANDE:
            nombrePrioridad = "Grupo Grande";
            break;
        default:
            nombrePrioridad = "Estandar";
            break;
    }

    printf("----- Reserva encontrada -----\n");
    printf("ID/Nombre: %s\n", actual->id);
    printf("Personas: %d\n", actual->personas);
    printf("Prioridad: %s\n", nombrePrioridad);
    printf("Hora de registro: %s", ctime(&actual->hora_registro));
}


// Libera toda la memoria
void liberarLista(Reserva **lista) {
    Reserva *actual = *lista;
    Reserva *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *lista = NULL;
}