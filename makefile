EXECS=oscilaciones
MPICC?=mpicc

all: ${EXECS}


placas : oscilaciones.c
	${MPICC} -o oscilaciones -lm oscilaciones.c

#valores.dat : oscilaciones
#	qsub submit_job.sh

plot :
	cp oscilaciones.o* valores.dat
	python plot.py


clean :
	rm oscilaciones
	rm valores.dat
	rm oscilaciones.o*
	rm oscilaciones.e*

