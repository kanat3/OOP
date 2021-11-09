#include <iostream>
#include "binary_signal.h"
#include "menu.h"
#include <cstring>
#include <exception>

namespace Binary_Signal {

	void Binary_Signal::ShowClassAsTable (void) const { //*
		Signal_Parameter* head = signals;
		while (head != nullptr) {
			std::cout << "level: " << head->level << " duration: " << head->duration << std::endl;
			head = head->next;
		}
		std::cout << " {size: " << REAL_SIZE << "}" << std::endl << std::endl;
		std::cout << std::endl;
	}

	void Binary_Signal::ShowClassAsString (void) const { //*
		Signal_Parameter* head = signals;
		std::cout << std::endl;
		while (head != nullptr) {
			for (int i = 0; i < head->duration - '0'; i++) {
				std::cout << head->level;
			}
			head = head->next;
		}
		std::cout << " {size: " << REAL_SIZE << "}" << std::endl << std::endl;
		std::cout << std::endl;
	}

	int Binary_Signal::CheckAString (const char* string) const { //*
		int len = strlen(string);
		int error = 0;
		int i = 0;
		if (len%2 != 0) {
			return 0;
		}
		while (error == 0 && i < len) {
			if (i%2 == 0 && (string[i] - '0' != 1 && string[i] - '0' != 0)) {
				std::cout << "str: " << string[i] - '0' << " ";
				error = -1;
				puts("err1");
				break;
			}
			if (error == 0 && i%2 != 0 && string[i] - '0' < 1 && string[i] - '0' > MAX_DURATION) {
				error = -1;
				puts("err2");
				break;
			}
			i++;
		}
		if (error == 0) {
			return 1;
		} else {
			return 0;
		}
	}

	Binary_Signal::Binary_Signal (const char* signal) { //* enter only in this format: 18020515 1/0 -level, 1-9 - duration
		REAL_SIZE = 0;
		int BAD_ALLOC = 0;
		int j = 2;
		int i = 1;
		if (!CheckAString(signal)) {
			throw std::invalid_argument("Bad string");
		} else {
			int len = strlen(signal);
			REAL_SIZE = len/2;
			Signal_Parameter* head;
			try {
				signals = new Signal_Parameter;
			} catch (const std::bad_alloc& str) {
				std::cout << "Allocation failed: " << str.what() << std::endl;
				BAD_ALLOC = 1;
			}
			if (BAD_ALLOC == 0) {
				head = signals;
				signals->level = signal[0] - '0';
				signals->duration = signal[1];
				while (i < len/2) {
					try {
						signals->next = new Signal_Parameter;
					} catch (const std::bad_alloc& str) {
						std::cout << "Allocation failed: " << str.what() << std::endl;
						BAD_ALLOC = 1;
					}
					if (BAD_ALLOC == 1) {
						Signal_Parameter* to_delete;
						while (head) {
							puts("DELETE");
							to_delete = head;
							head = head->next;
							delete to_delete;
						}
						break;
					}
					signals = signals->next;
					signals->level = signal[j] - '0';
					signals->duration = signal[j + 1];
					j += 2;
					i++;	
				}
				signals->next = nullptr;
				signals = head;
			}
		}
	}

	Binary_Signal::Binary_Signal (const int bin_level, const char duration, const int size) { //*
		REAL_SIZE = 1;
		int BAD_ALLOC = 0;
		Signal_Parameter* head;
		try {
			signals = new Signal_Parameter;
		} catch (const std::bad_alloc& str) {
			std::cout << "Allocation failed: " << str.what() << std::endl;
			BAD_ALLOC = 1;
		}
		if (BAD_ALLOC == 0) {
			head = signals;
			signals[0].level = bin_level;
			signals[0].duration = duration;
			for (int i = 1; i < size; i++) {
				try {
					signals->next = new Signal_Parameter;
				} catch (const std::bad_alloc& str) {
					std::cout << "Allocation failed: " << str.what() << std::endl;
					BAD_ALLOC = 1;
				}
				if (BAD_ALLOC == 1) {
					Signal_Parameter* to_delete;
					while (head) {
						to_delete = head;
						head = head->next;
						delete to_delete;
					}
					break;
				} else {
					signals = signals->next;
					signals->level = bin_level;
					signals->duration = duration;
				}
			}
			if (BAD_ALLOC == 0) {
				signals->next = nullptr;
				signals = head;
			}
		}
	}

