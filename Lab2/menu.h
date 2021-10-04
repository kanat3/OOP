#pragma once

namespace Menu {

	const int MENU_CHOISES = 8;

	void ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a);
	void PrintChoises (void);
	template <class T>
	void GetInput (T& new_T, int& error);
	int GetChoise (void);
	void DoChoise (Lemniscata_Bernoulli::Lemniscata& a);
	void ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a);
}