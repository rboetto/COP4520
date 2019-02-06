#include <stdio.h>
#include <mpi.h>

int main (int argc, char ** argv) {

	MPI_Init(&argc, &argv);

	int id;
	int p;

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Status status;
	int recv_a, recv_b;

	MPI_Sendrecv(&id, 1, MPI_INT, (id+1)%p, 0, &recv_a, 1, MPI_INT, id > 0 ? id-1 : p-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	MPI_Sendrecv(&id, 1, MPI_INT, id > 0 ? id-1 : p-1, 0, &recv_b, 1, MPI_INT, (id+1)%p, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	printf("%i:%i\n", id, id+recv_a+recv_b); 

	MPI_Finalize();
}
