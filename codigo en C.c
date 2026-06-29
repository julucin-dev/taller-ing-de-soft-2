#include <stdio.h>
#include <string.h>

#define MAX_PERSONAS 100

struct Persona {
    int id;
    char nombre[30];
};

// Prototipos
void crearPersona(struct Persona personas[], int *n);
void leerPersonas(const struct Persona personas[], int n);
void actualizarPersona(struct Persona personas[], int n);
void eliminarPersona(struct Persona personas[], int *n);
int buscarPorId(const struct Persona personas[], int n, int id);
void buscarPersonaMenu(const struct Persona personas[], int n);
void limpiarBuffer();

int main() {
    struct Persona personas[MAX_PERSONAS];
    int n = 0;
    int opcion;

    do {
        printf("\n=== SISTEMA DE GESTION DE PERSONAS ===\n");
        printf("1. Crear Persona\n");
        printf("2. Leer Lista\n");
        printf("3. Modificar Persona\n");
        printf("4. Eliminar Persona\n");
        printf("5. Buscar Persona por ID\n");
        printf("6. Mostrar cantidad de personas registradas\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Por favor, ingrese un numero valido.\n");
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1:
                crearPersona(personas, &n);
                break;

            case 2:
                leerPersonas(personas, n);
                break;

            case 3:
                actualizarPersona(personas, n);
                break;

            case 4:
                eliminarPersona(personas, &n);
                break;

            case 5:
                buscarPersonaMenu(personas, n);
                break;

            case 6:
                printf("\nTotal de personas registradas: %d\n", n);
                break;

            case 7:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

    } while (opcion != 7);

    return 0;
}

int buscarPorId(const struct Persona personas[], int n, int id) {

    for (int i = 0; i < n; i++) {
        if (personas[i].id == id) {
            return i;
        }
    }

    return -1;
}

void crearPersona(struct Persona personas[], int *n) {

    if (*n >= MAX_PERSONAS) {
        printf("Error: Memoria llena.\n");
        return;
    }

    int nuevoId;

    printf("\n--- Crear Persona ---\n");
    printf("ID: ");
    scanf("%d", &nuevoId);

    if (buscarPorId(personas, *n, nuevoId) != -1) {
        printf("Ya existe una persona con ese ID.\n");
        return;
    }

    personas[*n].id = nuevoId;

    printf("Nombre: ");
    limpiarBuffer();

    fgets(personas[*n].nombre,
          sizeof(personas[*n].nombre),
          stdin);

    personas[*n].nombre[strcspn(personas[*n].nombre, "\n")] = '\0';

    (*n)++;

    printf("Persona registrada con exito.\n");
}

void leerPersonas(const struct Persona personas[], int n) {

    printf("\n--- Lista de Personas ---\n");

    if (n == 0) {
        printf("No hay registros.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("[%d] ID: %d | Nombre: %s\n",
               i + 1,
               personas[i].id,
               personas[i].nombre);
    }
}

void actualizarPersona(struct Persona personas[], int n) {

    int id, indice;

    printf("\n--- Modificar Persona ---\n");

    if (n == 0) {
        printf("No hay registros para modificar.\n");
        return;
    }

    printf("Ingrese el ID de la persona a modificar: ");
    scanf("%d", &id);

    indice = buscarPorId(personas, n, id);

    if (indice != -1) {

        printf("Datos actuales -> ID: %d | Nombre: %s\n",
               personas[indice].id,
               personas[indice].nombre);

        printf("Ingrese el nuevo nombre: ");

        limpiarBuffer();

        fgets(personas[indice].nombre,
              sizeof(personas[indice].nombre),
              stdin);

        personas[indice].nombre[strcspn(personas[indice].nombre, "\n")] = '\0';

        printf("Registro actualizado correctamente.\n");

    } else {

        printf("ID no encontrado.\n");
    }
}

void eliminarPersona(struct Persona personas[], int *n) {

    int id, indice;

    printf("\n--- Eliminar Persona ---\n");

    if (*n == 0) {
        printf("No hay registros para eliminar.\n");
        return;
    }

    printf("Ingrese el ID a eliminar: ");
    scanf("%d", &id);

    indice = buscarPorId(personas, *n, id);

    if (indice != -1) {

        for (int j = indice; j < *n - 1; j++) {
            personas[j] = personas[j + 1];
        }

        (*n)--;

        printf("Registro eliminado correctamente.\n");

    } else {

        printf("ID no encontrado.\n");
    }
}

void buscarPersonaMenu(const struct Persona personas[], int n) {

    int id, indice;

    printf("\n--- Buscar Persona por ID ---\n");

    if (n == 0) {
        printf("No existen registros.\n");
        return;
    }

    printf("Ingrese el ID a buscar: ");
    scanf("%d", &id);

    indice = buscarPorId(personas, n, id);

    if (indice != -1) {

        printf("\nRegistro encontrado\n");
        printf("ID: %d\n", personas[indice].id);
        printf("Nombre: %s\n", personas[indice].nombre);

    } else {

        printf("La persona no existe.\n");
    }
}

void limpiarBuffer() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}