#ifndef RESERVA_H
#define RESERVA_H

#include <time.h>

typedef enum {
    ESTANDAR = 0,
    GRUPO_GRANDE = 1,
    VIP = 2
} Prioridad;
//TDA lista enlazada simple (reserva)
typedef struct Reserva {
    char id[50];
    int personas;
    Prioridad prioridad;
    time_t hora_registro;
    struct Reserva *siguiente;
} Reserva;

void registrarGrupo(Reserva **lista, char *id, int personas);
void asignarPrioridad(Reserva **lista, char *id, Prioridad nuevaPrioridad);
void mostrarListaEspera(Reserva *lista);
void asignarMesa(Reserva **lista);
void buscarReserva(Reserva *lista, char *id);
void liberarLista(Reserva **lista);

#endif