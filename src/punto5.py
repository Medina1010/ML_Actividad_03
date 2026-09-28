import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import seaborn as sns


df = pd.read_excel('Machine.xlsx',  sheet_name = 'Hoja 1')

features = ['Edad','Estatura','Nota Electro','Hermanos','Peso']
X =df.iloc[:21][features]

scaler = StandardScaler()
X_scaled =  scaler.fit_transform(X)

pca = PCA()
X_pca = pca.fit_transform(X_scaled)

for i  in range(len(X_pca)):
  plt.annotate(str(i), (X_pca[i,0] + 0.05 , X_pca[i,1]+ 0.05))

plt.scatter(X_pca[:,0], X_pca[:,1], color='purple')
plt.xlabel("Componente principal 1")
plt.ylabel("Componente principal 2")
plt.title("Análisis de componentes principales")
plt.grid(True)


plt.figure(figsize=(10,6))
sns.heatmap(X.corr(), annot= True , cmap= 'coolwarm')
plt.title("Matriz de correlación")
plt.show()
