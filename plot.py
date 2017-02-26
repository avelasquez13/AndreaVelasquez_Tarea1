import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt('valores.dat')

plt.imshow(datos, extent = [0, 5, 0, 5])
plt.colorbar()
plt.ylim([0, 5])

plt.title('Posicion de cada atomo en funcion del tiempo')
plt.savefig('grafica.pdf')
