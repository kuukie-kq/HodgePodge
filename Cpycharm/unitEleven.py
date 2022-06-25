import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from sklearn import metrics
import seaborn as sns


def k_SEE(X, clusters):
    # 自定义函数，绘制不同k值和对应总的族内离差平方和的折线图
    K = range(1, clusters+1)
    TSSE = []
    for k in K:
        # 用于存储各个族内离差平方和
        SSE = []
        kmeans = KMeans(n_clusters=k)
        kmeans.fit(X)
        # 返回族标签
        labels = kmeans.labels_
        # 返回族中心
        centers = kmeans.cluster_centers_
        # 计算各族样本的离差平方和，并保存到列表中
        for label in set(labels):
            SSE.append(np.sum((X.loc[labels == label, ]-centers[label, :])**2))
        # 计算总的族内离差平方和
        TSSE.append(np.sum(SSE))
    # 中文和负号的正常显示
    plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
    plt.rcParams['axes.unicode_minus'] = False
    # 设置绘图风格
    plt.style.use('ggplot')
    plt.plot(K, TSSE, 'b*-')
    plt.xlabel('k值，族的个数')
    plt.ylabel('族内离差平方和之和')
    plt.show()


def k_silhouette(X, clusters):
    # 自定义函数，绘制不同k值和对应轮廓系数的折线图
    K = range(2, clusters+1)
    S = []
    for k in K:
        kmeans = KMeans(n_clusters=k)
        kmeans.fit(X)
        labels = kmeans.labels_
        S.append(metrics.silhouette_score(X, labels, metric='euclidean'))
    # 中文和负号的正常显示
    plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
    plt.rcParams['axes.unicode_minus'] = False
    # 设置绘图风格
    plt.style.use('ggplot')
    plt.plot(K, S, 'b*-')
    plt.xlabel('k值，族的个数')
    plt.ylabel('轮廓系数')
    plt.show()


def short_pair_wise_D(each_cluster):
    # 自定义函数，计算族内任意两样本之间的欧式距离DK
    mu = each_cluster.mean(axis=0)
    DK = sum(sum((each_cluster - mu)**2))*2.0*each_cluster.shape[0]
    return DK


def compute_WK(data, classfication_result):
    # 自定义函数，计算族内的WK的值
    WK = 0
    label_set = set(classfication_result)
    for label in label_set:
        each_cluster = data[classfication_result == label, :]
        WK = WK + short_pair_wise_D(each_cluster)/2.0*each_cluster.shape[0]
    return WK


def gap_statistic(X, B=10, K=range(1,11), N_init=10):
    # 自定义函数，计算GAP统计量
    # 将输入的数据集转换成数组
    X = np.array(X)
    shape = X.shape
    tops = X.max(axis=0)
    bots = X.min(axis=0)
    dists = np.matrix(np.diag(tops-bots))
    rands = np.random.random_sample(size=(B, shape[0], shape[1]))
    for i in range(B):
        rands[i, :, :] = rands[i, :, :]*dists+bots
    # 自定义元素的数组，用于存储gaps、WKs、WKbs
    gaps = np.zeros(len(K))
    WKs = np.zeros(len(K))
    WKbs = np.zeros((len(K), B))
    # 循环不同的k值，计算各族下的WK值
    for idxk, k in enumerate(K):
        kmeans = KMeans(n_clusters=k)
        kmeans.fit(X)
        classfication_result = kmeans.labels_
        # 将所有族内的WK存储起来
        WKs[idxk] = compute_WK(X, classfication_result)
        # 通过循环，计算每一个参照数据集下的各族WK值
        for i in range(B):
            Xb = rands[i, :, :]
            kmeans.fit(Xb)
            classfication_result_b = kmeans.labels_
            WKbs[idxk, i] = compute_WK(Xb, classfication_result_b)
    # 计算gaps、sd_ks、sk和gapDiff
    gaps = (np.log(WKbs)).mean(axis=1)-np.log(WKs)
    sd_ks = np.std(np.log(WKbs), axis=1)
    sk = sd_ks*np.sqrt(1+1.0/B)
    # 用于判别最佳k的标准，当gapDiff首次为正时
    gapDiff = gaps[:-1]-gaps[1:]+sk[1:]
    # 中文和负号的正常显示
    plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
    plt.rcParams['axes.unicode_minus'] = False
    # 设置绘图风格
    plt.style.use('ggplot')
    plt.bar(np.arange(len(gapDiff))+1, gapDiff, color='steelblue')
    plt.xlabel('k值，族的个数')
    plt.ylabel('k选择标准')
    plt.show()


if __name__ == "__main__":
    clv = pd.read_csv(r'D:\MyPFile\BigDataPythonFile\CLV.csv')
    k_SEE(clv, 10)
    k_silhouette(clv, 10)
    gap_statistic(clv, B=10, K=range(1, 11))

    kmeans = KMeans(n_clusters=4)
    kmeans.fit(clv)
    clv['cluster'] = kmeans.labels_

    sns.lmplot(x='INCOME', y='SPEND', hue='cluster', data=clv, markers=['^', 's', 'o', '*'], fit_reg=False, scatter_kws={'alpha': 0.8}, legend=False)
    plt.show()
