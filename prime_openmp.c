# include <stdlib.h>
# include <stdio.h>
# include <omp.h>


void display( int lb, int ub, int factor )
 { 
 int i;
  int n;
  int isprime;
  double time;

  printf( "\n" );
  printf( "  count of primes from 1 to N.\n" );
  printf( "\n" );
  printf( "         N        #prime nos          Time\n" );
  printf( "\n" );

  n = lb;

  while( n <= ub )
  {
    time = omp_get_wtime( ); //Elapsed wall clock time in seconds

    isprime = prime_number( n );

    time = omp_get_wtime( ) - time;

    printf( "  %8d  %8d  %14f\n", n, isprime, time );

    n = n * factor;
  }
 
  
}


int prime_number( int n )
{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel \
  shared( n ) \
  private( i, j, prime )
  

# pragma omp for reduction( + : total )
  for( i = 2; i <= n; i++ )
  {
    prime = 1;

    for( j = 2; j < i; j++ )
    {
      if( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}

int main( int argc, char *argv[] )
{
  int factor;
  int ub;
  int lb;

  printf( "\n" );
  printf( "PRIME OPENMP\n" );
  lb = 1;
  ub = 1024;
  factor = 2;

  display( lb, ub, factor );
  return 0;
}

