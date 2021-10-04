#include <iostream>
#include "Lemniscata.h"
#include "menu.h"

namespace Menu {

	void PrintChoises (void) {
		std::cout << "=============This is lab for Lemniscata Bernoulli functions=============" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Enter the distance between the focuses" << std::endl;
		std::cout << "2. Enter the angle" << std::endl;
		std::cout << "3. Return the distance to the center depending on the angle" << std::endl;
		std::cout << "4. Return the radius of curvature depending on the angle" << std::endl;
		std::cout << "5. Return the radius of curvature as a function of the length" << std::endl;
		std::cout << "6. Return the area of the polar sector depending on the angle" << std::endl;
		std::cout << "7. Return the square" << std::endl;
		std::cout << "8. Show Lemniscata data" << std::endl;
	}

	template <class T>
	void GetInput (T& new_T, int& error) {
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

	int GetChoise (void) {
		int ERROR;
		int choice;
		do {
			GetInput(choice, ERROR);
		} while (ERROR == 2 || choice < 0 || choice > MENU_CHOISES);
		if (!ERROR) {
			return -1;
		} else {
			return choice;
		}
	}

	void DoChoise (Lemniscata_Bernoulli::Lemniscata& a) {
		int choice;
		do {
			Menu::PrintChoises();
			choice = Menu::GetChoise();
			Menu::ChoiseCase(choice, a);
		} while (choice != 0);
	}

	void ChoiseCase (int choice, Lemniscata_Bernoulli::Lemniscata& a) {
		if (choice == 1) {
			std::cout << "Lemniscate's equation: (x^2 + y^2)^2 = 2*c^2(x^2 - y^2)" << std::endl;
			double db;
			int ERROR;
			std::cout << "Enter c: ";
			GetInput(db, ERROR);
			a.SetDistance(db);
			std::cout << "Your distance: " << a.GetDistance() << std::endl;
		} else if (choice == 2) {
			int ERROR;
			std::cout << "Enter the angle (in grad):";
			double angle;
			GetInput(angle, ERROR);
			a.SetAngle(angle);
			std::cout << "Your angle: " << a.GetAngle() << std::endl;
		} else if (choice == 3) {
			std::cout << "Your distance to the center: " << a.DistanceToTheCenter(a.GetAngle()) << std::endl;
		} else if (choice == 4) {
			std::cout << "Your radius of curvature depending on the angle: " << a.RadiusOfCurvature_ByAngle(a.GetAngle()) << std::endl;
		} else if (choice == 5) {
			int dist, ERROR;
			std::cout << "Enter distance to the center: ";
			GetInput(dist, ERROR);
			std::cout << "Your radius of curvature depending on the distance to the center: " << a.RadiusOfCurvature_ByLength(dist) << std::endl;
		} else if (choice == 6) {
			std::cout << "Your area of the polar sector depending on the angle: " << a.AreaOfTheSector(a.GetAngle()) << std::endl;
		} else if (choice == 7) {
			std::cout << "Your area of Lemniscata: " << a.Area() << std::endl;
		} else if (choice == 8) {
			std::cout << std::endl << "=== C is: " << a.GetDistance() << " | Angle is (in rad): " << a.GetAngle() << " ===" << std::endl << std::endl;
		}
	}

}