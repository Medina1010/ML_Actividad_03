import numpy as np
import matplotlib.pyplot as plt

# 1. Tus datos de prueba (Matriz de datos: Filas = Muestras, Columnas = Características)
X = np.loadtxt('../res/pca_data.csv', delimiter=',', skiprows=1);

# 2. Estandarizar los datos (Crucial: Restar la media y dividir por la desviación estándar)
X_mean = np.mean(X, axis=0)
X_std = np.std(X, axis=0)
X_scaled = (X - X_mean) / X_std

# 3. Aplicar SVD (Descomposición en Valores Singulares)
# Pasamos full_matrices=False para obtener la forma reducida
U, S, Vt = np.linalg.svd(X_scaled, full_matrices=False)

# 4. Seleccionar el número de componentes (por ejemplo, n_components = 2)
n_components = 2
X_pca = U[:, :n_components] * S[:n_components]

# 5. Calcular la varianza explicada (para saber cuánto aporta cada componente)
variance_explained = (S ** 2) / (len(X) - 1)
total_variance = np.sum(variance_explained)
variance_ratio = variance_explained / total_variance

# --- RESULTADOS ---
print("--- Datos reducidos (Nuevas Coordenadas PC1 y PC2) ---")
print(X_pca)

print("\n--- Porcentaje de Varianza Explicada por componente ---")
for i, ratio in enumerate(variance_ratio[:n_components]):
    print(f"PC{i+1}: {ratio * 100:.2f}%")

plt.plot(X_pca[:,0],X_pca[:,1], 'o' )
plt.plot(Vt[0,0] * 2,Vt[1,0] * 2, 'o', label = 'edad')
plt.plot(Vt[0,1] * 2,Vt[1,1] * 2, 'o', label = 'estatura')
plt.plot(Vt[0,2] * 2,Vt[1,2] * 2, 'o', label = 'nota')
plt.plot(Vt[0,3] * 2,Vt[1,3] * 2, 'o', label = 'hermanos')
plt.plot(Vt[0,4] * 2,Vt[1,4] * 2, 'o', label = 'peso')
plt.legend();

print(X[8])
print(X[18])

for idx, (xi, yi) in enumerate(zip(X_pca[:,0], X_pca[:,1])):
    # Los argumentos son: texto_a_mostrar, (coordenadas_del_punto)
    plt.annotate(
        str(idx), 
        (xi, yi),
        textcoords="offset points", # Sistema de coordenadas relativo al punto
        xytext=(0, 8),              # Desplazamiento (0 pixeles horizontal, 8 vertical)
        ha='center',                # Alineación horizontal: centrado
        fontsize=9,                 # Tamaño de la letra
        fontweight='bold'           # Negrita para mejor lectura en pantallas de celular
    )
plt.savefig("holi.png")
