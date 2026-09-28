import numpy as np
import matplotlib.pyplot as plt


X = np.loadtxt('../res/pca_data.csv', delimiter=',', skiprows=1);


X_mean = np.mean(X, axis=0)
X_std = np.std(X, axis=0)
X_scaled = (X - X_mean) / X_std



U, S, Vt = np.linalg.svd(X_scaled, full_matrices=False)


n_components = 2
X_pca = U[:, :n_components] * S[:n_components]


variance_explained = (S ** 2) / (len(X) - 1)
total_variance = np.sum(variance_explained)
variance_ratio = variance_explained / total_variance


print("--- Datos reducidos (Nuevas Coordenadas PC1 y PC2) ---")
print(X_pca)

print("\n--- Porcentaje de Varianza Explicada por componente ---")
for i, ratio in enumerate(variance_ratio[:n_components]):
    print(f"PC{i+1}: {ratio * 100:.2f}%")

plt.grid()
plt.plot(X_pca[:,0],X_pca[:,1], 'o' )
plt.axline((0, 0), (Vt[0,0] * 2,Vt[1,0] * 2), linestyle="--", label="edad")
plt.axline((0, 0), (Vt[0,1] * 2,Vt[1,1] * 2), color="blue", linestyle="--", label="estatura")
plt.axline((0, 0), (Vt[0,2] * 2,Vt[1,2] * 2), color="red", linestyle="--", label="nota")
plt.axline((0, 0), (Vt[0,3] * 2,Vt[1,3] * 2), color="orange", linestyle="--", label="hermanos")
plt.axline((0, 0), (Vt[0,4] * 2,Vt[1,4] * 2), color="purple", linestyle="--", label="peso")

plt.legend();

print(X[8])
print(X[18])

for idx, (xi, yi) in enumerate(zip(X_pca[:,0], X_pca[:,1])):
    
    plt.annotate(
        str(idx), 
        (xi, yi),
        textcoords="offset points", 
        xytext=(0, 8),              
        ha='center',                
        fontsize=9,                 
        fontweight='bold'           
    )
plt.savefig("holi.png")

n_components = 3
X_pca = U[:, :n_components] * S[:n_components]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.grid()
ax.plot(X_pca[:,0],X_pca[:,1],X_pca[:,2], 'o' )
ax.plot(Vt[0,0] * 2,Vt[1,0] * 2, Vt[2,0] * 2, 'o', label = 'edad')
ax.plot(Vt[0,1] * 2,Vt[1,1] * 2, Vt[2,1] * 2, 'o', label = 'estatura')
ax.plot(Vt[0,2] * 2,Vt[1,2] * 2, Vt[2,2] * 2, 'o', label = 'nota')
ax.plot(Vt[0,3] * 2,Vt[1,3] * 2, Vt[2,3] * 2, 'o', label = 'hermanos')
ax.plot(Vt[0,4] * 2,Vt[1,4] * 2, Vt[2,4] * 2, 'o', label = 'peso')
ax.legend();

fig.savefig("holiasdf.png")
