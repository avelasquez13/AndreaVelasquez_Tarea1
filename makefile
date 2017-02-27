#para correr en un nodo local 

grafica.pdf : valores.dat
	python plot.py

#valores.dat : oscilaciones
#	qsub submit_job.sh


valores.dat : oscilaciones
	mpiexec -n 4 ./oscilaciones

oscilaciones : oscilaciones.c
	mpicc -o oscilaciones oscilaciones.c -lm


clean :
	rm oscilaciones
	rm valores.dat

