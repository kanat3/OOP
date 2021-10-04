#pragma once

enum Results {
	GOOD = 10,
	INPUT_ERROR = -10,
	EXCEPTION = -5,
};

namespace Menu {

	const int MENU_CHOISES = 8;

	int ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a);
	void PrintChoises (void);
	template <class T>
	void GetCin (T& new_T, int& error);
	template <class T>
	int GetInput (T& new_T, int& error);
	int GetChoise (void);
	int DoChoise (Lemniscata_Bernoulli::Lemniscata& a);
	int ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a);
}