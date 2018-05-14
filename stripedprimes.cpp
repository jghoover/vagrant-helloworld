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

  if(id==0)
  {
    std::cout << "Limit?" << std::endl;
    std::cin >> limit;
  }

  MPI_Bcast(&limit, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int count = 0;
  // each process only looks at numbers that are equal to their id mod np
  for(int i=id; i <= limit; i+=np)
  {
    if(isPrime(i))
    {
      //  std::cout << id << " says prime:" << i << std::endl;
      count++;
    }
  }
  int total;
  // each process sends their total back to root, which adds them all together to get the grand total
  MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(id==0) // then the root prints it out!
  {
    std::cout << "There are " << total << " primes less than or equal to " << limit << "." << std::endl;
  }

  // stop MPI
  MPI_Finalize();

  return 0;
}
