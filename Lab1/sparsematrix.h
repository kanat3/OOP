#pragma once

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
	void SelectionRow (List* index_start, List* row_start, const int int_count, const int M, const int index_row);
	int FindRowInSparseMatrix (SparseMatrix &Matrix, const int N, const int M);
	void ShowNotSparseMatrix (const SparseMatrix Matrix, const int N, const int M);
	int GetSizeOfMatrix (int& N, int& M);

}

namespace MyInput {

	void GetInt (int& new_int, int& error);
	void GetUInt(int& size, int& error);

}