#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DatosEnergia {
    char tipodeenergia[100];
    double consumo;
};

void agregarDatos(FILE *archivo) {
    struct DatosEnergia nuevoDato;
    printf("Ingrese el tipo de energia: ");
    scanf("%s", nuevoDato.tipodeenergia);
    printf("Ingrese el consumo de energía: ");
    scanf("%lf", &nuevoDato.consumo);

    fprintf(archivo, "%s %.2lf\n", nuevoDato.tipodeenergia, nuevoDato.consumo);

    printf("Datos agregados correctamente.\n");
}

void mostrarDatos(FILE *archivo) {
    printf("Distribución de energía de la red eléctrica española:\n");
    struct DatosEnergia dato;

    while (fscanf(archivo, "%s %lf", dato.tipodeenergia, &dato.consumo) == 2) {
        printf("tipo de energia: %s, Consumo: %.2lf\n", dato.tipodeenergia, dato.consumo);
    }
}

int main() {
    int opcion;
    FILE *archivo = fopen("datos_energia.txt", "a+");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        printf("1. Agregar datos\n");
        printf("2. Mostrar datos\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarDatos(archivo);
                break;
            case 2:
                mostrarDatos(archivo);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);

    fclose(archivo);

    return 0;
}

