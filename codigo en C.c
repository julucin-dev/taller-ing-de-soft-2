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
void actualizarPersona(struct Persona personas[], int n);
void eliminarPersona(struct Persona personas[], int *n);
int buscarPorId(const struct Persona personas[], int n, int id);
void buscarPersonaMenu(const struct Persona personas[], int n); // <- TU NUEVA FUNCIÓN
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
        printf("4. Buscar Persona\n"); // <- TU NUEVA OPCION
        printf("5. Eliminar Persona\n");
        printf("6. Salir\n");
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
                actualizarPersona(personas, n);
                break;
            case 4:
                buscarPersonaMenu(personas, n); // <- LLAMADA A TU FUNCIÓN
                break;
            case 5:
                eliminarPersona(personas, &n);
                break;
            case 6:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 6);

    return 0;
}

// --- Implementacion de Funciones ---

// Función de apoyo para evitar repetir código de búsqueda
int buscarPorId(const struct Persona personas[], int n, int id) {
    for(int i = 0; i < n; i++) {
        if(personas[i].id == id) {
            return i; // Retorna el índice donde se encuentra
        }
    }
    return -1; // Retorna -1 si no existe
}

void crearPersona(struct Persona personas[], int *n) {
    if (*n >= MAX_PERSONAS) {
        printf("Error: Memoria llena. No se pueden agregar mas personas.\n");
        return;
    }

    int nuevoId;
    printf("\n--- Crear Persona ---\n");
    printf("ID: ");
    scanf("%d", &nuevoId);
    
    // Validación de ID duplicado utilizando la nueva función de búsqueda
    if (buscarPorId(personas, *n, nuevoId) != -1) {
        printf("Error: Ya existe una persona registrada con el ID %d.\n", nuevoId);
        return;
    }

    personas[*n].id = nuevoId;
    
    printf("Nombre: ");
    limpiarBuffer(); 
    fgets(personas[*n].nombre, sizeof(personas[*n].nombre), stdin);
    personas[*n].nombre[strcspn(personas[*n].nombre, "\n")] = 0; 

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

// NUEVA FUNCIÓN: Permite cambiar el nombre buscando al usuario por su ID
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
        printf("Datos actuales -> ID: %d | Nombre: %s\n", personas[indice].id, personas[indice].nombre);
        printf("Ingrese el NUEVO Nombre: ");
        limpiarBuffer();
        fgets(personas[indice].nombre, sizeof(personas[indice].nombre), stdin);
        personas[indice].nombre[strcspn(personas[indice].nombre, "\n")] = 0;
        
        printf("¡Registro actualizado con exito!\n");
    } else {
        printf("Error: ID %d no encontrado.\n", id);
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

    // Reutilizamos la función de búsqueda limpia
    indice = buscarPorId(personas, *n, id);

    if (indice != -1) {
        // Desplazar los elementos hacia la izquierda desde el índice hallado
        for(int j = indice; j < *n - 1; j++) {
            personas[j] = personas[j + 1];
        }
        (*n)--;
        printf("Registro con ID %d eliminado correctamente.\n", id);
    } else {
        printf("Error: ID %d no encontrado.\n", id);
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//Nueva Funcion: Buscar y mostrar los datos dde una personas especifica 
void buscarPersonaMenu(const struct Persona personas[], int n) {
    int id, indice;

    printf("\n--- Buscar Persona ---\n");
    if (n == 0) {
        printf("No hay registros en el sistema para buscar.\n");
        return;
    }

    printf("Ingrese el ID a buscar: ");
    scanf("%d", &id);

    // Reutilizas la función de tu compañero
    indice = buscarPorId(personas, n, id);

    if (indice != -1) {
        printf("¡Encontrado! -> ID: %d | Nombre: %s\n", personas[indice].id, personas[indice].nombre);
    } else {
        printf("Error: No existe ninguna persona registrada con el ID %d.\n", id);
    }
}
