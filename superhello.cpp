#include <mpi.h>
#include <stdio.h>

// rank
int id;
// number of processes
int np;

int main(int argc, char *argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  // stop MPI
  MPI_Finalize();

  return 0;
}
