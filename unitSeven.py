import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import statsmodels.api as sm
import sklearn.model_selection as model_selection

selfUnitSeven = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\self-testUnitSeven.xlsx',
                              header=None, names=['One', 'Two', 'Three'],
                              skiprows=1)

# sns.lmplot(x='Two', y='One', data=selfUnitSeven, ci=None)
# sns.lmplot(x='Three', y='One', data=selfUnitSeven, ci=None)
# plt.show()

train, test = model_selection.train_test_split(selfUnitSeven, test_size=0.15)
model = sm.formula.ols('One ~ Two + Three', data=train).fit()
print(model.params)
test_X = test.drop(labels='One', axis=1)
pred = model.predict(exog=test_X)

print(pd.DataFrame({'Prediction': pred, 'Real': test.One}))

from scipy.stats import f

p = model.df_model
n = train.shape[0]
print(p, n)
print(model.fvalue, f.ppf(q=0.95, dfn=p, dfd=n-1-p))
