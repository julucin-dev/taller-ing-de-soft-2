#include <stdio.h>

struct Persona {
    int id;
    char nombre[30];
};

int main() {
    struct Persona personas[100];
    int n = 0, opcion, id, i, encontrado;

    do {
        printf("\n1. Crear\n2. Leer\n3. Eliminar\n4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("ID: ");
                scanf("%d", &personas[n].id);
                printf("Nombre: ");
                scanf("%s", personas[n].nombre);
                n++;
                break;

            case 2:
                printf("\nLista de personas:\n");
                for(i = 0; i < n; i++)
                    printf("ID: %d - Nombre: %s\n",
                           personas[i].id,
                           personas[i].nombre);
                break;

            case 3:
                printf("ID a eliminar: ");
                scanf("%d", &id);
                encontrado = 0;

                for(i = 0; i < n; i++) {
                    if(personas[i].id == id) {
                        for(int j = i; j < n - 1; j++)
                            personas[j] = personas[j + 1];
                        n--;
                        encontrado = 1;
                        printf("Registro eliminado.\n");
                        break;
                    }
                }

                if(!encontrado)
                    printf("ID no encontrado.\n");
                break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 4);

    return 0;
}