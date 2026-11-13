# Laboratorio-C — Simulador Misión Artemis (Escenario 4)

## Integrantes y Comisión

- **Universidad:** Universidad Tecnológica Nacional - Facultad Regional Resistencia (UTN FRR)
- **Carrera:** Ingeniería en Sistemas de Información
- **Asignatura:** Algoritmos y Estructuras de Datos
- **Comisión:** K1.4

## Equipo de Desarrollo

- **Barreto, Yamila Elisa** — Legajo: `31168`
- **Klatt, Tiago David** — Legajo: `27866`
- **Villalba, Luciano Alberto** — Legajo: `27843`
- **[Apellido, Nombre]** — Legajo: `12345`
- **[Apellido, Nombre]** — Legajo: `12345`

---

## Contexto de Desarrollo

Tras varias reuniones de planificación y diseño por Google Meet, como equipo definimos la hoja de ruta para abordar el **Escenario 4 de la misión Artemis**. Durante estos encuentros analizamos el problema, las ecuaciones físicas involucradas y la mejor manera de organizar el desarrollo.

A partir de ese trabajo, acordamos utilizar una estructura modular en lenguaje C, distribuyendo las responsabilidades para facilitar el desarrollo, las pruebas y la integración de cada parte del sistema.

A continuación se presenta la arquitectura propuesta, las decisiones técnicas y la organización del equipo para llevar adelante el proyecto.

---

## Enfoque del Proyecto

Este proyecto propone desarrollar un simulador interactivo en lenguaje C basado en el **Escenario 4 de la misión Artemis**, que representa el retorno hiperveloz del módulo tripulado Orion a la Tierra.

El principal desafío consiste en traducir las ecuaciones de conservación de energía y dinámica de impacto a un programa estructurado, garantizando que sea robusto ante errores de usuario, fácil de mantener y sencillo de comprender y defender técnicamente.

Para evitar un único archivo difícil de depurar, planteamos una **arquitectura modular de adentro hacia afuera**, separando las responsabilidades en archivos fuente (`.c`) y de cabecera (`.h`). La organización seguirá un orden progresivo: primero se definirán las estructuras de datos y las restricciones físicas, luego se desarrollarán las validaciones de entrada, después el motor de cálculo y, finalmente, se integrará todo mediante un menú interactivo con historial de ejecuciones.

## Estructura y Organización del Proyecto

### 1. El contrato del sistema: `artemis.h`

Este archivo establecerá la base común del simulador. Mediante directivas `#define`, se centralizarán las constantes físicas y las restricciones del escenario, evitando dejar valores numéricos dispersos en el código.

Las constantes principales serán:

- `MASA_ORION`: `10400.0` kg.
- `GRAVEDAD`: `9.80` m/s².
- `ANG_MIN`: `5.5`° (límite inferior de entrada atmosférica).
- `ANG_MAX`: `7.0`° (límite superior de entrada atmosférica).

También se definirá la estructura `ParametrosReingreso`, que permitirá agrupar toda la información de una simulación (`vel_ini`, `alt_ini`, `vel_para`, `alt_para`, `vel_agua`, `t_freno`, `hundimiento` y `angulo`), evitando pasar múltiples variables sueltas entre funciones.

Se utilizarán nombres descriptivos en español en lugar de abreviaturas cortas, como `v_i` o `h_i`, y se mantendrá el nombre `simulacion` para los punteros que reciban las funciones. De esta manera, se buscará que el código sea más claro y fácil de seguir.

### 2. El control de entradas: `validaciones.h` y `validaciones.c`

Este módulo tendrá la responsabilidad de controlar los datos ingresados por el usuario y evitar errores durante la ejecución.

En C, un `scanf` sin controles adecuados puede provocar problemas cuando se ingresan letras en lugar de números o quedan caracteres pendientes en el búfer de entrada (`stdin`).

Para evitar estas situaciones, se desarrollarán tres funciones:

- **`limpiar_buffer()`**: consumirá y descartará los caracteres sobrantes de `stdin` hasta encontrar un salto de línea o el fin de archivo (`EOF`).
- **`leer_entero()`**: controlará la lectura de las opciones del menú principal.
- **`leer_flotante()`**: permitirá ingresar los parámetros físicos, verificando que sean valores numéricos y se encuentren dentro de los rangos permitidos.

Ambas funciones de lectura utilizarán `limpiar_buffer()` tanto cuando la lectura sea correcta como cuando se produzca un error, evitando que los datos pendientes afecten las siguientes operaciones.

### 3. El motor físico y la lógica de simulación: `artemis.c`

Este archivo concentrará los cálculos físicos y la lógica principal del simulador. El flujo estará coordinado por `ejecutar_simulacion()`, que creará una variable local de tipo `ParametrosReingreso`, llamada `simulacion`, y pasará su dirección de memoria (`&simulacion`) a cinco funciones especializadas.

Las funciones previstas serán:

- **`inicializar_parametros(ParametrosReingreso *simulacion)`**: recibirá un puntero con permiso de escritura para cargar las condiciones iniciales de la misión: reingreso a `11.000,0 m/s` desde `120.000,0 m` de altitud, apertura de paracaídas a `25,0 m/s` y `2.500,0 m`, e impacto en el océano a `8,0 m/s`. Luego solicitará al usuario las tres variables dinámicas del experimento: tiempo de frenado (`t_freno`), profundidad de hundimiento (`hundimiento`) y ángulo de entrada (`angulo`).

