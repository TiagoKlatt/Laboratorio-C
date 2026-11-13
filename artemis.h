// Módulo de Cabecera: Declaración de constantes, definición de tipos estructurados.
#ifndef ARTEMIS_H
#define ARTEMIS_H

#define MASA_ORION 10400.0 // Masa del módulo Orion en kg . Constante
#define GRAVEDAD 9.80
// Restricciones de dominio del mundo real para el angulo de reingreso
#define ANG_MIN 5.5
#define ANG_MAX 7.0
// Estructura de datos para representar entidades y estados. 
typedef struct {
    double vel_ini; // 11000.0 m/s - Velocidad inicial.
    double alt_ini; // 120000.0 m - Altura inicial.
    double vel_para; // 25.0 m/s - No es final genérico, es momento paracaídas.
    double alt_para; // 2500.0 m - Desplegar los paracaídas.
    double v_impacto; // 8.0 m/s - Impacto de amerizaje.
    double t_freno;
    double hundimiento;
    double angulo_reingreso;
} ParametrosReingreso;

void inicializar_parametros(ParametrosReingreso *simulacion);
void calcular_trabajo_rozamiento(const ParametrosReingreso *simulacion);
void calcular_desaceleracion_media(const ParametrosReingreso *simulacion);
void calcular_fuerza_amerizaje(const ParametrosReingreso *simulacion);
void analizar_angulo_reingreso(const ParametrosReingreso *simulacion);
ParametrosReingreso ejecutar_simulacion(void); // Retorna la estructura para el historial

#endif