// Módulo de Lógica (artemis.c): Implementará los algoritmos de simulación y cálculos físicos del reingreso.
// Contendrá la inicialización de parámetros de la nave Orión y las funciones de cálculo de
// trabajo por rozamiento, desaceleración media, fuerza de amerizaje y análisis del ángulo de reingreso.
// Servirá como controlador principal de la simulación mediante ejecutar_simulacion().

#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

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
    simulacion->angulo = leer_flotante("Ingrese angulo de reingreso en grados (ej. 6.0): ", 0.0, 90.0);
}

void calcular_trabajo_rozamiento(const ParametrosReingreso *simulacion) {
    double ec_ini = 0.5 * MASA_ORION * pow(simulacion->vel_ini, 2);
    double ep_ini = MASA_ORION * GRAVEDAD * simulacion->alt_ini;
    double ec_fin = 0.5 * MASA_ORION * pow(simulacion->vel_para, 2);
    double ep_fin = MASA_ORION * GRAVEDAD * simulacion->alt_para;
    
    double w_roz = (ec_fin + ep_fin) - (ec_ini + ep_ini);
    
    printf("\n\n======================================================\n");
    printf("         REPORTE DE RESULTADOS - FASE DE REINGRESO    \n");
    printf("======================================================\n\n");
    
    printf(" [1] Trabajo total por rozamiento (Wroz)\n");
    printf("     -> %.2e Joules\n\n", w_roz);
}

void calcular_desaceleracion_media(const ParametrosReingreso *simulacion) {
    double decel = fabs((simulacion->vel_para - simulacion->vel_ini) / simulacion->t_freno);
    double decel_g = decel / GRAVEDAD;
    
    printf(" [2] Desaceleracion media de frenado\n");
    printf("     -> %.2f m/s^2  (%.2f g)\n\n", decel, decel_g);
}

// Determinación de la fuerza promedio del agua sobre el módulo durante el impacto
void calcular_fuerza_amerizaje(const ParametrosReingreso *simulacion) {
    double ec_impacto = 0.5 * MASA_ORION * pow(simulacion->v_impacto, 2);
    double trabajo_peso = MASA_ORION * GRAVEDAD * simulacion->hundimiento;
    double f_agua = (ec_impacto + trabajo_peso) / simulacion->hundimiento;
    double peso = MASA_ORION * GRAVEDAD;

    printf(" [3] Fuerza promedio del agua (Amerizaje)\n");
    printf("     -> %.2f N  (%.2f veces el peso de la nave)\n\n", f_agua, f_agua / peso);
}

// Evaluación del ángulo de reingreso respecto a los límites de seguridad de la trayectoria
void analizar_angulo_reingreso(const ParametrosReingreso *simulacion) {
    printf(" [4] Analisis del angulo de reingreso (%.2f deg)\n", simulacion->angulo);
    printf("     -> Estado: ");
    
    if (simulacion->angulo > ANG_MAX) {
        printf("[ALERTA] Desaceleracion excesiva (superior a %.1f deg).\n", ANG_MAX);
    } else if (simulacion->angulo < ANG_MIN) {
        printf("[ALERTA] Rebote atmosferico (inferior a %.1f deg).\n", ANG_MIN);
    } else {
        printf("[ESTABLE] Dentro de la ventana de seguridad (%.1f - %.1f deg).\n", ANG_MIN, ANG_MAX);
    }
    
    printf("======================================================\n\n");
}





// Función controladora principal que instancia el estado e invoca los cálculos
ParametrosReingreso ejecutar_simulacion(void) {
    // Función controladora principal que instancia el estado e invoca los cálculos
    ParametrosReingreso simulacion;
    
    inicializar_parametros(&simulacion);
    calcular_trabajo_rozamiento(&simulacion);
    calcular_desaceleracion_media(&simulacion);
    calcular_fuerza_amerizaje(&simulacion);
    analizar_angulo_reingreso(&simulacion);
    return simulacion; // Retorna la estructura para registrarla en el historial del main
}


// Reporte final de desempeño: resume los ángulos probados en la sesión (arreglo recibido por puntero)
void mostrar_reporte_final(const double *hist_angulos, int total) {
    printf("\n======================================================\n");
    printf("            REPORTE FINAL DE DESEMPENO\n");
    printf("======================================================\n");

    if (total == 0) {
        printf(" No se realizaron simulaciones en esta sesion.\n");
        printf("======================================================\n");
        return;
    }

    double minimo = hist_angulos[0];
    double maximo = hist_angulos[0];
    double suma = 0.0;
    int seguros = 0;

    for (int i = 0; i < total; i++) {
        double angulo = hist_angulos[i];
        if (angulo < minimo) minimo = angulo;
        if (angulo > maximo) maximo = angulo;
        suma += angulo;
        if (angulo >= ANG_MIN && angulo <= ANG_MAX) seguros++;
    }

    printf(" Simulaciones realizadas  : %d\n", total);
    printf(" Angulo minimo / maximo   : %.2f / %.2f grados\n", minimo, maximo);
    printf(" Angulo promedio          : %.2f grados\n", suma / total);
    printf(" Dentro de ventana segura : %d de %d (%.1f%%)\n", seguros, total, 100.0 * seguros / total);
    printf("======================================================\n");
}