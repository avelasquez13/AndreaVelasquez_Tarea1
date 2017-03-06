tiempos.pdf energias.pdf: valores.dat energias.dat
	python plot.py
	python tiempos.py

valores.dat : oscilaciones
	./oscilaciones 1
	./oscilaciones 2
	./oscilaciones 4

oscilaciones : oscilaciones.c
	gcc -fopenmp -o oscilaciones oscilaciones.c -lm

clean :
	rm oscilaciones
	rm energias.dat
	rm tiempos.dat
	rm valores.dat
