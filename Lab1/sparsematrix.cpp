#include <iostream>
#include "sparsematrix.h"

namespace MyInput {

	void GetInt (int& new_int, int& error) {
		error = 1;
		while (1) {
			std::cin >> new_int;
			if (std::cin.eof()) {
				std::cout << "End" << std::endl;
				error = 0;
				break;
			}
			if (std::cin.fail()) {
				std::cout << "Incorrect input. Try again" << std::endl;
				std::cin.clear();
				while(std::cin.get()!='\n');
				error = 2;
			} else {
				std::cin.clear();
				while(std::cin.get()!='\n');
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
				std::cout << "Incorrect input. Try again" << std::endl;
			} else {
				break;
			}
		}
	}
}

namespace MySparseMatrix {

	int InitMatrix (SparseMatrix &Matrix, int& not_null_int, const int N, const int M) {
		List* head = nullptr;
		List* head2 = nullptr;
		List* ptr1 = nullptr;
		List* ptr2 = nullptr;
		try {
			Matrix.IndexPointers = new int[N + 1];
		}
			catch (std::bad_alloc)
		{
			std::cerr << "Memory error" << std::endl;
			return MEMORY_ERROR;
		}
		Matrix.IndexPointers[0] = 0;
		not_null_int = 0;
		int index_row;
		int index_pointers = 0;
		int data;
		int MEMORY_ERROR = 0;
		int INPUT_ERROR = 1;
		for (int i = 0; i < N; i++) {
			index_row = -1;
			std::cout << "Enter new row of matrix (NxM):" << std::endl;
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
						try {
							ptr1 = new List;
						}
							catch (std::bad_alloc)
						{
							std::cerr << "Memory error" << std::endl;
							MEMORY_ERROR = 1;
							break;
						}
						try {
							ptr2 = new List;
						}
							catch (std::bad_alloc)
						{
							std::cerr << "Memory error" << std::endl;
							MEMORY_ERROR = 1;
							break;
						}
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
					if (MEMORY_ERROR) {
						break;
					}
					index_pointers++;
					not_null_int++;
				}
			if (MEMORY_ERROR) {
				break;
			}
			Matrix.IndexPointers[i+1] = index_pointers;
			}
		}
		if (MEMORY_ERROR) {
			return MEMORY_ERROR;
		}
		if (INPUT_ERROR == -22) {
			List* to_delete = nullptr;
			while (head) {
				to_delete = head;
				head = head->next;
				delete to_delete;
			}
			while (head2) {
				to_delete = head2;
				head2 = head2->next;
				delete to_delete;
			}
			return INPUT_EOF; // eof, exit
		}
		Matrix.NotNull = head;
		Matrix.IndexRow = head2;
		return GOOD;
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

	void ShowSparseMatrix (const SparseMatrix Matrix, const int N) {
		List* print = Matrix.NotNull;
		List* index = Matrix.IndexRow;
		std::cout << std::endl << "Data:" << std::endl;
		while (print) {
			std::cout << print->a << " ";
			print = print->next;
		}
		std::cout << std::endl << "Pointers:" << std::endl;
		for (int i = 0; i < N + 1; i++) {
			std::cout << Matrix.IndexPointers[i] << " ";
		}
		std::cout << std::endl << "Index:" << std::endl;
		while (index) {
			std::cout << index->a << " ";
			index = index->next;
		}
		std::cout << std::endl;
	}

	int Selection1 (int a) {
		if ((a >= 1 && a <= 9) || (a <= -1 && a >= -9)) {
			return 1;
		} else {
			return 0;
		}
	}

	int Selection2 (int a) {
		if ((a >= 10 && a <= 99) || (a <= -10 && a >= -99)) {
			return 1;
		} else {
			return 0;
		}
	}

	int Selection3 (int a) {
		if ((a >= 100 && a <= 999) || (a <= -100 && a >= -999)) {
			return 1;
		} else {
			return 0;
		}
	}

	int* FormingVector (SparseMatrix &Matrix, const int choice, const int N, const int M, int* new_vector) {
		int result;
		int sum;
		List* data = Matrix.NotNull;
		List* indexes = Matrix.IndexRow;
		int int_count;
		int (*Selection[3])(int a) = {Selection1, Selection2, Selection3};
		for (int i = 0; i < N; i++) {
			sum = 0;
			int_count = Matrix.IndexPointers[i + 1] - Matrix.IndexPointers[i];
			for (int j = 0; j < int_count; j++) {
				result = Selection[choice - 1](data->a);
				if (result) {
					sum += data->a;
				}
				data = data->next;
				indexes = indexes->next;
			}
			new_vector[i] = sum;
		}
		return new_vector;
	}

	int* AskIndexElement (SparseMatrix &Matrix, const int N, const int M, int* new_vector) {
		int choice;
		int INPUT_ERROR;
		std::cout << std::endl << "Enter 1: Find elements in i row that more than 1 and less than 9:" << std::endl;
		std::cout << "Enter 2: Find elements in i row that more than 10 and less than 99:" << std::endl;
		std::cout << "Enter 3: Find elements in i row that more than 100 and less than 999:" << std::endl;
		std::cout << std::endl << "Your choice:" << std::endl;
		do {
			MyInput::GetInt(choice, INPUT_ERROR);
		} while (INPUT_ERROR == 2 || (choice <= 0 || choice >= 4));
		if (!INPUT_ERROR) {
			return nullptr;
		}
		FormingVector(Matrix, choice, N, M, new_vector);
		return new_vector;
	}

	void ShowVector (const int* arr, const int N) {
		std::cout << std::endl << "Your vector:" << std::endl;
		for (int t = 0; t < N; t++) {
			std::cout << arr[t] << " ";
		}
		std::cout << std::endl;
	}

	void ShowNotSparseMatrix (const SparseMatrix Matrix, const int N, const int M) {
		std::cout << std::endl << "Your matrix:" << std::endl;
		int prev_index;
		List* index = Matrix.IndexRow;
		List* data = Matrix.NotNull;
		for (int row = 0; row < N; row++) {
			prev_index = -1;
			int int_count_in_the_row = Matrix.IndexPointers[row + 1] - Matrix.IndexPointers[row];
			std::cout << "==" << row + 1 << "==  ";
			for (int i = 0; i < int_count_in_the_row; i++) {
				if (index) {
					for (prev_index; prev_index < index->a - 1; prev_index++) {
						std::cout << " 0 ";
					}
				}
				if (data) {
					std::cout << " " << data->a << " ";
				}
				if (index && data) {
					prev_index = index->a;
					index = index->next;
					data = data->next;
				}
			}
			for (prev_index; prev_index < M - 1; prev_index++) {
				std::cout << " 0 ";
			}
			std::cout << std::endl;
		}
	}

	int GetSizeOfMatrix (int& N, int& M) {
		int INPUT_ERROR;
		MyInput::GetUInt(N, INPUT_ERROR);
		if(!INPUT_ERROR) {
			return INPUT_ERROR_BREAK;
		}
		MyInput::GetUInt(M, INPUT_ERROR);
		if(!INPUT_ERROR) {
			return INPUT_ERROR_BREAK;
		}
		return GOOD;
	}
}