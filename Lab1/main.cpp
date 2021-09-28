#include <iostream>
#include "sparsematrix.h"

using namespace MyInput;
using namespace MySparseMatrix;

int main (void) {
	int* new_vector;
	SparseMatrix Matrix;
	int N, M, not_null_int;
	not_null_int = 0;
	std::cout << std::endl << "Enter size of matrix (NxM):" << std::endl;
	if (GetSizeOfMatrix(N, M) < 0) {
		return INPUT_ERROR_BREAK;
	}
	if (InitMatrix(Matrix, not_null_int, N, M) < 0) {
		delete [] Matrix.IndexPointers;
		return INPUT_ERROR_BREAK;
	}
	ShowSparseMatrix(Matrix, N);
	ShowNotSparseMatrix(Matrix, N, M);
	new_vector = new int[N];
	new_vector = AskIndexElement(Matrix, N, M, new_vector);
	if (new_vector == nullptr) {
		return INPUT_ERROR_BREAK;
	}
	ShowVector(new_vector, N);
	delete [] new_vector;
	FreeMatrix(Matrix);
	return GOOD;
}