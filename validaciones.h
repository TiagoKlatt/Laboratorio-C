// Creo el ambiente para validaciones.c
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Formato que espera el sistema
double leer_flotante(const char *msg, double min, double max);
int leer_entero(const char *msg, int min, int max);
void limpiar_buffer(void);

#endif