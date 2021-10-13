#include <iostream>
#include "binary_signal.h"
#include <cstring>
#include <exception>

void Binary_Signal::Binary_Signal::Test_Class (void) {
	size_now = 0;
	const char* str[4] = {"10", "20", "30", "40"};
	for (int i = 0; i < 4; i++) {
		signals[i].level = rand()%2;
		strcpy(signals[i].duration, str[i]);
		size_now++;
	}
}

Binary_Signal::Binary_Signal::Binary_Signal (int bin_level, const char signal_duration[5]) {
	size_now = 0;
	for (int i = 0; i < SIZE; i++) {
		signals[i].level = bin_level;
		strcpy(signals[i].duration, signal_duration);
		size_now++;
	}
}

Binary_Signal::Binary_Signal::Binary_Signal (int bin_level) {
	size_now = 0;
	for (int i = 0; i < SIZE; i++) {
		signals[i].level = bin_level;
		size_now++;
	}
}

void Binary_Signal::Binary_Signal::ShowClass (void) const {
	std::cout << "{ size: " << size_now << " }" << std::endl << std::endl;
	for (int i = 0; i < size_now; i++) {
		std::cout << "level: " << signals[i].level << " duration: " << signals[i].duration << std::endl;
	}
}

void Binary_Signal::Binary_Signal::SignalInversion (void) {
	for (int i = 0; i < size_now; i++) {
		if (signals[i].level == 1) {
			signals[i].level = 0;
		} else {
			signals[i].level = 1;
		}
	}
}

void Binary_Signal::Binary_Signal::GetSignal (Signal_Parameter& a, int index) const {
	a.level = -1;
	if ((index < 0 && index > 10) || index >= size_now) {
		return;
	}
	a.level = signals[index].level;
	strcpy(a.duration, signals[index].duration);
}

void Binary_Signal::Binary_Signal::GetSignal (Signal_Parameter& a, int bin_level, const char str[5]) const {
	a.level = -1;
	for (int i = 0; i < SIZE; i++) {
		if (signals[i].level == bin_level && strcmp(signals[i].duration, str) == 0) {
			a.level = signals[i].level;
			strcpy(a.duration, signals[i].duration);
		}
	}
}

void Binary_Signal::Binary_Signal::SetSignal (int bin_level, const char* signal_duration) {
	if (size_now - 1 == SIZE) {
		return;
	}
	if (bin_level != 1 && bin_level != 0) {
		return;
	}
	signals[size_now].level = bin_level;
	strcpy(signals[size_now].duration, signal_duration);
	size_now++;
}

Binary_Signal::Binary_Signal::Binary_Signal (const Binary_Signal& a) {
	size_now = a.size_now;
	if (size_now == 0) {
		return;
	}
	for (int i = 0; i < size_now; i++) {
		signals[i].level = a.signals[i].level;
		strcpy(signals[i].duration, a.signals[i].duration);
	}
}

void Binary_Signal::Binary_Signal::SetSignalInTime (int time, Binary_Signal to_add) {
	if (size_now + to_add.size_now >= SIZE) {
		std::cout << "Can't add" << std::endl;
		return;
	}
	int sum = 0;
	int index = -1;
	int index_add = 0;
	while (sum < time && index < size_now - 1) {
		index++;
		sum += atoi(signals[index].duration);
	}
	if (sum < time) {
		index++;
	}
	size_now = index + to_add.size_now;
	for (int i = index; i < index + to_add.size_now; i++) {
		signals[i].level = to_add.signals[index_add].level;
		strcpy(signals[i].duration, to_add.signals[index_add].duration);
		index_add++;
	}
}

void Binary_Signal::Binary_Signal::DeleteSignal (int time, const char* signal_duration) {
	int sum = 0;
	int index = -1;
	while (sum < time && index < size_now - 1) {
		index++;
		sum += atoi(signals[index].duration);
	}
	if (sum < time) {
		std::cout << "No such signal" << std::endl;
		return;
	}
	if (strcmp(signals[index].duration, signal_duration) == 0) {
		for (int i = index++; i < size_now - 1; i++) {
			signals[i].level = signals[i + 1].level;
			strcpy(signals[i].duration, signals[i + 1].duration);
		}
		size_now--;
	} else {
		std::cout << "No such signal" << std::endl;
		return;
	}
}

void Binary_Signal::Binary_Signal::SignalAddition (Binary_Signal to_add) {
	if (size_now + to_add.size_now >= SIZE) {
		std::cout << "Can't add" << std::endl;
		return;
	}
	int index_add = 0;
	for (int i = size_now; i < size_now + to_add.size_now; i++) {
		signals[i].level = to_add.signals[index_add].level;
		strcpy(signals[i].duration, to_add.signals[index_add].duration);
		index_add++;
	}
	size_now += to_add.size_now;
}