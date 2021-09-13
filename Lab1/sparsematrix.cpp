#include <iostream>
#include "sparsematrix.h"

namespace MyInput {

	using namespace std;

	void GetInt (int& new_int, int& error) {
		error = 1;
		while (1) {
			cin >> new_int;
			if (cin.eof()) {
				cout << "End" << endl;
				error = 0;
				break;
			}
			if (cin.fail()) {
				cout << "Incorrect input. Try again" << endl;
				cin.clear();
				while(cin.get()!='\n');
				error = 2;
			} else {
				cin.clear();
				while(cin.get()!='\n');
				error = 1;
				break;
			}
		}
	}

	void GetUInt(int& size, int& error) {
		while (1) {
			GetInt(size, error);
			if(!error) {
				break;
			}
			if (size <= 0) {
				cout << "Incorrect input. Try again" << endl;
			} else {
				break;
			}
		}
	}
}

namespace MySparseMatrix {

	using namespace std;

	int InitMatrix (SparseMatrix &Matrix, int& not_null_int, int N, int M) {
		List* head = nullptr;
		List* head2 = nullptr;
		List* ptr1 = nullptr;
		List* ptr2 = nullptr;
		Matrix.IndexPointers = new int[N + 1];
		Matrix.IndexPointers[0] = 0;
		not_null_int = 0;
		int index_row;
		int index_pointers = 0;
		int data;
		int INPUT_ERROR = 1;
		for (int i = 0; i < N; i++) {
			index_row = -1;
			cout << "Enter new row of matrix (NxM):" << endl;
			for (int j = 0; j < M; j++) {
				do {
					MyInput::GetInt(data, INPUT_ERROR);
				} while (INPUT_ERROR == 2);
				if (INPUT_ERROR == 0) { //exit from for1 -> eof
					INPUT_ERROR = -22;
					break;
				}
				index_row++;
				if (data) {
					if (ptr1 == nullptr) {
						ptr1 = new List;
						ptr2 = new List;
						ptr1->a = data;
						ptr2->a = index_row;
						ptr1->next = nullptr;
						ptr2->next = nullptr;
						head = ptr1;
						head2 = ptr2;
					} else {
						while (ptr1->next) {
							ptr1 = ptr1->next;
						}
						while (ptr2->next) {
							ptr2 = ptr2->next;
						}
						ptr1->next = new List;
						ptr1->next->a = data;
						ptr1->next->next = nullptr;
						ptr1 = ptr1->next;
						ptr2->next = new List;
						ptr2->next->a = index_row;
						ptr2->next->next = nullptr;
						ptr2 = ptr2->next;
					}
					index_pointers++;
					not_null_int++;
				}
			Matrix.IndexPointers[i+1] = index_pointers;
			}
		}
		if (INPUT_ERROR == -22) {
			return -22; // eof, exit
		}
		Matrix.NotNull = head;
		Matrix.IndexRow = head2;
		return 22;
	}

	void FreeMatrix (SparseMatrix& Matrix) {
		List* to_delete = nullptr;
		delete [] Matrix.IndexPointers;
		while (Matrix.NotNull) {
			to_delete = Matrix.NotNull;
			Matrix.NotNull = Matrix.NotNull->next;
			delete to_delete;
		}
		while (Matrix.IndexRow) {
			to_delete = Matrix.IndexRow;
			Matrix.IndexRow = Matrix.IndexRow->next;
			delete to_delete;
		}
	}

	void ShowSparseMatrix (SparseMatrix Matrix, int N) {
		List* print = Matrix.NotNull;
		List* index = Matrix.IndexRow;
		cout << endl << "Data:" << endl;
		while (print) {
			cout << print->a << " ";
			print = print->next;
		}
		std::cout << endl << "Pointers:" << endl;
		for (int i = 0; i < N + 1; i++) {
			cout << Matrix.IndexPointers[i] << " ";
		}
		cout << endl << "Index:" << endl;
		while (index) {
			cout << index->a << " ";
			index = index->next;
		}
		cout << std::endl;
	}

	void SelectionRow (List* index_start, List* row_start, int int_count, int M, int index_row) { //int x1x2
		int sum = 0;
		int* new_row = new int [M];
		for (int i = 0; i < M; i++) {
			new_row[i] = 0;
		}
		for (int k = 0; k < int_count; k++) {
			if (row_start && ((row_start->a > 9 && row_start->a < 100) || (row_start->a < -9 && row_start->a > -100))) {
				sum += row_start->a;
			}
			if (row_start && index_start) {
				row_start = row_start->next;
				index_start = index_start->next;
			}
		}
		new_row[index_row - 1] = sum;
		cout << endl << "new row: " << endl;
		for (int i = 0; i < M; i++) {
			cout << new_row[i] << " ";
		}
		delete [] new_row;
	}

	int FindRowInSparseMatrix (SparseMatrix &Matrix, int N, int M) {
		int index_row = -1;
		int INPUT_ERROR;
		cout << endl << "Enter row to find:" << endl;
		do {
			MyInput::GetInt(index_row, INPUT_ERROR);
		} while (INPUT_ERROR == 2);
		if (!INPUT_ERROR) {
			return -22;
		}
		if (index_row > N || index_row <= 0) {
			cout << "There no this row" << endl;
			return 11;
		}
		List* start = Matrix.NotNull;
		List* index_start = Matrix.IndexRow;
		int int_count = Matrix.IndexPointers[index_row] - Matrix.IndexPointers[index_row - 1];
		if (int_count == 0) {
			cout << "Row has only nulls" << endl;
		} else {
			for (int i = 0; i < Matrix.IndexPointers[index_row - 1]; i++) {
				if (start && index_start) {
					start = start->next;
					index_start = index_start->next;
				}
			}
			SelectionRow(index_start, start, int_count, M, index_row + 1);
		}
		cout << endl << endl;
		return 22;
	}

	void ShowNotSparseMatrix (SparseMatrix &Matrix, int N, int M) {
		cout << endl << "Your matrix:" << endl;
		int prev_index;
		List* index = Matrix.IndexRow;
		List* data = Matrix.NotNull;
		for (int row = 0; row < N; row++) {
			prev_index = -1;
			int int_count_in_the_row = Matrix.IndexPointers[row + 1] - Matrix.IndexPointers[row];
			cout << "==" << row + 1 << "==  ";
			for (int i = 0; i < int_count_in_the_row; i++) {
				if (index) {
					for (prev_index; prev_index < index->a - 1; prev_index++) {
						cout << " 0 ";
					}
				}
				if (data) {
					cout << " " << data->a << " ";
				}
				if (index && data) {
					prev_index = index->a;
					index = index->next;
					data = data->next;
				}
			}
			for (prev_index; prev_index < M - 1; prev_index++) {
				cout << " 0 ";
			}
			cout << endl;
		}
	}

	int GetSizeOfMatrix (int& N, int& M) {
		int INPUT_ERROR;
		MyInput::GetUInt(N, INPUT_ERROR);
		if(!INPUT_ERROR) {
			return -11;
		}
		MyInput::GetUInt(M, INPUT_ERROR);
		if(!INPUT_ERROR) {
			return -11;
		}
		return 11;
	}
}