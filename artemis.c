// Módulo de Lógica (artemis.c): Implementará los algoritmos de simulación y cálculos físicos del reingreso.
// Contendrá la inicialización de parámetros de la nave Orión y las funciones de cálculo de
// trabajo por rozamiento, desaceleración media, fuerza de amerizaje y análisis del ángulo de reingreso.
// Servirá como controlador principal de la simulación mediante ejecutar_simulacion().

#include <stdio.h>
#include <math.h>
#include "artemis.h"

// Valores base preestablecidos para el reingreso de la nave 
void inicializar_parametros(ParametrosReingreso *simulacion) {
    simulacion->vel_ini = 11000.0;     // Velocidad hiperveloz inicial (m/s)
    simulacion->alt_ini = 120000.0;    // Altitud inicial de reingreso (m)
    simulacion->vel_para = 25.0;       // Rapidez en el momento de despliegue de paracaídas (m/s)
    simulacion->alt_para = 2500.0;     // Altitud de despliegue de paracaídas (m)
    simulacion->v_impacto = 8.0;       // Rapidez final segura al amerizar (m/s)
    
    // Lectura de parámetros variables mediante validaciones
    printf("\n--- Configuracion de Parametros de Reingreso ---\n");
    simulacion->t_freno = leer_flotante("Ingrese duracion de desaceleracion en seg (ej. 400.0): ", 1.0, 10000.0);
    simulacion->hundimiento = leer_flotante("Ingrese hundimiento en el agua en metros (ej. 1.50): ", 0.1, 100.0);
    simulacion->angulo_reingreso = leer_flotante("Ingrese angulo de reingreso en grados (ej. 6.0): ", 0.0, 90.0);
}

void calcular_trabajo_rozamiento(const ParametrosReingreso *simulacion) {
    double ec_ini = 0.5 * MASA_ORION * pow(simulacion->vel_ini, 2);
    double ep_ini = MASA_ORION * GRAVEDAD * simulacion->alt_ini;
    double ec_fin = 0.5 * MASA_ORION * pow(simulacion->vel_para, 2);
    double ep_fin = MASA_ORION * GRAVEDAD * simulacion->alt_para;
    
    double w_roz = (ec_fin + ep_fin) - (ec_ini + ep_ini);
    
    printf("\na. Trabajo total por rozamiento (Wroz): %.2e Joules\n", w_roz);

}

void calcular_desaceleracion_media(const ParametrosReingreso *simulacion) {
    double decel = fabs((simulacion->vel_para - simulacion->vel_ini) / simulacion->t_freno);
    double decel_g = decel / GRAVEDAD;
    
    printf("b. Desaceleracion media: %.2f m/s^2  (%.2f g)\n", decel, decel_g);
  
}








// Función controladora principal que instancia el estado e invoca los cálculos
void ejecutar_simulacion() {
    
    ParametrosReingreso simulacion;

    inicializar_parametros(&simulacion);
    calcular_trabajo_rozamiento(&simulacion);
    calcular_desaceleracion_media(&simulacion);

    return simulacion; // Retorna la estructura para registrarla en el historial del main
}