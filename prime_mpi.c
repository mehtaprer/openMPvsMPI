# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main ( int argc, char *argv[] )
{
  int i;
  int id;
  int ierr;
  int n;
  int factor;
  int ub;
  int lb;
  int p;
  int isprime;
  int primes_part;
  double wtime;

  lb = 1;
  ub=1024;
  factor = 2;
/*
  Initialize MPI. // same ierr must call MPI_finalize()
*/
  ierr = MPI_Init ( &argc, &argv );
/*
  Get the number of processes.
*/
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
/*
  Determine this processes's rank.
*/
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );

  if ( id == 0 )
  {
    
    printf ( "\n" );
    printf ( "PRIME_MPI\n" );
    printf ( "         N        Pi          Time\n" );
    printf ( "\n" );
  }

  n = lb;

  while ( n <= ub )
  {
    if ( id == 0 )
    {
      wtime = MPI_Wtime ( );
    }
    ierr = MPI_Bcast ( &n, 1, MPI_INT, 0, MPI_COMM_WORLD ); //Broadcasts a message from the process with rank "root" to all other processes of the communicator 

    primes_part = prime_number ( n, id, p );

    ierr = MPI_Reduce ( &primes_part, &isprime, 1, MPI_INT, MPI_SUM, 0, 
      MPI_COMM_WORLD ); //Reduces values on all processes within a group. 

    if ( id == 0 )
    {
      wtime = MPI_Wtime ( ) - wtime;
      printf ( "  %8d  %8d  %14f\n", n, isprime, wtime );
    }
    n = n * factor;
  }
/*
  Terminate MPI.
*/
  ierr = MPI_Finalize ( );

  return 0;
}


int prime_number ( int n, int id, int p )
{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for ( i = 2 + id; i <= n; i = i + p )
  {
    prime = 1;
   
    for ( j = 2; j < i; j++ )
    {
      if ( ( i % j ) == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}


