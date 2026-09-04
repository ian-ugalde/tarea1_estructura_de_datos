#ifndef RESERVA_H
#define RESERVA_H
#include <time.h>
#include "list.h"

typedef enum {
    ESTANDAR = 0,
    GRUPO_GRANDE = 1,
    VIP = 2
} Prioridad;

typedef struct Reserva {
    char id[50];
    int personas;
    Prioridad prioridad;
    time_t hora_registro;
} Reserva;

void registrarGrupo(List *lista, char *id, int personas);
void asignarPrioridad(List *lista, char *id, Prioridad nuevaPrioridad);
void mostrarListaEspera(List *lista);
void asignarMesa(List *lista);
void buscarReserva(List *lista, char *id);
void liberarLista(List *lista);

#endif