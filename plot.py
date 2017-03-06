import numpy as np
import matplotlib.pyplot as plt

datos = np.loadtxt('valores.dat')

energias=np.loadtxt('energias.dat')

E1=energias[0]
E2=energias[1]
E3=energias[2]

plt.imshow(datos)
plt.colorbar()

plt.title('Posicion de cada atomo en funcion del tiempo')
plt.savefig('grafica.pdf')
plt.close()

plt.plot(E1)
plt.plot(E2)
plt.plot(E3)
plt.savefig('energias.pdf')
