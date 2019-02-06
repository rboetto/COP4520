#define QUIET_OUTPUT printf("%f\n%f\n", recv_a, recv_b);

#include <stdio.h>
#include <mpi.h>

int main (int argc, char ** argv) {

	MPI_Init(&argc, &argv);

	int id;
	int p;

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	double send_a = id;
	double send_b = -id;
	double recv_a, recv_b;

	MPI_Reduce(&send_a, &recv_a, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&send_b, &recv_b, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (!id) printf("%f\n%f\n", recv_a, recv_b);

	MPI_Finalize();
}
