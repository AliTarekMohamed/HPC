#include <iostream>
#include <mpi.h>
using namespace std;
int main() {

	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int source, dest;

	if (rank == 0) {
		int data = 792003;
		source = 3;  dest = 1;
		
		MPI_Status status;
		MPI_Send(&data, 6, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
		MPI_Recv(&data, 6, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);

		cout << "Processor" << rank << " : " << data << endl;
	}
	else if (rank == 1) {
		int data;
		source = 0; dest = 2;
		
		MPI_Status status;
		MPI_Recv(&data, 6, MPI_CHAR, source, 0, MPI_COMM_WORLD,  &status);
		MPI_Send(&data, 6, MPI_CHAR, dest, 0, MPI_COMM_WORLD);

		cout << "Processor" << rank << " : " << data << endl;
	}
	else if (rank == 2) {
		int data;
		source = 1; dest = 3;
		
		MPI_Status status;
		MPI_Recv(&data, 6, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&data, 6, MPI_CHAR, dest, 0, MPI_COMM_WORLD);

		cout << "Processor" << rank << " : " << data << endl;
	}
	else if (rank == 3) {
		int data;
		source = 2; dest = 0;

		MPI_Status status;
		MPI_Request request;
		MPI_Recv(&data, 6, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);
		MPI_Isend(&data, 6, MPI_CHAR, dest, 0, MPI_COMM_WORLD, &request);

		cout << "Processor" << rank << " : " << data << endl;
	}

	MPI_Finalize();
	return 0;
}