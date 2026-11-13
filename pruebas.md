# Casos de prueba

| # | Qué se prueba | Entrada (en orden) | Resultado esperado |
|---|---|---|---|
| 1 | Caso exitoso | `1`, `400`, `1.5`, `6.0`, `0` | Wroz ≈ -6.41e+11 J; 27.44 m/s² (2.80 g); 323786.67 N (3.18 veces el peso); ángulo estable; reporte final con 1 simulación |
| 2 | Letras en el menú | `abc`, `0` | Error "entero entre 0 y 2" y vuelve a pedir |
| 3 | Opción fuera de rango | `7`, `0` | Error y vuelve a pedir |
| 4 | Letras en un flotante | `1`, `hola`, `400`, ... | Error y vuelve a pedir |
| 5 | `nan` | `1`, `nan`, `400`, ... | Error y vuelve a pedir |
| 6 | `inf` | `1`, `inf`, `400`, ... | Error y vuelve a pedir |
| 7 | Coma decimal | hundimiento `1,5` y luego `1.5` | Error con aviso de usar punto; después acepta `1.5` |
| 8 | Basura detrás del número | tiempo `12abc` y luego `400` | Error y vuelve a pedir |
| 9 | Tiempo fuera de rango | tiempo `0` y luego `400` | Error (rango 1 a 10000) |
| 10 | Ángulo fuera de rango | ángulo `120` y luego `90` | Error con 120; acepta 90 |
| 11 | Fin de entrada a mitad | `1`, `400`, cerrar entrada | "Entrada finalizada", termina sin colgarse |
| 12 | Ángulo 8.0 | `1`, `400`, `1.5`, `8`, `0` | Alerta: desaceleración excesiva; 0 de 1 en ventana segura |
| 13 | Ángulo 4.0 | igual con `4` | Alerta: rebote atmosférico |
| 14 | Dos simulaciones (4.0 y 6.0) | dos corridas y `0` | Reporte: 2 simulaciones, mín/máx 4.00/6.00, promedio 5.00, 1 de 2 (50.0%) |
| 15 | Salir sin simular | `0` | "No se realizaron simulaciones" |

Nota: una línea vacía (solo Enter) no genera error: `scanf` la ignora y sigue esperando un dato.