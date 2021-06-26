import pandas as pd
from sklearn import model_selection, metrics
from sklearn import neighbors

unitNine = pd.read_csv(r'D:\MyPFile\BigDataPythonFile\house_data.csv')
unitNine.drop(['id', 'date'], inplace=True, axis=1)

from sklearn.preprocessing import minmax_scale
predictors = unitNine.columns[1:]
X = minmax_scale(unitNine[predictors])
X_train, X_test, Y_train, Y_test = model_selection.train_test_split(unitNine[predictors], unitNine.price, test_size=0.25, random_state=100)

import numpy as np

K = np.arange(1, np.ceil(np.log2(unitNine.shape[0]))).astype(int)
mse = []
for k in K:
    cv_result = model_selection.cross_val_score(neighbors.KNeighborsRegressor(n_neighbors=k, weights='distance'),
                                                X_train, Y_train, cv=10, scoring='neg_mean_squared_error')
    mse.append((-1*cv_result).mean())
arg_min = np.array(mse).argmin()
knn_reg = neighbors.KNeighborsRegressor(n_neighbors=arg_min+1, weights='distance')
knn_reg.fit(X_train, Y_train)
predict = knn_reg.predict(X_test)

print("Mse:", metrics.mean_squared_error(Y_test, predict))
print(pd.DataFrame({'R': Y_test, 'P': predict}).head(5))
