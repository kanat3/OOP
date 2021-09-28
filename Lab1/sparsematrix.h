#pragma once

enum Results {
	GOOD = 1,
	MEMORY_ERROR = -7,
	INPUT_ERROR_BREAK = -11,
	INPUT_EOF = -22
};

namespace MySparseMatrix {

	struct SparseMatrix {
		struct List* NotNull;
		struct List* IndexRow;
		int* IndexPointers;
	};

	struct List {
		int a;
		List* next;
	};

	int InitMatrix (SparseMatrix &Matrix, int& not_null_int, const int N, const int M);
	void FreeMatrix (SparseMatrix& Matrix);
	void ShowSparseMatrix (const SparseMatrix Matrix, const int N);
	void ShowNotSparseMatrix (const SparseMatrix Matrix, const int N, const int M);
	int GetSizeOfMatrix (int& N, int& M);
	int* FormingVector (SparseMatrix &Matrix, const int choice, const int N, const int M, int* new_vector);
	int* AskIndexElement (SparseMatrix &Matrix, const int N, const int M, int* new_vector);
	void ShowVector (const int* arr, const int N);
}

namespace MyInput {
	void GetInt (int& new_int, int& error);
	void GetUInt(int& size, int& error);

}