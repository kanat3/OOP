#include <iostream>
#include <cstring>
#include "binary_signal.h"

int main () {
	/*Binary_Signal::Binary_Signal a(0, "10\n");
	a.Test_Class();
	a.ShowClass();
	puts("\nInversion\n");
	a.SignalInversion();
	a.ShowClass();
	Binary_Signal::Signal_Parameter b;
	a.GetSignal(b, 6);
	if (b.level == -1) {
		std::cout << "\nno\n";
	} else {
		std::cout << "\nSignal: " << b.level << " | " << b.duration << "\n";
	}
	a.GetSignal(b, 1, "20\n");
	if (b.level == -1) {
		std::cout << "\nno\n";
	} else {
		std::cout << "\nSignal: " << b.level << " | " << b.duration << "\n";
	}*/
	Binary_Signal::Binary_Signal b;
	puts("\nset b\n");
	b.SetSignal(1, "15\n");
	b.SetSignal(0, "5\n");
	b.SetSignal(1, "85\n");
	b.SetSignal(0, "2\n");
	b.ShowClass();
	Binary_Signal::Binary_Signal c;
	puts("\nset c\n");
	c.SetSignal(0, "45\n");
	c.SetSignal(0, "3\n");
	c.SetSignal(1, "86\n");
	c.SetSignal(1, "9\n");
	c.ShowClass();
	b.SetSignalInTime(110, c);
	puts("\nAdd new signal\n");
	b.ShowClass();
	b.DeleteSignal(249, "85\n");
	b.ShowClass();
	Binary_Signal::Binary_Signal t;
	puts("\nset t\n");
	t.SetSignal(1, "145\n");
	t.SetSignal(0, "15\n");
	t.SetSignal(1, "835\n");
	t.SetSignal(0, "24\n");
	t.ShowClass();
	puts("Add");
	c.SignalAddition(t);
	c.ShowClass();
	return 0;
}