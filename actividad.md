# Actividad #03 - Maching Learning
- Christian Marroquin
- Julian Medina
# actividad
- Generar descomposicion de valores singulares de una imagen de dimensiones (1920, 1080). Para luego eliminar los elementos menores que aporten menos del 5% a la suma de los valores singulares.
- Pasar el resultado anterior a otro grupo y recibir la descomposicion de otro grupo para reconstruir la imagen que descompusieron.
- Generar estadisticas para los valores singulares de las 6 imagenes adjuntas, para ver como decaen los valores singulares.
- Generar una nube de puntos 2D con distribusion gaussiana, luego aplicarle la siguiente matriz
Para ver la matriz en GitHub, escribe el bloque así:
$$
\begin{bmatrix}
1 & 2 \\
-1 & 0
\end{bmatrix}
$$
y aplicarle un analisis de componentes principales a la distribucion de punto final.
- Aplicarle el analisis de componentes principales a los datos en el archivo sol_objects.csv
- Construya un mapa mental del tema

```mermaid
mindmap
  root((Algebra Lineal: SVD y PCA))
    SVD - Descomposicion en Valores Singulares
      Estructura Matematica A = U S V^T
        U y V: Matrices Ortogonales
        S: Valores Singulares Mayores o Iguales a Cero
      Propiedades Teoricas
        Rango de la Matriz: Cantidad de valores no nulos
        Numero de Condicion: Razon entre mayor y menor valor
      Algoritmos Numericos de Calculo
        Golub-Reinsch General
        Golub-Reinsch Modificado
        Ortogonalizacion Unilateral de Jacobi
    Teoria de Compresion e Informacion
      Ponderacion de Energia
        Suma Total D
        Ponderado Individual pi = di / D
      Criterio del 95 por ciento de Informacion
        Suma Acumulada PN = 0.95
      Aproximacion de Rango Bajo
        Matriz Truncada con N Terminos Principales
      Analisis Espectral
        Comportamiento y Decaimiento Lineal o Exponencial
    PCA - Analisis de Componentes Principales
      Reduccion de Dimensionalidad
        Maximizacion de la Varianza Explicada
      Transformaciones y Proyecciones
        Distribuciones Gaussianas 2D centradas en cero
        Transformacion mediante Matrices de Proyeccion
      Analisis de Datos
        Aplicacion a Tablas de Atributos
```
