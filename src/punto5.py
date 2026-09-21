import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA


df = pd.read_excel("../res/sol_objects.csv")#, engine="odf")


X = df[[
        "semimajorAxis",
            "eccentricity",
                "meanRadius",
                    "mass_kg",
                        "orbit_type"
                        ]]


X = X.fillna(X.median(numeric_only=True))

scaler = StandardScaler()
X_std = scaler.fit_transform(X)

pca = PCA()
X_pca = pca.fit_transform(X_std)


print("Varianza explicada:")
print(pca.explained_variance_ratio_)

print("\nVarianza acumulada:")
print(pca.explained_variance_ratio_.cumsum())