- **`calcular_trabajo_rozamiento(const ParametrosReingreso *simulacion)`**: calculará la energía mecánica inicial y final, considerando la energía cinética y potencial gravitatoria. A partir de su diferencia se obtendrá el trabajo negativo realizado por la resistencia aerodinámica (`W_roz`), expresado en Joules.

- **`calcular_desaceleracion_media(const ParametrosReingreso *simulacion)`**: determinará la desaceleración promedio durante el frenado atmosférico en `m/s²` y su equivalente en fuerzas `g`, permitiendo representar la exigencia física sobre la tripulación.

- **`calcular_fuerza_amerizaje(const ParametrosReingreso *simulacion)`**: aplicará el teorema del trabajo y la energía durante el impacto contra el agua. Considerará la energía cinética de impacto y el trabajo del peso durante el hundimiento, calculando la fuerza promedio ejercida por el agua en Newtons y su relación respecto al peso de la nave.

- **`analizar_angulo_reingreso(const ParametrosReingreso *simulacion)`**: evaluará el ángulo ingresado respecto a `ANG_MIN` y `ANG_MAX`. Si supera los `7,0°`, advertirá sobre una desaceleración excesiva por una entrada demasiado empinada; si es inferior a `5,5°`, alertará sobre un posible rebote atmosférico. Si se mantiene dentro del intervalo, indicará que la trayectoria se encuentra dentro de la ventana de seguridad.

Las funciones que solamente necesiten consultar los datos recibirán punteros constantes (`const`), para proteger la integridad de la información almacenada.

Al finalizar, `ejecutar_simulacion()` devolverá la estructura completa por valor, permitiendo conservar los parámetros utilizados en cada ejecución.

### 4. La integración y el historial de ejecuciones: `main.c`

Este archivo será el encargado de integrar los módulos y gestionar el funcionamiento general del programa mediante un menú interactivo, controlado a través de `leer_entero()`.

Para permitir comparaciones entre distintos ensayos, se utilizará un arreglo estático:

`double hist_angulos[MAX_HIST]`

Junto con un contador `total`, que permitirá llevar el registro de las simulaciones realizadas.

Cada vez que se complete una simulación, `main.c` recibirá la estructura devuelta por `ejecutar_simulacion()` y almacenará el ángulo utilizado (`sim.angulo`) en la siguiente posición disponible del arreglo `hist_angulos[total]`.

De esta manera, el usuario podrá realizar diferentes pruebas con distintos ángulos de reingreso y consultar posteriormente el historial acumulado desde la segunda opción del menú.

## Organización del Equipo y División de Tareas

Para trabajar en paralelo en GitHub y evitar conflictos al integrar los archivos, se propone distribuir las responsabilidades según la cantidad de integrantes.

### Equipo de 4 integrantes

1. **Arquitectura de datos (`artemis.h`):** definición de constantes físicas, límites del escenario, estructura `ParametrosReingreso` y prototipos de funciones.
2. **Validaciones e interfaz de entrada (`validaciones.h` / `validaciones.c`):** desarrollo de las funciones de lectura segura y limpieza del búfer, junto con pruebas de entradas incorrectas y valores fuera de rango.
3. **Motor de simulación (`artemis.c`):** implementación de los cálculos físicos, manejo de punteros constantes y presentación de resultados en consola.
4. **Integración y documentación (`main.c` y `README.md`):** desarrollo del menú principal, gestión del historial, integración de los módulos y documentación técnica del repositorio.

### Equipo de 5 integrantes

Se mantendrán los cuatro roles anteriores y se incorporará un quinto integrante como responsable de **Aseguramiento de Calidad (QA) y Control de Versiones**.

Su tarea será diseñar casos de prueba, contrastar los resultados físicos mediante una calculadora científica, revisar los *Pull Requests* antes de integrarlos en la rama `main`, gestionar el archivo `.gitignore` y coordinar la grabación y demostración técnica del sistema.

## Compilación y Ejecución

El proyecto se desarrollará utilizando el estándar C99/C11 y la biblioteca matemática `<math.h>`. Para compilar con GCC en Linux o Unix será necesario enlazar dicha biblioteca mediante el parámetro `-lm`.

**Compilación:**

```bash
gcc main.c artemis.c validaciones.c -o simulador_artemis -lm
```

**Ejecución desde la terminal:**

```bash
# Windows (CMD / PowerShell)
simulador_artemis.exe

# Linux / macOS
./simulador_artemis
```

## Uso de Inteligencia Artificial

Durante la planificación y el desarrollo del proyecto se contempla utilizar herramientas de Inteligencia Artificial Generativa (Gemini y ChatGPT) como apoyo técnico y de consulta.

Su utilización estará orientada principalmente a los siguientes aspectos:

- **Legibilidad y nomenclatura:** consultar alternativas para nombrar variables y punteros, priorizando identificadores descriptivos como `vel_ini`, `simulacion`, `ec_ini` y `f_agua`, en lugar de abreviaturas poco claras.
- **Control de entradas y búfer:** analizar el comportamiento de `scanf` ante entradas no numéricas y evaluar soluciones mediante funciones específicas como `limpiar_buffer()`.
- **Presentación de resultados:** consultar propuestas para mejorar la organización visual, el espaciado y la claridad de los reportes de salida en consola.

Las sugerencias obtenidas serán evaluadas y adaptadas según las necesidades del proyecto. Las decisiones de implementación, la comprensión del código y la verificación de los resultados estarán a cargo del equipo.
