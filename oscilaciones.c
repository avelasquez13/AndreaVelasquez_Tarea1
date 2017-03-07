#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

#define PI 3.14159265
#define N 64

int n, i, j, d;
float B = 1.0, dt = 0.005;

double x_0(int n);
double acceleration(int n, double *x);
double *lf_x(double *xi_1, double *v);
double *lf_v(double *xi, double *v);
double Ek(double *x, double *v, int k);


int main(int argc, char *argv[]){
	
        double tiempo0 = omp_get_wtime();
	int I=5*pow(N,2.2)/dt;
	int d=1;
	int num = atoi(argv[1]);
	omp_set_num_threads(num);
	
	FILE *out;

	//crea el archivo de salida de xs contra t
	out = fopen("valores.dat", "w");
	fclose(out); 
  
	//crea el archivo de salida de energias
	out = fopen("energias.dat", "w");
	fclose(out); 

	//crea el archivo de salida de tiempos
	out = fopen("tiempos.dat", "a");
	fclose(out); 
  
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
	
	//crea vectores de energia en los 3 modos
	double *E1;
	E1= (double*) malloc(1000*sizeof(double));
	double *E2;
	E2= (double*) malloc(1000*sizeof(double));
	double *E3;
	E3= (double*) malloc(1000*sizeof(double));

	
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
	
	//calcula las energias en t=0
	E1[0]=Ek(x[0],v[0],1);
	E2[0]=Ek(x[0],v[0],2);
	E3[0]=Ek(x[0],v[0],3);
			
	//itera a traves del tiempo
	for(i=1; i<I; i++)
	{
		x[i]=lf_x(x[i-1], v[i-1]);
		v[i]=lf_v(x[i], v[i-1]);
		
		if(i%(I/1000)==0){
		
	       		//calcula las energias en t=i
	 		E1[d]=Ek(x[i],v[i],1);
	 		E2[d]=Ek(x[i],v[i],2);
	 		E3[d]=Ek(x[i],v[i],3);
	 		d++;

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

	//imprime energias
	out = fopen("energias.dat", "a");
	for(i=0;i<1000;i++)
	{
		fprintf(out, "%.20f ", E1[i]);
	}
	fprintf(out,"\n");
	
	for(i=0;i<1000;i++)
	{
		fprintf(out, "%.20f ", E2[i]);
	}
	fprintf(out,"\n");
	
	for(i=0;i<1000;i++)
	{
		fprintf(out, "%.20f ", E3[i]);
	}
	fprintf(out,"\n");
	fclose(out);

	//imprime los tiempos
	double tiempo = omp_get_wtime() - tiempo0;
	out = fopen("tiempos.dat", "a");
	fprintf(out, "%.20f ", tiempo);
	

	return 0;

}


double x_0(int n){

  double x0;
  x0 = sin(PI*n/(N-1));

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
  
  #pragma omp parallel for
	for(n=0; n<N; n++)
	{
		xi[n]=xi_1[n]+v[n]*dt;
	}
	free(xi);
	return xi;

}


double *lf_v(double *xi, double *v){

	double *vi12;
  vi12 = malloc(N*sizeof(double));
  
  #pragma omp parallel for
	for(n=1; n<N-1; n++)
	{
		vi12[n]=v[n]+acceleration(n, xi)*dt;
	}
	free(vi12);
	return vi12;
	
}


double Ek(double *x, double *v, int k){

	double Qk=0;
	double Qkp=0;
	double wk2 = 4*pow(sin(k*PI/(2*N)), 2);
	
	for (n=0; n<N; n++)
	{
	 	 Qk+=x[n]*sin(n*k*PI/(N));
	 	 Qkp+=v[n]*sin(n*k*PI/(N));
	}
	Qk = Qk*pow(2.0/(N), 0.5);
	Qkp = Qkp*pow(2.0/(N), 0.5);
	
	return 0.5*(pow(Qkp,2) + wk2*pow(Qk, 2));
	
}
