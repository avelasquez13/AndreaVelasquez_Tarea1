#para correr en un nodo local 

grafica.pdf energias.pdf: valores.dat
	python plot.py

#valores.dat : oscilaciones
#	qsub submit_job.sh


valores.dat : oscilaciones
	./oscilaciones 4

oscilaciones : oscilaciones.c
	gcc -fopenmp  -o oscilaciones oscilaciones.c -lm


clean :
	rm oscilaciones
	rm valores.dat

