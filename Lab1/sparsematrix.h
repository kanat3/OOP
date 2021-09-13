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

	int InitMatrix (SparseMatrix &Matrix, int& not_null_int, int N, int M);
	void FreeMatrix (SparseMatrix& Matrix);
	void ShowSparseMatrix (SparseMatrix Matrix, int N);
	void SelectionRow (List* index_start, List* row_start, int int_count, int M, int index_row);
	int FindRowInSparseMatrix (SparseMatrix &Matrix, int N, int M);
	void ShowNotSparseMatrix (SparseMatrix &Matrix, int N, int M);
	int GetSizeOfMatrix (int& N, int& M);

}

namespace MyInput {

	void GetInt (int& new_int, int& error);
	void GetUInt(int& size, int& error);

}