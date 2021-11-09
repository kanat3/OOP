#pragma once
#include "binary_signal.h"

enum Results {
	GOOD = 10,
	INPUT_ERROR = -10,
	EXCEPTION = -5,
};

namespace Menu {

	const int MENU_CHOISES = 7;

	int T_DoChoise (Binary_Signal::Binary_Signal& a);
	void PrintChoises (void);
	template <class T>
	void GetCin (T& new_T, int& error);
	template <class T>
	int GetInput (T& new_T, int& error);
	int GetChoise (void);
	int ChoiseCase (int choice, Binary_Signal::Binary_Signal& a);
}