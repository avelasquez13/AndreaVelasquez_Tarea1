#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int N = 1024;
float B = 0.3, dt = 0.001;

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
