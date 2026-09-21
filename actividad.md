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
  root((Álgebra Lineal: SVD y PCA))
    SVD - Descomposición en Valores Singulares
      Estructura Matemática A = U S V^T
        U y V: Matrices Ortogonales
        S: Valores Singulares S_1 >= S_2 >= ... >= S_N >= 0
      Propiedades Teóricas
        Rango de la Matriz: Cantidad de valores singulares no nulos
        Número de Condición: Razón entre el mayor y menor valor singular
      Algoritmos Numéricos de Cálculo
        Golub-Reinsch General
        Golub-Reinsch Modificado para M >> N
        Ortogonalización Unilateral de Jacobi
    Teoría de Compresión e Información
      Ponderación de Energía
        Suma Total D = sum(d_i)
        Ponderado Individual p_i = d_i / D
      Criterio del 95% de Información
        Suma Acumulada P_N = sum_N(p_i) = 0.95
      Aproximación de Rango Bajo
        Matriz Truncada con N Términos Principales
      Análisis Espectral
        Comportamiento y Decaimiento Lineal, Algebraico o Exponencial
    PCA - Análisis de Componentes Principales
      Reducción de Dimensionalidad
        Maximización de la Varianza Explicada
      Transformaciones y Proyecciones
        Distribuciones Gaussianas 2D centradas en cero
        Transformación mediante Matrices de Proyección
      Análisis de Datos
        Aplicación a Tablas de Atributos (sol_objects.ods)
```
