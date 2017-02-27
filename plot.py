import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt('valores.dat')

plt.imshow(datos)
plt.colorbar()

plt.title('Posicion de cada atomo en funcion del tiempo')
plt.savefig('grafica.pdf')
