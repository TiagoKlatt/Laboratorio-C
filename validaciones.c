// Módulo de Validaciones e Interfaz: Funciones dedicadas al ingreso seguro de datos.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "validaciones.h"

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // se descartan los caracteres sobrantes
    }
}

// Revisa el resto de la línea después de un número leído con scanf.
// Devuelve 1 si hay algo más que espacios (ej. "12abc" o "1,5"), y 0 si está limpia.
static int quedan_caracteres_extra(void) {
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');

    if (c == '\n' || c == EOF) {
        return 0;
    }
    limpiar_buffer();
    return 1;
}

int leer_entero(const char *mensaje, int min, int max) {
    int valor = 0;
    int leidos;
    int valido;

    do {
        printf("%s", mensaje);
        leidos = scanf("%d", &valor);

        if (leidos == EOF) {
            printf("\nEntrada finalizada. Cerrando el programa.\n");
            exit(EXIT_FAILURE);
        }

        if (leidos == 1) {
            valido = !quedan_caracteres_extra();
        } else {
            limpiar_buffer();
            valido = 0;
        }

        if (valido && (valor < min || valor > max)) {
            valido = 0;
        }

        if (!valido) {
            printf("Error: ingrese un numero entero entre %d y %d.\n", min, max);
        }
    } while (!valido);

    return valor;
}

double leer_flotante(const char *mensaje, double min, double max) {
    double valor = 0.0;
    int leidos;
    int valido;

    do {
        printf("%s", mensaje);
        leidos = scanf("%lf", &valor);

        if (leidos == EOF) {
            printf("\nEntrada finalizada. Cerrando el programa.\n");
            exit(EXIT_FAILURE);
        }

        if (leidos == 1) {
            valido = !quedan_caracteres_extra();
        } else {
            limpiar_buffer();
            valido = 0;
        }

        // isfinite descarta "nan" e "inf", que scanf acepta como números válidos
        if (valido && (!isfinite(valor) || valor < min || valor > max)) {
            valido = 0;
        }

        if (!valido) {
            printf("Error: ingrese un numero entre %.2f y %.2f (use punto como separador decimal).\n", min, max);
        }
    } while (!valido);

    return valor;
}
