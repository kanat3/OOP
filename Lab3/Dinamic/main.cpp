#include <iostream>
#include <cstring>
#include "binary_signal.h"
#include "menu.h"

int main () {
	int error;
	Binary_Signal::Binary_Signal a("120314");
	a.ShowClassAsString();
	Binary_Signal::Binary_Signal b(1, 51, 6);
	a.SignalInversion();
	a.ShowClassAsString();
	
	/*error = Menu::T_DoChoise(a);
	if (error == INPUT_ERROR) {
		return INPUT_ERROR;
	}*/
	return GOOD;
}