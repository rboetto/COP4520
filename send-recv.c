#define NOISY_RUN
#ifdef NOISY_RUN
	#define NOISY_OUTPUT printf("%i) %f %f\n", id, recv_a, recv_b);
	#define QUIET_OUTPUT
#else
	#define NOISY_OUTPUT
	#define QUIET_OUTPUT printf("%f\n", recv_a. recv_b);
#endif

#include <stdio.h>
#include <mpi.h>

int main (int argc, char ** argv) {

	MPI_Init(&argc, &argv);

	double c;
	sscanf(*(argv+1), "%lf", &c);

	int id;
	int p;

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	double send_a, send_b;
	double recv_a, recv_b;

	if (id) {
		MPI_Recv (&recv_a, 1, MPI_DOUBLE, id-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_a = (recv_a*c)+id;
		MPI_Send (&send_a, 1, MPI_DOUBLE, (id+1)%p, 0, MPI_COMM_WORLD);
		MPI_Recv (&recv_b, 1, MPI_DOUBLE, (id+1)%p, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_b = (recv_b*c)-id;
		MPI_Send (&send_b, 1, MPI_DOUBLE, id-1, 0, MPI_COMM_WORLD);
	} else {
		send_a = 0;
		MPI_Send(&send_a, 1, MPI_DOUBLE, (id+1)%p, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv_a, 1, MPI_DOUBLE, p-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		send_b = 0;
		MPI_Send(&send_b, 1, MPI_DOUBLE, p-1, 0, MPI_COMM_WORLD);
		MPI_Recv(&recv_b, 1, MPI_DOUBLE, (id+1)%p, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		QUIET_OUTPUT
	}

	NOISY_OUTPUT
}
