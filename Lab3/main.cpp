#include <iostream>
#include <cstring>
#include "binary_signal.h"
#include "menu.h"

int main () {
	int error;
	Binary_Signal::Binary_Signal a;
	error = Menu::T_DoChoise(a);
	if (error == INPUT_ERROR) {
		return INPUT_ERROR;
	}
	return GOOD;
	return 0;
}