# openMPvsMPI

compile openMP:
$ gcc -fopenmp -o tt prime_openmp.c
$ ./tt

compile MPI:
$ mpicc prime_mpi.c -o hello -lm
$ ./hello
