import pandas as pd

skin = pd.read_excel(r'D:\MyPFile\BigDataPythonFile\Skin_Segment.xlsx')
skin.y = skin.y.map({2: 0, 1: 1})

from sklearn import model_selection
from sklearn import naive_bayes

X_train, X_test, Y_train, Y_test = model_selection.train_test_split(skin.iloc[:, :3], skin.y, test_size=0.25, random_state=1)
gnb = naive_bayes.GaussianNB()
gnb.fit(X_train, Y_train)
gnb_pred = gnb.predict(X_test)

from sklearn import metrics
import matplotlib.pyplot as plt
import seaborn as sns

plt.figure(figsize=(12, 6))
ax1 = plt.subplot2grid(shape=(1, 2), loc=(0, 0))
ax2 = plt.subplot2grid(shape=(1, 2), loc=(0, 1))

cm = pd.crosstab(gnb_pred, Y_test)
sns.heatmap(cm, annot=True, cmap='GnBu', fmt='d', ax=ax1)
plt.xlabel('Real')
plt.ylabel('Predict')

print("准确率为:", metrics.accuracy_score(Y_test, gnb_pred))
print("评估报告为:\n", metrics.classification_report(Y_test, gnb_pred))

Y_score = gnb.predict_proba(X_test)[:, 1]
fpr, tpr, threshold = metrics.roc_curve(Y_test, Y_score)
roc_auc = metrics.auc(fpr, tpr)
ax2 = plt.stackplot(fpr, tpr, colors='steelblue', alpha=0.5, edgecolor='black')
plt.plot(fpr, tpr, color='black', lw=1)
plt.plot([0, 1], [0, 1], color='red', linestyle='--')
plt.text(0.5, 0.3, 'ROC(area=%0.2f)' % roc_auc)

plt.show()