	void Binary_Signal::SignalInversion (void) {
		if (REAL_SIZE == 0) {
			return;
		}
		Signal_Parameter* head = signals;
		while (signals) {
			if (signals->level == 1) {
				signals->level = 0;
			} else {
				signals->level = 1;
			}
			signals = signals->next;
		}
		signals = head;
	}

	Binary_Signal::~Binary_Signal (void) {
		Signal_Parameter* to_delete;
		while (signals) {
			to_delete = signals;
			signals = signals->next;
			delete to_delete;
		}
		signals = nullptr;
		REAL_SIZE = 0;
	}

/*
	Signal_Parameter Binary_Signal::GetSignal (int index) const {
		Signal_Parameter a;
		if ((index < 0 && index > SIZE) || index >= size_now) {
			throw std::invalid_argument("Bad index");
		}
		a.level = signals[index].level;
		a.duration = signals[index].duration;
		return a;
	}

	Signal_Parameter Binary_Signal::GetSignal (int bin_level, const char str) const {
		Signal_Parameter a;
		for (int i = 0; i < SIZE; i++) {
			if (signals[i].level == bin_level && signals[i].duration == str) {
				a.level = signals[i].level;
				a.duration = signals[i].duration;
			}
		}
		return a;
	}

	void Binary_Signal::SetSignal (const int bin_level, const char signal_duration) {
		if (size_now - 1 == SIZE) {
			return;
		}
		if (bin_level != 1 && bin_level != 0) {
			return;
		}
		signals[size_now].level = bin_level;
		signals[size_now].duration = signal_duration;
		size_now++;
	}

	void Binary_Signal::SetSignal (const char* signal) {
		size_now = 0;
		int j = 0;
		if (!CheckAString(signal)) {
			throw std::invalid_argument("Bad string");
		} else {
			int len = strlen(signal);
			for (int i = 0; i < len; i++) {
				if (i%2 == 0) {
					signals[j].level = signal[i] - '0';
					size_now++;
				} else {
					signals[j].duration = signal[i];
					j++;
				}
			}
		}
	}

	Binary_Signal::Binary_Signal (const Binary_Signal& a) {
		size_now = a.size_now;
		if (size_now == 0) {
			return;
		}
		for (int i = 0; i < size_now; i++) {
			signals[i].level = a.signals[i].level;
			signals[i].duration = a.signals[i].duration;
		}
	}

	Binary_Signal::Binary_Signal (const Binary_Signal& a, const int N) { //хз
		if (N * a.size_now > SIZE) {
			throw std::invalid_argument("Can't copy");
			return;
		}
		size_now = N * a.size_now;
		int j = 0;
		for (int i = 0; i < size_now; i++, j++) {
			if (i%a.size_now == 0) {
				j = 0;
			}
			signals[i].level = a.signals[j].level;
			signals[i].duration = a.signals[j].duration;
		}
	}


	void Binary_Signal::SetSignalInTime (const int time, const Binary_Signal& to_add) {
		if (size_now + to_add.size_now >= SIZE) {
			throw std::invalid_argument("Can't add");
			return;
		}
		int sum = 0;
		int index = -1;
		int index_add = 0;
		while (sum < time && index < size_now - 1) {
			index++;
			sum += signals[index].duration - '0';
		}
		if (sum < time) {
			index++;
		}
		size_now = index + to_add.size_now;
		for (int i = index; i < index + to_add.size_now; i++) {
			signals[i].level = to_add.signals[index_add].level;
			signals[i].duration = to_add.signals[index_add].duration;
			index_add++;
		}
	}


	void Binary_Signal::DeleteSignal (const int time, const char signal_duration) {
		int sum = 0;
		int index = -1;
		while (sum < time && index < size_now - 1) {
			index++;
			sum += signals[index].duration - '0';
		}
		if (sum < time) {
			std::cout << "No such signal" << std::endl;
			return;
		}
		if (signals[index].duration == signal_duration) {
			for (int i = index++; i < size_now - 1; i++) {
				signals[i].level = signals[i + 1].level;
				signals[i].duration = signals[i + 1].duration;
			}
			size_now--;
		} else {
			std::cout << "No such signal" << std::endl;
			return;
		}
	}

	Binary_Signal Binary_Signal::SignalAddition (const Binary_Signal& to_add) {
		Binary_Signal a;
		if (size_now + to_add.size_now >= SIZE) {
			std::cout << "Can't add" << std::endl;
			a = GetBinarySignal();
			return a;
		}
		int index_add = 0;
		for (int i = size_now; i < size_now + to_add.size_now; i++) {
			signals[i].level = to_add.signals[index_add].level;
			signals[i].duration = to_add.signals[index_add].duration;
			index_add++;
		}
		size_now += to_add.size_now;
		a = GetBinarySignal();
		return a;
	}

	int Binary_Signal::GetFullSignalDuration (void) const {
		int sum = 0;
		for (int i = 0; i < size_now; i++) {
			sum += signals[i].duration - '0';
		}
		return sum;
	}

	std::ostream& Binary_Signal::print (std::ostream &s) const {
		puts("\nFirst print\n");
		for (int i = 0; i < size_now; i++) {
			std::cout << "level: " << signals[i].level << " duration: " << signals[i].duration << std::endl;
		}
		std::cout << " {size: " << size_now << "}" << std::endl << std::endl;
		puts("\nSecond print\n");
		for (int i = 0; i < size_now; i++) {
			for (int j = 0; j < signals[i].duration - '0'; j++) {
				std::cout << signals[i].level;
			}
		}
		std::cout << " {size: " << size_now << "}" << std::endl << std::endl;
		std::cout << std::endl;
		return s;
	}

	Binary_Signal Binary_Signal::GetBinarySignal (void) {
		Binary_Signal a;
		a.SetSizeNow(size_now);
		for (int i = 0; i < size_now; i++) {
			a.signals[i].level = signals[i].level;
			a.signals[i].duration = signals[i].duration;
		}
		return a;
	}

	std::istream& operator >> (std::istream& in, Binary_Signal& a) {
			int ERROR;
			a.FreeClass();
			std::cout << "\nEnter signal like that -> Example: 15021104, 1 - level, 5 - duration, 0 - level etc." << std::endl;
			std::string str;
			if (!Menu::GetInput(str, ERROR)) {
				return in;
			}
			try {
				a.SetSignal(str.c_str());
			} catch (std::invalid_argument) {
				std::cout << "Exception: Invalid value" << std::endl;
				return in;
			}
			return in;
	}

	std::ostream& operator << (std::ostream& out, const Binary_Signal& a) {
		a.print(out);
		return out;
	}

	Binary_Signal operator + (const Binary_Signal& signal1, const Binary_Signal& signal2) {
		Binary_Signal a;
		Binary_Signal b(signal1);
		a = b.SignalAddition(signal2);
		return a;
	}

	Binary_Signal& Binary_Signal::operator ~ (void) {
		SignalInversion();
		return *this;
	}

	bool operator == (const Binary_Signal& signal1, const Binary_Signal& signal2) {
		if (signal1.GetSizeNow() != signal2.GetSizeNow()) {
			return false;
		}
		bool result;
		for (int i = 0; i < signal1.GetSizeNow(); i++) {
			if ((signal1.signals[i].level == signal2.signals[i].level) && (signal1.signals[i].duration == signal2.signals[i].duration)) {
				result = true;
			} else {
				result = false;
			}
		}
		return result;
	}

	Binary_Signal& Binary_Signal::operator = (const Binary_Signal& a) {
		size_now = a.GetSizeNow();
		for (int i = 0; i < a.GetSizeNow(); i++) {
			signals[i].level = a.signals[i].level;
			signals[i].duration = a.signals[i].duration;
		}
		return *this;
	}*/
}