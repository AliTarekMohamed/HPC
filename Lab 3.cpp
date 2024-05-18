#include <iostream>
#include <mpi.h>
using namespace std;
int main(){

	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int data = 1, source = 1, destination = 1;

	if (rank == 0) {
		source = destination = 1;

		MPI_Send(&data, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);

		MPI_Status stat;
		MPI_Recv(&data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &stat);
		cout << "Pong" << endl;
	}
	else if (rank == 1) {
		source = destination = 0;

		MPI_Status stat;
		MPI_Recv(&data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &stat);
		cout << "Ping" << endl;

		MPI_Send(&data, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;
}