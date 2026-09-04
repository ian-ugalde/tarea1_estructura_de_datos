# tarea1_estructura_de_datos

# Sistema de Gestión de Lista de Espera para Restaurante

## Descripción

Este sistema permite gestionar la lista de espera en un 
restaurante durante horas de alta demanda, mediante una cola de prioridad 
implementada como Tipo de Dato Abstracto (TDA) sobre una lista enlazada. 
Los usuarios pueden registrar nuevos grupos, modificar su nivel de 
prioridad, asignar mesa al siguiente grupo según corresponda, buscar una 
reserva por ID/Nombre, y consultar la lista de espera pendiente. Esta 
herramienta busca organizar de forma eficiente la atención de los 
clientes, priorizando según su categoría (VIP, Grupo Grande, Estándar) y
según su orden de llegada.

## Cómo compilar y ejecutar

Este sistema fue desarrollado en lenguaje C y puede ejecutarse en Replit o en cualquier equipo con un compilador de C instalado (como gcc).

**En Replit:**

1. Abre el proyecto en Replit.
2. Presiona el botón "Run" ubicado en la parte superior.
3. Replit compilará automáticamente los archivos `main.c`, `reserva.c` y `reserva.h`, y ejecutará el programa en la consola.

**Si no llega a funcionar**

Compila el programa con el siguiente comando en la shell:

`gcc main.c reserva.c list.c -o listaespera`


Ejecuta el programa con:

`./listaespera`


## Funcionalidades

**Funcionando correctamente:**

- Registrar un nuevo grupo con nombre/ID y cantidad de personas, quedando con prioridad "Estándar" y hora de registro actual.
- Asignar o modificar el nivel de prioridad de un grupo existente (VIP, Grupo Grande, Estándar).
- Mostrar la lista de espera ordenada por prioridad y, dentro de la misma prioridad, por orden de llegada.
- Asignar mesa al grupo con mayor prioridad (y más antiguo dentro de su nivel), eliminándolo de la lista.
- Buscar una reserva por ID/Nombre y mostrar sus datos completos.
- Manejo de errores: avisos cuando se busca o modifica un ID inexistente, y cuando se intenta asignar mesa sin grupos pendientes.

**Problemas conocidos:**

- Al reasignar la prioridad de un grupo, este pasa a ubicarse al final del bloque a su nueva prioridad, sin respetar estrictamente su hora de registro original respecto a los demás grupos que ya se encontraban en ese nivel, esto puede modificar el orden de llegada dentro de una misma categoría cuando se producen cambios de prioridad
- No se toma en cuenta cuando alguien utiliza un tipo de dato no esperado, es decir si se utiliza un string cuando se pide la cantidad el programa no lo acepta y resulta en error.

**A mejorar:**

- Actualmente el ID/Nombre no valida que no se repita entre distintos grupos.
- Se podría agregar una opción para editar la cantidad de personas de un grupo ya registrado.
- Se puede comprobar que los datos ingresados por el usuario sean del tipo esperado (string, int, etc...)

## Ejemplo de uso

**Paso 1: Registrar un nuevo grupo**

Se registra un grupo que acaba de llegar al restaurante.
```
1) Registrar grupo
Ingrese ID/Nombre: Familia Gonzalez
Ingrese cantidad de personas: 4
```

El sistema registra a "Familia Gonzalez" con prioridad inicial "Estándar" y guarda la hora actual de registro.

**Paso 2: Asignar prioridad a un cliente**

El grupo indica que tiene una reserva VIP, por lo que se actualiza su prioridad.
```
`2) Asignar prioridad a cliente`
`Ingrese ID/Nombre: Familia Gonzalez`

VIP
Grupo Grande
Estandar
Ingrese opcion: 1
```
El sistema actualiza la prioridad de "Familia Gonzalez" a "VIP", ubicándolo al inicio de la lista de espera.

**Paso 3: Mostrar la lista de espera**
```
3) Mostrar lista de espera

----- Lista de espera -----
1. Familia Gonzalez | Personas: 4 | Prioridad: VIP | Hora: 00:00
```
La lista muestra a "Familia Gonzalez" en primer lugar, dado su nivel de prioridad VIP.


**Paso 4: Buscar una reserva existente**
El usuario quiere verificar los datos de un grupo ya registrado. 
``` 
5) Buscar reserva por id 

Ingrese ID/Nombre: Familia Gonzalez 

----- Reserva encontrada ----- 
ID/Nombre: Familia Gonzalez 
Personas: 4 
Prioridad: VIP 
Hora de registro: 00:00 
``` 
El sistema muestra los datos completos de "Familia Gonzalez": cantidad de personas, prioridad y hora de registro.

**Paso 5: Asignar mesa al siguiente grupo**
```
4) Asignar mesa al siguiente grupo

----- Mesa asignada -----
ID/Nombre: Familia Gonzalez
Personas: 4
Prioridad: VIP
Hora de registro: 00:00
```
El sistema asigna mesa a "Familia Gonzalez" (por ser el de mayor prioridad), muestra sus datos y lo elimina de la lista de espera.


**Paso 6: Manejo de errores**

Si se ingresa un ID/Nombre que no existe (por ejemplo, al buscar o al 
asignar prioridad), el sistema muestra un aviso indicando que no se 
encontró ninguna reserva con ese identificador. De la misma forma, si 
se intenta asignar mesa cuando no hay grupos pendientes, el sistema 
informa que no hay grupos en espera.

**Paso 7: Salir del sistema**

`6) Salir`


El sistema libera toda la memoria reservada por los nodos de la lista 
y finaliza la ejecución, mostrando el mensaje `"Saliendo del sistema...".`