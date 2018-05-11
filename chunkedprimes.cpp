#include <mpi.h>
#include <stdio.h>
#include <cmath>

// rank
int id;
// number of processes
int np;

bool isPrime(int n)
{
  if(n==2)
  {
    return true;
  }
  if((n<2) || (n%2==0))
  {
    return false;
  }

  for(int i=3; i < ceil(sqrt(n))+1; i+=2)
  {
    if(n%i == 0)
    {
      return false;
    }
  }

  return true;
}


int main(int argc, char *argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // get my rank
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  int limit;
  int start;
  int stop;

  if(id==0)
  {
    std::cout << "Limit?" << std::endl;
    std::cin >> limit;
  }

  MPI_Bcast(&limit, 1, MPI_INT, 0, MPI_COMM_WORLD);

  // compute each starting and stopping point
  start = floor((double)(limit)/np)*id;
  stop = floor((double)(limit)/np)*(id+1);
  if(stop > limit)
  {
    stop = limit;
  }

  //  std::cout << "rank:" << id << " start:" << start << " stop:" << stop << std::endl;

  int count = 0;
  for(int i=start; i < stop; i++)
  {
    if(isPrime(i))
    {
      //  std::cout << id << " says prime:" << i << std::endl;
      count++;
    }
  }
  int total;
  MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(id==0)
  {
    std::cout << "There are " << total << " primes less than or equal to " << limit << "." << std::endl;
  }

  // stop MPI
  MPI_Finalize();

  return 0;
}
