#include <iostream>
#include <cstring>
#include "menu.h"
#include "binary_signal.h"

namespace Menu {

	void PrintChoises (void) {
		std::cout << "=============This is lab for Binary Signal functions=============" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Set signal" << std::endl;
		std::cout << "2. Set signal in the define time" << std::endl;
		std::cout << "3. Signal inversion" << std::endl;
		std::cout << "4. Add new signal" << std::endl;
		std::cout << "5. Delete signal in the define time" << std::endl;
		std::cout << "6. Show class" << std::endl;
		std::cout << "7. New class" << std::endl;
	}

	template <class T>
	void GetCin (T& new_T, int& error) {
		error = 1;
		while (1) {
			std::cin >> new_T;
			if (std::cin.eof()) {
				std::cout << "End" << std::endl;
				error = 0;
				break;
			}
			if (std::cin.fail()) {
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

	template <class T>
	int GetInput (T& new_T, int& error) {
		do {
			Menu::GetCin(new_T, error);
		} while (error == 2);
		if (!error) {
			return 0;
		}
		return 1;
	}

	int GetChoise (void) {
		int ERROR, choice;
		ERROR = choice = 0;
		do {
			Menu::GetInput(choice, ERROR);
		} while (ERROR == 2 || choice < 0 || choice > MENU_CHOISES);
		if (!ERROR) {
			return INPUT_ERROR;
		} else {
			return choice;
		}
	}

	int T_DoChoise (Binary_Signal::Binary_Signal& a) {
		int choice = 0;
		int error = 0;
		do {
			Menu::PrintChoises();
			choice = Menu::GetChoise();
			if (choice == INPUT_ERROR) {
				break;
			}
			error = Menu::ChoiseCase(choice, a);
			if (error == INPUT_ERROR) {
				break;
			}
		} while (choice != 0);
		if (error == INPUT_ERROR) {
			return INPUT_ERROR;
		} else {
			return GOOD;
		}
	}

	int ChoiseCase (int choice, Binary_Signal::Binary_Signal& a) {
		if (choice == 1) {
			int ERROR;
			int level;
			std::string str;
			std::cout << "Enter level: ";
			if (!GetInput(level, ERROR)) {
				return INPUT_ERROR;
			}
			std::cout << "Enter duration: ";
			if (!GetInput(str, ERROR)) {
				return INPUT_ERROR;
			}
			if (str.length() > Binary_Signal::MAX_DURATION) {
				str.erase(Binary_Signal::MAX_DURATION, str.length() - Binary_Signal::MAX_DURATION);
			}
			a.SetSignal(level, str.c_str());
		} else if (choice == 2) {
			Binary_Signal::Binary_Signal b;
			b.Test_Class();
			std::cout << "Test signal:" << std::endl;
			b.ShowClass();
			int ERROR;
			int time;
			std::cout << "Enter time: ";
			if (!GetInput(time, ERROR)) {
				return INPUT_ERROR;
			}
			a.SetSignalInTime(time, b);
			std::cout << "Your first signal now:" << std::endl;
			a.ShowClass();
		} else if (choice == 3) {
			a.SignalInversion();
		} else if (choice == 4) {
			Binary_Signal::Binary_Signal b;
			b.Test_Class();
			std::cout << "Test signal:" << std::endl;
			b.ShowClass();
			a.SignalAddition(b);
			std::cout << "Your first signal now:" << std::endl;
			a.ShowClass();
		} else if (choice == 5) {
			int ERROR;
			int time;
			std::string str;
			std::cout << "Enter time: ";
			if (!GetInput(time, ERROR)) {
				return INPUT_ERROR;
			}
			if (!GetInput(str, ERROR)) {
				return INPUT_ERROR;
			}
			if (str.length() > Binary_Signal::MAX_DURATION) {
				str.erase(Binary_Signal::MAX_DURATION, str.length() - Binary_Signal::MAX_DURATION);
			}
			a.DeleteSignal(time, str.c_str());
		} else if (choice == 6) {
			std::cout << "You are working with signal A" << std::endl;
			a.ShowClass();
		} else if (choice == 7) {
			a.FreeClass();
		}
		return GOOD;
	}

}