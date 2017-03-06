import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


datos = np.loadtxt('valores.dat')
energias=np.loadtxt('energias.dat')

E1=energias[0]
E2=energias[1]
E3=energias[2]

t = np.linspace(0, 47050, 1000)

plt.imshow(datos)
plt.colorbar()

plt.title('Posicion de cada atomo en funcion del tiempo')
plt.savefig('grafica.pdf')
plt.close()

plt.plot(t, E1, label = 'E1')
plt.plot(t, E2, label = 'E2')
plt.plot(t, E3, label = 'E3')
plt.title('Energia Ek en funcion del tiempo')
plt.legend()
plt.xlabel('Tiempo')
plt.ylabel('Ek')
plt.savefig('energias.pdf')
