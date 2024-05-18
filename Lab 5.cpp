#include <iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);
	
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 ,10, 11, 12, 13, 14, 15 };
		int final_sum = 0;

		MPI_Send(&data[5], 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&data[10], 5, MPI_INT, 2, 0, MPI_COMM_WORLD);

		for (int i = 0; i < 5; i++) {
			final_sum += data[i];
		}

		int sum1, sum2;
		MPI_Status status;
		MPI_Recv(&sum1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&sum2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);

		final_sum += sum1 + sum2;

		cout << "Final Sum = " << final_sum << endl;
	}
	else if (rank < 3) {
		int data[5], sum = 0;

		MPI_Status status;
		MPI_Recv(data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		for (int i = 0; i < 5; i++) {
			sum += data[i];
		}

		MPI_Request request;
		MPI_Isend(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
	}

	MPI_Finalize();
	return 0;
}