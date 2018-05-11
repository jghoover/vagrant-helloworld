#include <mpi.h>
#include <stdio.h>

// compile with "mpicxx blah.cpp -o blah"
// run with "mpirun -np p blah"

int main(int argc, char *argv[])
{
  // rank (process number)
  int id;

  // number of processes
  int np;

  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  
  int baton;

  if(id==0)
  {
    std::cout << "Starting number?" << std::endl;
    std::cin >> baton;

    MPI_Send(&baton, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }

  MPI_Recv(&baton, 1, MPI_INT, (np+id-1)%np, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  std::cout << "Process " << id << " was passed the baton!" << std::endl;
  std::cout << "It's value is " << baton << "!" << std::endl;

  baton++;
  
  if(id!=0)
  {
    MPI_Send(&baton, 1, MPI_INT, (id+1)%np, 0, MPI_COMM_WORLD);
  }

  // stop MPI
  MPI_Finalize();

  return 0;
}
