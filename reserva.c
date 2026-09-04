#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"


static int tienePrioridadMayor(void *data1, void *data2) {
    Reserva *r1 = (Reserva *) data1;
    Reserva *r2 = (Reserva *) data2;

    if (r1->prioridad != r2->prioridad) {
        return r1->prioridad > r2->prioridad; // mayor prioridad primero
    }
    //el que llegó antes va primero
    return r1->hora_registro < r2->hora_registro;
}

// registra gente en la lista de espera
void registrarGrupo(List *lista, char *id, int personas) {
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

    list_sortedInsert(lista, nuevo, tienePrioridadMayor);
    printf("Grupo '%s' registrado con exito.\n", id);
}

// cambia la prioridad de un grupo
void asignarPrioridad(List *lista, char *id, Prioridad nuevaPrioridad) {
    Reserva *actual = (Reserva *) list_first(lista);

    while (actual != NULL && strcmp(actual->id, id) != 0) {
        actual = (Reserva *) list_next(lista);
    }

    if (actual == NULL) {
        printf("Aviso: no se encontro ningun grupo con id '%s'.\n", id);
        return;
    }
    list_popCurrent(lista);

    // actualizamos su prioridad
    actual->prioridad = nuevaPrioridad;
    list_sortedInsert(lista, actual, tienePrioridadMayor);

    printf("Prioridad de '%s' actualizada correctamente.\n", id);
}

void mostrarListaEspera(List *lista) {
    if (list_size(lista) == 0) {
        printf("No hay grupos en la lista de espera.\n");
        return;
    }

    printf("----- Lista de espera -----\n");

    Reserva *actual = (Reserva *) list_first(lista);
    int posicion = 1;

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

        actual = (Reserva *) list_next(lista);
        posicion++;
    }
}
void asignarMesa(List *lista) {
    if (list_size(lista) == 0) {
        printf("Aviso: no hay grupos pendientes por asignar mesa.\n");
        return;
    }

    Reserva *siguienteGrupo = (Reserva *) list_popFront(lista);

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

    free(siguienteGrupo);
}
void buscarReserva(List *lista, char *id) {
    Reserva *actual = (Reserva *) list_first(lista);

    while (actual != NULL && strcmp(actual->id, id) != 0) {
        actual = (Reserva *) list_next(lista);
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

// Libera toda la memoria de las Reservas y limpia la lista
void liberarLista(List *lista) {
    Reserva *actual = (Reserva *) list_first(lista);
    while (actual != NULL) {
        free(actual);
        actual = (Reserva *) list_next(lista);
    }
    list_clean(lista);
}