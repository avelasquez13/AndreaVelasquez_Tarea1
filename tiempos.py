import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

tiempos = np.loadtxt('tiempos.dat')
procesador = [1, 2, 4]

plt.plot(procesador, tiempos)
plt.title('Tiempo que se demora corriendo el codigo segun numero de procesadores')
plt.xlabel('Numero de procesadores')
plt.ylabel('Tiempo')
plt.savefig('tiempos.pdf')
plt.close()
