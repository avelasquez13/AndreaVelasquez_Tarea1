#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

#define PI 3.14159265
#define N 1024

int n, i, j;
float B = 0.3, dt = 0.001;
//TODO volver a poner 2.2


double x_0(int n);
double acceleration(int n, double *x);
double *lf_x(double *xi_1, double *v);
double *lf_v(double *xi, double *v);


int main(void){
	
	int I=100*N;
	
	FILE *out;

  //crea el archivo de salida
  out = fopen("valores.dat", "w");
  fclose(out); 
   
	//crea la matriz
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
	
	//inicializa la matriz con las condiciones iniciales

	for(n=0; n<N; n++)
	{
		x[0][n]=x_0(n);
	}
	
	//kick
	for(n=1; n<N-1; n++)
	{
		v[0][n]=acceleration(n, x[0])*dt/2;
	}
	
	//condiciones de frontera
	v[0][0]=0;
	v[0][N-1]=0;
	
	//imprime x en t=0
	out = fopen("valores.dat", "a");
  for(n=0;n<N;n++)
	{
		fprintf(out, "%.20f ", x[0][n]);
	}
	fprintf(out,"\n");
	fclose(out);

	  
			
	//itera a traves del tiempo
	for(i=1; i<I; i++)
	{
		x[i]=lf_x(x[i-1], v[i-1]);
		v[i]=lf_v(x[i], v[i-1]);
		
		if(i%100==0){
		
			//imprime x en t=i
			out = fopen("valores.dat", "a");
  		for(n=0;n<N;n++)
			{
				fprintf(out, "%.20f ", x[i][n]);
			}
			fprintf(out,"\n");
			fclose(out);
		} 	
	}

  return 0;

}



double x_0(int n){

  double x0;
  x0= sin(2*PI*n/(N-1));

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
  
	for(n=1; n<N-1; n++)
	{
		vi12[n]=v[n]+acceleration(n, xi)*dt;
	}
	return vi12;
	
}

