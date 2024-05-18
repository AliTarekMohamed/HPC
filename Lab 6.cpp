#include <iostream>
#include <mpi.h>
using namespace std;
int main() {
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int local_data[5], local_sum = 0;
	int final_sum = 0, sums[16];

	MPI_Scatter(data, 5, MPI_INT, local_data, 5, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < 5; i++) {
		local_sum += local_data[i];
	}

	MPI_Gather(&local_sum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (int i = 0; i < 3; i++) {
			final_sum += sums[i];
		}
		cout << "Final Sum = " << final_sum << endl;
	}

	MPI_Finalize();
	return 0;
}