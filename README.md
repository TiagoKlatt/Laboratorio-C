# Laboratorio-C

### 👥 Integrantes y Comisión

* **Universidad:** Universidad Tecnológica Nacional - Facultad Regional Resistencia (UTN FRR)
* **Carrera:** Ingeniería en Sistemas de Información
* **Asignatura:** Algoritmos y Estructuras de Datos
* **Comisión:** k1.4

### Equipo de Desarrollo:
* **[Apellido, Nombre]** — Legajo: `[12345]` 
* **[Apellido, Nombre]** — Legajo: `[12345]`
* **Klatt, Tiago David** — Legajo: `27866`
* **Villalba, Luciano Alberto** — Legajo: `27843`

---

## 🛰️ Escenario 4: Reingreso Atmosférico, Frenado Aerodinámico y Amerizaje

### Descripción del Escenario
Este proyecto implementa la **Situación - Problema 4: Reingreso Atmosférico, Frenado Aerodinámico y Amerizaje**.
El sistema simula el reingreso del módulo de tripulación Orion ($m = 10.400,0$ kg) a la atmósfera terrestre a una velocidad hiperveloz de $11.000,0$ m/s a $120$ km de altitud. Calcula la disipación de energía cinética mediante el rozamiento del aire, la desaceleración media experimentada por la tripulación, la fuerza de impacto durante el amerizaje en el Océano Pacífico y analiza la ventana de seguridad del ángulo de reingreso.

---

##  Detalle de Funcionamiento y Arquitectura

El sistema está modularizado en múltiples archivos para separar la lógica física de la interfaz de usuario, utilizando estructuras de datos y punteros para el paso por referencia:

* **`artemis.h` (Cabeceras y Estructuras):** Define constantes globales (MASA_ORION, GRAVEDAD). Declara la estructura `ParametrosReingreso` (que agrupa velocidades, altitudes, tiempos y ángulos) y los prototipos de las funciones públicas.
* **`validaciones.c / .h` (Validación robusta):** Contiene la función `leer_flotante()` que garantiza el ingreso seguro de datos numéricos. Implementa limpieza del buffer de teclado (`getchar()`) para prevenir bucles infinitos ante ingresos de caracteres inválidos.
* **`artemis.c` (Lógica y Física):** Implementa el motor de la simulación. Utiliza punteros a la estructura `ParametrosReingreso` para operar sobre los datos (ej. `simulacion->vel_ini`). Incluye funciones para calcular el trabajo por rozamiento, la desaceleración (fuerzas G), la fuerza promedio de impacto en el agua y el análisis del ángulo de reingreso.
* **`main.c` (Punto de Entrada):** Inicializa el flujo del programa mediante un menú interactivo en consola gestionado por un bloque `do-while` y `switch`.
