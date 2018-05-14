#include <mpi.h>
#include <stdio.h>

// rank
int id;
// number of processes
int np;


// print out each process rank (id)
void sayHello()
{
  std::cout << "Hello from process " << id << " of " << np << "!" << std::endl;
}

// pass the baton!
void relay()
{
  char *message = new char[32];

  if(id == 0)
  {
    // send a message, then wait to receive one
    strcpy("BATON", message);
    
    MPI_Send(message, 32, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
    
  }
  else
  {
    // wait to recieve a message, then send one
    MPI_Recv(message, 32, id-1, 0, MPI_COMM_WORLD);
    
  }
}


int main(int argc, char *argv[])
{
  // initialize MPI
  MPI_Init(&argc, &argv);

  // get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // get my rank (id number)
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  
  sayHello();

  relay();

  // print the number of process
  if(id==0)
  {
    std::cout << "There are " << np << " processes total!" << std::endl;
  }

  // stop MPI
  MPI_Finalize();  
}
