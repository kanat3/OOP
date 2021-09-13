#include <iostream>
#include "sparsematrix.h"

using namespace MyInput;
using namespace MySparseMatrix;

int main (void) {
	SparseMatrix Matrix;
	int N, M, not_null_int;
	not_null_int = 0;
	std::cout << std::endl << "Enter size of matrix (NxM):" << std::endl;
	if (GetSizeOfMatrix(N, M) < 0) {
		return -11;
	}
	if (InitMatrix(Matrix, not_null_int, N, M) < 0) {
		//delete [] Matrix.IndexPointers; //for scan-build
		return -11;
	}
	ShowSparseMatrix(Matrix, N);
	ShowNotSparseMatrix(Matrix, N, M);
	if (FindRowInSparseMatrix(Matrix, N, M) < 0) {
		//delete [] Matrix.IndexPointers; //for scan-build
		return -11;
	}
	FreeMatrix(Matrix);
	return 1;
}