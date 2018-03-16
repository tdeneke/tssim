import numpy as np
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt 

#generate n group of timeserieses
def ts_gen(ng=5, nts=20, n=100):
    """ function to generate ng clusters of nts timeseries with len n"""
    lts = np.empty((0, n))
    np.random.seed(100)
    for i in range(ng):
        # template timeseries for a group 
        ts = np.random.uniform(-500, 500, n)
        for j in range(nts):
            # a similar timeseries based on template
            tssim = ts + 0.05*np.random.uniform(-500, 500, n)
            lts = np.append(lts, [tssim], axis=0)
    return lts
#do a pca on a set of timeserieses
def ts_pca(lts, npc=3):
    pca = PCA(n_components=npc)
    pca.fit(lts)
    return pca
#plot n pcs
def ts_plot_pc(lts, pca, npc=3):
    x = pca.transform(lts)
    print(x)
    plt.plot(x[:,0])
    plt.plot(x[:,1])
    plt.plot(x[:,2])
    plt.show()
    return

if __name__ == "__main__":
    print("pca of timeseries data!\n")
    lts = ts_gen()
    pca = ts_pca(lts)
    ts_plot_pc(lts, pca)
