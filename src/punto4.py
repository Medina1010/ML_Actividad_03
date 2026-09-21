import numpy as np

N = 1000
sigma_x = 2
sigma_y = 1

x = np.random.normal(0, sigma_x, N)
y = np.random.normal(0, sigma_y, N)

datos = np.column_stack((x, y))

A = np.array([[1,2],
                            [-1,0]])

datos_transformados = datos @ A.T

cov = np.cov(datos_transformados.T)

valores, vectores = np.linalg.eig(cov)

idx = np.argsort(valores)[::-1]

valores = valores[idx]
vectores = vectores[:, idx]

datos_pca = datos_transformados @ vectores

print("Covarianza:")
print(cov)

print("\nAutovalores:")
print(valores)

print("\nAutovectores:")
print(vectores)
