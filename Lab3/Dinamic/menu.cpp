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
		std::cout << "4. Copy signal" << std::endl;
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
			puts("\n1. Enter the signal as a string (If the signal exists it will be deleted)");
			puts("2. Enter the one signal with level and duration (If the signal exists it will be added in the end)");
			puts("3. Just use test signal\n");
			puts("Make your choice: ");
			int format_input;
			do {
				Menu::GetInput(format_input, ERROR);
			} while (ERROR == 2 || (format_input < 1 && format_input > 3));
			if (!ERROR) {
				return INPUT_ERROR;
			}
			if (format_input == 1) {
				a.FreeClass();
				std::cout << "\nEnter signal like that -> Example: 15021104, 1 - level, 5 - duration, 0 - level etc." << std::endl;
				std::string str;
				if (!GetInput(str, ERROR)) {
					return INPUT_ERROR;
				}
				try {
					a.SetSignal(str.c_str());
				} catch (std::invalid_argument) {
					std::cout << "Exception: Invalid value" << std::endl;
					return EXCEPTION;
				}
			}
			if (format_input == 2) {
				int level;
				char duration;
				std::cout << "Enter level: ";
				if (!GetInput(level, ERROR)) {
					return INPUT_ERROR;
				}
				std::cout << "Enter duration: ";
				if (!GetInput(duration, ERROR)) {
					return INPUT_ERROR;
				}
				a.SetSignal(level, duration);
			}
			if (format_input == 3) {
				puts("Generation.....");
				a.SetSignal(Binary_Signal::STANDART_SIGNAL);
				puts("Ok");
			}
		} else if (choice == 2) {
			Binary_Signal::Binary_Signal b;
			b.SetSignal(Binary_Signal::STANDART_SIGNAL);
			std::cout << "Test signal:" << std::endl;
			b.ShowClassAsString();
			int ERROR;
			int time;
			std::cout << "Enter time: ";
			if (!GetInput(time, ERROR)) {
				return INPUT_ERROR;
			}
			try {
				a.SetSignalInTime(time, b);
			} catch (std::invalid_argument) {
				std::cout << "Exception: Invalid value" << std::endl;
				return EXCEPTION;
			}
			std::cout << "Your first signal now:" << std::endl;
			a.ShowClassAsString();
		} else if (choice == 3) {
			a.SignalInversion();
		} else if (choice == 4) {
			int ERROR;
			puts("\n1. Copy your signal once");
			puts("2. Copy your signal multiple");
			puts("3. Copy test signal");
			puts("4. Copy test signal multiple\n");
			puts("Make your choice: ");
			int format_input;
			do {
				Menu::GetInput(format_input, ERROR);
			} while (ERROR == 2 || (format_input < 1 && format_input > 4));
			if (!ERROR) {
				return INPUT_ERROR;
			}
			if (format_input == 1) {
				Binary_Signal::Binary_Signal b(a);
				puts("Your temporary object:");
				b.ShowClassAsString();
			} else if (format_input == 2) {
				puts("Enter the number of copies:");
				int N;
				do {
					Menu::GetInput(N, ERROR);
				} while (ERROR == 2 || N < 1);
				if (!ERROR) {
					return INPUT_ERROR;
				}
				try {
					Binary_Signal::Binary_Signal b(a, N);
					puts("Your temporary object:");
					b.ShowClassAsString();
				} catch (std::invalid_argument) {
					std::cout << "Exception: Invalid value" << std::endl;
					return EXCEPTION;
				}
			} else if (format_input == 3) {
				Binary_Signal::Binary_Signal c;
				puts("Generation........");
				c.SetSignal(Binary_Signal::STANDART_SIGNAL);
				Binary_Signal::Binary_Signal b(c);
				std::cout << "Your temporary object:" << std::endl;
				b.ShowClassAsString();
			} else if (format_input == 4) {
				puts("Enter the number of copies:");
				int N;
				do {
					Menu::GetInput(N, ERROR);
				} while (ERROR == 2 || N < 1);
				if (!ERROR) {
					return INPUT_ERROR;
				}
				Binary_Signal::Binary_Signal c;
				puts("Generation........");
				c.SetSignal(Binary_Signal::STANDART_SIGNAL);
				Binary_Signal::Binary_Signal b(c);
				std::cout << "Your temporary object:" << std::endl;
				b.ShowClassAsString();
			}
		} else if (choice == 5) {
			int ERROR;
			int time;
			char str;
			std::cout << "Enter time: ";
			if (!GetInput(time, ERROR)) {
				return INPUT_ERROR;
			}
			std::cout << "Enter signal duration: ";
			if (!GetInput(str, ERROR)) {
				return INPUT_ERROR;
			}
			puts("Trying to delete.....");
			a.DeleteSignal(time, str);
			puts("Result\n");
			a.ShowClassAsString();
		} else if (choice == 6) {
			std::cout << "\nYou are working with this signal:" << std::endl;
			a.ShowClassAsString();
		} else if (choice == 7) {
			a.FreeClass();
		}
		return GOOD;
	}
}