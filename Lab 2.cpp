#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main() {

	int rows = 3, cols = 3;
	int** A1 = new int* [rows];
	int** A2 = new int* [rows];
	int** Result = new int* [rows];

	for (int i = 0; i < cols; i++) {
		A1[i] = new int[cols];
		A2[i] = new int[cols];
		Result[i] = new int[cols];
	}

	int A1_Values[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	int A2_Values[3][3] = { {1, 2, 1}, {2, 4, 6}, {7, 2, 5} };
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			A1[i][j] = A1_Values[i][j];
			A2[i][j] = A2_Values[i][j];
			Result[i][j] = 0;
		}
	}

	auto start = high_resolution_clock::now();

	// Normal Matrix Multiplication
	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			for (int k = 0; k < cols; k++) {
				Result[i][j] += (A1[i][k] * A2[k][j]);
			}
		}
	}*/

	// Optimized Matrix Multiplication
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++) {
			for (int j = 0; j < cols; j++) {
				Result[i][j] += (A1[i][k] * A2[k][j]);
			}
		}
	}

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	
	// Print
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << Result[i][j] << "	";
		}
		cout << endl;
	}

	cout << "Running Time = " << duration.count() << " milliseconds" << endl;

	// Deallocate memory
	for (int i = 0; i < rows; i++) {
		delete[] A1[i];
		delete[] A2[i];
		delete[] Result[i];
	}
	delete[] A1;
	delete[] A2;
	delete[] Result;

	return 0;
}