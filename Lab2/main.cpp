#include <iostream>
#include "Lemniscata.h"
#include "menu.h"

int main (void) {
	int error;
	Lemniscata_Bernoulli::Lemniscata a;
	error = Menu::DoChoise(a);
	if (error == INPUT_ERROR) {
		return INPUT_ERROR;
	}
	return GOOD;
}