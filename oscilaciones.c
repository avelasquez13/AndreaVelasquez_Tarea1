#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.14159265
#define Ng 1024

int N, I=100*Ng, n, i;
float B = 0.3, dt = 0.001;
double x_0(int n);
double acceleration(int n, double *x);
double *lf_x(double *xi_1, double *v);
double *lf_v(double *xi, double *v);


int main(void){

	FILE *out;
  MPI_Init(NULL, NULL);

  int world_size, rank, source, destination;
  //MPI_Request request[4];
  //MPI_Status status[4];

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  //crea el archivo de salida
  if(rank==0){
    out = fopen("file.dat", "w");
    fclose(out);
  }
  MPI_Barrier( MPI_COMM_WORLD );
  
  if(rank==0||rank==world_size-1){
  	N=Ng/world_size+1;
  }
  else{
  	N=Ng/world_size+2;
  }
  
   
	//crea las matrices
	double **v;
	v=(double**) malloc(I*sizeof(double*));
	for(i=0; i<I; i++)
	{
		v[i]=(double*) malloc(N*sizeof(double));
	}
	
	double **x;
	x=(double**) malloc(I*sizeof(double*));
	for(i=0; i<I; i++)
	{
		x[i]=(double*) malloc(N*sizeof(double));
	}
	
	//inicializa las matrices con las condiciones iniciales
	if(rank==0){
		for(n=0; n<N; n++)
		{
			x[0][n]=x_0(n);
		}
	}
	else{
		for(n=0; n<N; n++)
		{
			x[0][n]=x_0(n+rank*Ng/world_size-1);
		}
	}
	
	for(n=1; n<N-1; n++)
	{
		v[0][n]=acceleration(n, x[0])*dt/2;
	}
	if(rank==0){
		v[0][0]=0;
	}
	else if(rank==world_size-1){
		v[0][N-1]=0;
	}
	MPI_Barrier( MPI_COMM_WORLD );
	
	if(rank==0){
		MPI_Send(&v[0][N-2], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(&v[0][N-1], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	else if(rank==world_size-1){
	  MPI_Recv(&v[0][0], 1, MPI_DOUBLE, world_size-2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&v[0][1], 1, MPI_DOUBLE, world_size-2, 0, MPI_COMM_WORLD);
	}
	else{
	  MPI_Send(&v[0][N-2], 1, MPI_DOUBLE, rank+1, 0, MPI_COMM_WORLD);
	  MPI_Recv(&v[0][0], 1, MPI_DOUBLE, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&v[0][1], 1, MPI_DOUBLE, rank-1, 0, MPI_COMM_WORLD);
    MPI_Recv(&v[0][N-1], 1, MPI_DOUBLE, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
	
	//itera a traves del tiempo
	for(i=1; i<I; i++)
	{
		
	}
	MPI_Barrier( MPI_COMM_WORLD );
	
	//imprime v en t0
	for(i=0;i<world_size;i++)
	{
    if(i==rank&&i==0){
      out = fopen("valores.dat", "a");
      for(n=0;n<N-1;n++)
      {
				fprintf(out, "%.20f ", v[0][n]);
      }
      fclose(out);
    }
    else if(i==rank&&i==world_size-1){
      out = fopen("valores.dat", "a");
      for(n=1;n<N;n++)
      {
				fprintf(out, "%.20f ", v[0][n]);
      }
      fprintf(out, "\n");
      fclose(out);
    }
    else if(i==rank){
      out = fopen("valores.dat", "a");
      for(n=1;n<N-1;n++)
      {
				fprintf(out, "%.20f ", v[0][n]);
      }
      fclose(out);
    }
    MPI_Barrier( MPI_COMM_WORLD );
  }
	

  MPI_Finalize();
  return 0;

}



double x_0(int n){

  double x0;
  x0= sin(2*PI*n/(Ng-1));

  return x0;

}



double acceleration(int n, double *x){

  double xpp;
	xpp = (x[n+1]-2*x[n]+x[n-1]) + B*(pow((x[n+1]-x[n]), 3)-pow((x[n]-x[n-1]), 3));
	
  return xpp;

}

double *lf_x(double *xi_1, double *v){

	double *xi;
  xi = malloc(N*sizeof(double));
  
	for(n=0; n<N; n++)
	{
		xi[n]=xi_1[n]+v[n]*dt;
	}
	return xi;
}

double *lf_v(double *xi, double *v){

	double *vi12;
  vi12 = malloc(N*sizeof(double));
  
	for(n=0; n<N; n++)
	{
		vi12[n]=v[n]+acceleration(n, xi)*dt;
	}
	return vi12;
}

