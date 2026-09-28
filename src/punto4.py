import numpy as np

sigma_x = 1
sigma_y =  2 
N=100

x = np.random.normal(0,sigma_x, N)
y = np.random.normal(0, sigma_y,  N)

matrix = np.column_stack((x,y))

T= [(1 , 2),
    (-1 , 0)]

product= np.dot(matrix, T)

datos_centrados = product - np.mean(product , axis= 0)
covar = np.cov(datos_centrados , rowvar= False)

eigenvalues,  eigenvectors = np.linalg.eig(covar)

sort_indices = np.argsort(eigenvalues)[::-1]
eigenvalues = eigenvalues[sort_indices]
eigenvectors = eigenvectors[:, sort_indices]

explained_variance_ratio = eigenvalues / np.sum(eigenvalues)


pca_projection = np.dot(datos_centrados, eigenvectors)

print("Matriz de Covarianza:\n", covar)
print("\nAutovalores (Varianza explicada por cada CP):\n", eigenvalues)
print("\nAutovectores (Direcciones de las Componentes Principales):\n", eigenvectors)
print("\nProporción de Varianza Explicada:\n", explained_variance_ratio)
