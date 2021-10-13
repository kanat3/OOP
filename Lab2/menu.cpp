#include <iostream>
#include "Lemniscata.h"
#include "menu.h"

namespace Menu {

	void PrintChoises (void) {
		std::cout << "=============This is lab for Lemniscata Bernoulli functions=============" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Enter the distance between the focuses" << std::endl;
		std::cout << "2. Return the distance to the center depending on the angle" << std::endl;
		std::cout << "3. Return the radius of curvature depending on the angle" << std::endl;
		std::cout << "4. Return the radius of curvature as a function of the length" << std::endl;
		std::cout << "5. Return the area of the polar sector depending on the angle" << std::endl;
		std::cout << "6. Return the square" << std::endl;
		std::cout << "7. Show Lemniscata data" << std::endl;
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
			GetCin(new_T, error);
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
			GetInput(choice, ERROR);
		} while (ERROR == 2 || choice < 0 || choice > MENU_CHOISES);
		if (!ERROR) {
			return INPUT_ERROR;
		} else {
			return choice;
		}
	}

	int DoChoise (Lemniscata_Bernoulli::Lemniscata& a) {
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

	int ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a) {
		if (choice == 1) {
			std::cout << "Lemniscate's equation: (x^2 + y^2)^2 = 2*c^2(x^2 - y^2)" << std::endl;
			double db;
			int ERROR;
			std::cout << "Enter c: ";
			if (!GetInput(db, ERROR)) {
				return INPUT_ERROR;
			}
			try {
				a.SetDistance(db);
			} catch (std::invalid_argument) {
				std::cout << "Exception: Invalid value" << std::endl;
				return EXCEPTION;
			}
			std::cout << "Your distance: " << a.GetDistance() << std::endl;
		} else if (choice == 2) {
			int ERROR;
			std::cout << "Enter the angle (in grad):";
			double angle;
			if (!GetInput(angle, ERROR)) {
				return INPUT_ERROR;
			}
			std::cout << "Your distance to the center: " << a.DistanceToTheCenter(angle) << std::endl;
		} else if (choice == 3) {
			int ERROR;
			std::cout << "Enter the angle (in grad):";
			double angle;
			if (!GetInput(angle, ERROR)) {
				return INPUT_ERROR;
			}
			std::cout << "Your radius of curvature depending on the angle: " << a.RadiusOfCurvature_ByAngle(angle) << std::endl;
		} else if (choice == 4) {
			int dist, ERROR;
			double result;
			std::cout << "Enter distance to the center: ";
			if (!GetInput(dist, ERROR)) {
				return INPUT_ERROR;
			}
			try {
				result = a.RadiusOfCurvature_ByLength(dist);
			} catch (std::invalid_argument) {
				std::cout << "Exception: Invalid value" << std::endl;
				return EXCEPTION;
			}
			std::cout << "Your radius of curvature depending on the distance to the center: " << result << std::endl;
		} else if (choice == 5) {
			int ERROR;
			std::cout << "Enter the angle (in grad):";
			double angle;
			if (!GetInput(angle, ERROR)) {
				return INPUT_ERROR;
			}
			std::cout << "Your area of the polar sector depending on the angle: " << a.AreaOfTheSector(angle) << std::endl;
		} else if (choice == 6) {
			std::cout << "Your area of Lemniscata: " << a.Area() << std::endl;
		} else if (choice == 7) {
			std::cout << std::endl << "=== C is: " << a.GetDistance() << std::endl << std::endl;
		}
		return GOOD;
	}

}