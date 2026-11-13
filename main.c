// Módulo principal contiene menú y flujo general del algoritmo.
#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

#define MAX_HIST 20

int main() {
    double hist_angulos[MAX_HIST]; // ARREGLO para guardar historial de simulaciones
    int total = 0;                 // Contador de elementos almacenados en el arreglo
    int opcion;
    
    do {
        // Interfaz interactiva y coherente con el escenario.
        printf("\n======================================================\n");
        printf(" SIMULADOR MISIONES ARTEMIS - ESCENARIO 4 (REINGRESO) \n");
        printf("\n======================================================\n");
        printf("1. Iniciar simulacion\n");
        printf("2. Ver historial de angulos probados (%d/%d)\n", total, MAX_HIST);
        printf("0. Salir\n");
        printf("======================================================\n");

        opcion = leer_entero("Seleccione una opcion: ", 0, 2);

        switch (opcion) {
            case 1:
                if (total < MAX_HIST) {
                    ParametrosReingreso sim = ejecutar_simulacion(); // Recibe la ficha estructurada
                    hist_angulos[total] = sim.angulo;              // Almacena en el arreglo usando acceso directo
                    total++;
                    printf("\n[Simulacion guardada exitosamente en el historial]\n");
                } else {
                    printf("\n[Aviso] El historial de simulaciones esta lleno (%d/%d).\n", MAX_HIST, MAX_HIST);
                }
                break;
                
            case 2:
                printf("\n--- HISTORIAL DE ANGULOS DE REINGRESO ---\n");
                if (total == 0) {
                    printf("No hay simulaciones registradas todavia.\n");
                } else {
                    for (int i = 0; i < total; i++) {
                        printf("%d) Angulo registrado: %.2f grados\n", i + 1, hist_angulos[i]);
                    }
                }
                break;
                
            case 0:
                mostrar_reporte_final(hist_angulos, total);
                printf("\nSaliendo del simulador de la Mision Artemis. ¡Hasta luego!\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
