#include <stdio.h>
#include <string.h>

#define MAX_PERSONAS 100

// Estructura de datos
struct Persona {
    int id;
    char nombre[30];
};

// Prototipos de funciones
void crearPersona(struct Persona personas[], int *n);
void leerPersonas(const struct Persona personas[], int n);
void eliminarPersona(struct Persona personas[], int *n);
void limpiarBuffer();

int main() {
    struct Persona personas[MAX_PERSONAS];
    int n = 0;
    int opcion;

    do {
        printf("\n=== SISTEMA DE GESTION DE PERSONAS ===\n");
        printf("1. Crear Persona\n");
        printf("2. Leer Lista\n");
        printf("3. Eliminar Persona\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Por favor, ingrese un numero valido.\n");
            limpiarBuffer();
            continue;
        }

        switch(opcion) {
            case 1:
                crearPersona(personas, &n);
                break;
            case 2:
                leerPersonas(personas, n);
                break;
            case 3:
                eliminarPersona(personas, &n);
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 4);

    return 0;
}

// --- Implementacion de Funciones ---

void crearPersona(struct Persona personas[], int *n) {
    if (*n >= MAX_PERSONAS) {
        printf("Error: Memoria llena. No se pueden agregar mas personas.\n");
        return;
    }

    printf("\n--- Crear Persona ---\n");
    printf("ID: ");
    scanf("%d", &personas[*n].id);
    
    printf("Nombre: ");
    limpiarBuffer(); // Evita problemas con espacios o saltos de linea anteriores
    fgets(personas[*n].nombre, sizeof(personas[*n].nombre), stdin);
    personas[*n].nombre[strcspn(personas[*n].nombre, "\n")] = 0; // Remueve el salto de linea de fgets

    (*n)++;
    printf("¡Persona registrada con exito!\n");
}

void leerPersonas(const struct Persona personas[], int n) {
    printf("\n--- Lista de Personas ---\n");
    if (n == 0) {
        printf("No hay registros en el sistema.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        printf("[%d] ID: %d | Nombre: %s\n", i + 1, personas[i].id, personas[i].nombre);
    }
}

void eliminarPersona(struct Persona personas[], int *n) {
    int id, encontrado = 0;

    printf("\n--- Eliminar Persona ---\n");
    if (*n == 0) {
        printf("No hay registros para eliminar.\n");
        return;
    }

    printf("Ingrese el ID a eliminar: ");
    scanf("%d", &id);

    for(int i = 0; i < *n; i++) {
        if(personas[i].id == id) {
            // Desplazar los elementos hacia la izquierda
            for(int j = i; j < *n - 1; j++) {
                personas[j] = personas[j + 1];
            }
            (*n)--;
            encontrado = 1;
            printf("Registro con ID %d eliminado correctamente.\n", id);
            break;
        }
    }

    if(!encontrado) {
        printf("Error: ID %d no encontrado.\n", id);
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
