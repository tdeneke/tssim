import numpy as np
from sklearn.decomposition import PCA, FastICA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt 

scale = lambda x: (x - x.mean()) / x.std()

#generate n group of timeserieses
def ts_gen(ng=3, nts=300, n=100):
    """ function to generate ng clusters of nts timeseries with len n"""
    lts = np.empty((0, n))
    np.random.seed(167)
    for i in range(ng):
        # template timeseries for a group 
        ts = np.random.uniform(-100, 100, n)
        for j in range(1, len(ts)):
            ts[j] = ts[j-1] + ts[j]
        # group of timeseries with slight variations
        for k in range(nts):
            # a similar timeseries based on template
            tssim = ts + 0.5*np.random.uniform(-100, 100, n)
            lts = np.append(lts, [tssim], axis=0)
    return lts
#do a pca on a set of timeserieses
def ts_pca(lts, npc=3):
    pca = PCA(n_components=npc)
    pca.fit(lts.transpose())
    return pca
#plot n pcs
def ts_plot_pc(lts, pca, npc=3):
    x = pca.transform(lts.transpose())
    #print(x)
    for i in range(npc):
        plt.plot(x[:,i])
    plt.show()
    return

#do a pca on a set of timeserieses
def ts_ica(lts, nic=3):
    ica = FastICA(n_components=nic)
    ica.fit(lts.transpose())
    return ica
#plot n pcs
def ts_plot_ic(lts, ica, nic=3):
    x = ica.transform(lts.transpose())
    #print(x)
    for i in range(nic):
        plt.plot(x[:,i])
    plt.show()
    return

if __name__ == "__main__":
    print("pca of timeseries data!\n")
    lts = ts_gen()
    plt.plot(lts[0,:])
    plt.plot(lts[300,:])
    plt.plot(lts[600,:])
    #scaler = StandardScaler()
    #lts = scaler.fit_transform(lts)
    #lts = scale(lts)
    # lts /= lts.std(axis=0) #standardise
    plt.plot(lts[10,:])
    plt.plot(lts[310,:])
    plt.plot(lts[610,:])
    plt.show()

    pca = ts_pca(lts)
    ts_plot_pc(lts, pca)

    ica = ts_ica(lts)
    ts_plot_ic(lts, ica)
