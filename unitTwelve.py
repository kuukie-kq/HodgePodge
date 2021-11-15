import pandas as pd
from sklearn.cluster import KMeans, DBSCAN, AgglomerativeClustering
from sklearn import metrics


def transformKMeans(string):
    if string == 'Kama wheat':
        return 0
    elif string == 'Rosa wheat':
        return 1
    elif string == 'Canadian wheat':
        return 2
    else:
        return -1


def transformDBSCAN(string):
    if string == 'Kama wheat':
        return 0
    elif string == 'Rosa wheat':
        return 2
    elif string == 'Canadian wheat':
        return 1
    else:
        return -1


def transformAgglo(string):
    if string == 'Kama wheat':
        return 2
    elif string == 'Rosa wheat':
        return 0
    elif string == 'Canadian wheat':
        return 1
    else:
        return -1


if __name__ == '__main__':
    seeds = pd.read_csv(r'D:\MyPFile\BigDataPythonFile\seeds.csv',
                        header=None, names=['S', 'C', 'jzx', 'L', 'W', 'pxd', 'zlcd', 'zl'],
                        skiprows=1)
    seed = seeds.drop(['zl'], axis=1)
    seeds['kmeans_zl'] = seeds.zl.apply(lambda x: transformKMeans(x))
    seeds['dbscan_zl'] = seeds.zl.apply(lambda x: transformDBSCAN(x))
    seeds['agglo_zl'] = seeds.zl.apply(lambda x: transformAgglo(x))

    kmeans = KMeans(n_clusters=3, random_state=15)
    kmeans.fit(seed)
    seed['kmeans'] = kmeans.labels_

    dbscan = DBSCAN(eps=1.2, min_samples=9)
    dbscan.fit(seed)
    seed['dbscan'] = dbscan.labels_

    agglo = AgglomerativeClustering(n_clusters=3)
    agglo.fit(seed)
    seed['agglo'] = agglo.labels_

    print("KMeans准确率", metrics.accuracy_score(seeds.kmeans_zl, seed.kmeans))
    print("DBSCAN准确率", metrics.accuracy_score(seeds.dbscan_zl, seed.dbscan))
    print("Agglo准确率", metrics.accuracy_score(seeds.agglo_zl, seed.agglo)
