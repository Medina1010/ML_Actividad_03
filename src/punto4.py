import numpy as np

sigma_x = 1
sigma_y = 2
N = 100

x = np.random.normal(0, sigma_x, N)
y = np.random.normal(0, sigma_y, N)

matrix = np.column_stack((x, y))

T = np.array([[1, 2],
              [-1, 0]])

new_matrix = matrix @ T.T

data_centered = new_matrix - np.mean(new_matrix, axis=0)

cov_matrix = np.cov(data_centered, rowvar=False)

eigenvalues, eigenvectors = np.linalg.eig(cov_matrix)

sort_indices = np.argsort(eigenvalues)[::-1]
eigenvalues = eigenvalues[sort_indices]
eigenvectors = eigenvectors[:, sort_indices]

explained_variance_ratio = eigenvalues / np.sum(eigenvalues)


pca_projection = np.dot(data_centered, eigenvectors)

print("Matriz de Covarianza:\n", cov_matrix)
print("\nAutovalores (Varianza explicada por cada CP):\n", eigenvalues)
print("\nAutovectores (Direcciones de las Componentes Principales):\n", eigenvectors)
print("\nProporción de Varianza Explicada:\n", explained_variance_ratio)
