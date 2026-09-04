#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#include "list.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Prioridad leerPrioridad() {
    int opcion;
    printf("1. VIP\n2. Grupo Grande\n3. Estandar\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();
    switch (opcion) {
        case 1: return VIP;
        case 2: return GRUPO_GRANDE;
        default: return ESTANDAR;
    }
}

int main() {
    List *lista = list_create();
    int opcion;
    char id[50];
    int personas;
    do {
        printf("\n===== Sistema de Lista de Espera =====\n");
        printf("1. Registrar grupo\n");
        printf("2. Asignar prioridad a cliente\n");
        printf("3. Mostrar lista de espera\n");
        printf("4. Asignar mesa al siguiente grupo\n");
        printf("5. Buscar reserva por id\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        switch (opcion) {
            case 1:
                printf("Ingrese ID/Nombre: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0';
                printf("Ingrese cantidad de personas: ");
                scanf("%d", &personas);
                limpiarBuffer();
                registrarGrupo(lista, id, personas);
                break;
            case 2:
                printf("Ingrese ID/Nombre: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0';
                Prioridad nueva = leerPrioridad();
                asignarPrioridad(lista, id, nueva);
                break;
            case 3:
                mostrarListaEspera(lista);
                break;
            case 4:
                asignarMesa(lista);
                break;
            case 5:
                printf("Ingrese ID/Nombre: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0';
                buscarReserva(lista, id);
                break;
            case 6:
                liberarLista(lista);
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 6);
    return 0;
}