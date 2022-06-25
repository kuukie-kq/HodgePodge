import pandas as pd
from sklearn import svm
from sklearn import metrics
from sklearn import model_selection


if __name__ == "__main__":
    boston = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\Boston.xlsx')
    predictors = boston.columns[1:]
    X_train, X_test, Y_train, Y_test = model_selection.train_test_split(boston[predictors], boston[0], test_size=0.25, random_state=100)

    C = [0.05, 0.1, 0.5, 1, 2, 5]
    parameters = {'C': C}
    grid_linear_svc = model_selection.GridSearchCV(estimator=svm.LinearSVC(), param_grid=parameters, scoring='accuracy', cv=5, verbose=1)
    grid_linear_svc.fit(X_train, Y_train)
    print(grid_linear_svc.best_params_, grid_linear_svc.best_score_)
