#include <iostream>
#include <mpi.h>
using namespace std;

#define n 100

int main() {
	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int local_sum = 0, final_sum = 0;
	int* a = new int[n];
	int* b = new int[n];
	int* sub_a = new int[n / size];
	int* sub_b = new int[n / size];

	if (rank == 0) {
		for (int i = 0; i < n; i++) {
			a[i] = 2;
			b[i] = 3;
		}
	}
	
	MPI_Scatter(a, n / size, MPI_INT, sub_a, n / size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, n / size, MPI_INT, sub_b, n / size, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < n / size; i++) {
		local_sum += (sub_a[i] * sub_b[i]);
	}

	MPI_Reduce(&local_sum, &final_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (int i = n - (n % size); i < n; i++) {
			final_sum += (a[i] * b[i]);
		}

		cout << "Final sum = " << final_sum << endl;
	}

	MPI_Finalize();
	return 0;
}