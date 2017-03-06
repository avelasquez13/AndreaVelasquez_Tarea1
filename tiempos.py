import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

tiempos = np.loadtxt('tiempos.dat')
procesador = [1, 2, 4]

plt.scatter(procesador, tiempos)
plt.title('Tiempo que se demora corriendo el codigo segun numero de procesadores')
plt.xlabel('Numero de procesadores')
plt.ylabel('Tiempo (s)')
plt.xticks([0, 1, 2, 3, 4, 5])
plt.savefig('tiempos.pdf')
plt.close()
