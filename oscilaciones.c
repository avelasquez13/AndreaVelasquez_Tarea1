#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.14159265

int N = 1024;
float B = 0.3, dt = 0.001;

double *x_0(int n);
double *acceleration(int n, double *x);
//double leapfrog();

int main(void){
 
  MPI_Init(NULL, NULL);

  int world_size, rank, source, destination;
  MPI_Request request[4];
  MPI_Status status[4];

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  



  MPI_Finalize();
  return 0;

}



double *x_0(int n){

  double *x0;
  x0 = malloc(N*sizeof(double));

  for(n=0; n<N; n++){
    x0[n] = sin(2*PI*n/(N-1));
  }

  return x0;

}



double *acceleration(int n, double *x){

  double *xpp;
  xpp = malloc(N*sizeof(double));

  for(n=0; n<N; n++){
    xpp[n] = (x[n+1]-2*x[n]+x[n-1]) + B*(pow((x[n+1]-x[n]), 3)-pow((x[n]-x[n-1]), 3));
  }

  return xpp;

}
