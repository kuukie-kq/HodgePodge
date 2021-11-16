import pandas as pd

selfUnitEight = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\self-testUnitEight.xlsx')
dummy = pd.get_dummies(selfUnitEight[['年龄段', '是否有工作', '有自己的房子', '信贷情况', '类别']])
selfUnitEight = pd.concat([selfUnitEight, dummy], axis=1)
selfUnitEight.drop(['ID', '年龄段', '是否有工作', '有自己的房子', '信贷情况', '类别', '类别_否', '是否有工作_否', '有自己的房子_否'], inplace=True, axis=1)

from sklearn import model_selection, metrics

predictors = selfUnitEight.columns[:-1]
X_train, X_test, Y_train, Y_test = model_selection.train_test_split(selfUnitEight[predictors], selfUnitEight.类别_是, test_size=0.1, random_state=1)

from sklearn.model_selection import GridSearchCV
from sklearn import tree

max_depth = [2, 3, 4]
min_samples_split = [2, 4, 6]
min_samples_leaf = [2, 3, 4]
parameters = {'max_depth': max_depth, 'min_samples_split': min_samples_split, 'min_samples_leaf': min_samples_leaf}
grid_dtcateg = GridSearchCV(estimator=tree.DecisionTreeClassifier(), param_grid=parameters)
grid_dtcateg.fit(X_train, Y_train)
print(grid_dtcateg.best_params_)
CartClass = tree.DecisionTreeClassifier(max_depth=2, min_samples_leaf=2, min_samples_split=2)

decision_tree = CartClass.fit(X_train, Y_train)
pred = CartClass.predict(X_test)

print('测试集中的准确率:', metrics.accuracy_score(Y_test, pred))
print('训练集中的准确率:', metrics.accuracy_score(Y_train, CartClass.predict(X_train)))
