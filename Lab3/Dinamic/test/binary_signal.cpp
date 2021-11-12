#include <iostream>
#include "binary_signal.h"
#include "menu.h"
#include <cstring>
#include <exception>

namespace Binary_Signal {

	void Binary_Signal::ShowClassAsTable (void) const noexcept {
		if (REAL_SIZE == 0) {
			std::cout << "Your class is empty" << std::endl;
			return;
		}
		Signal_Parameter* head = signals;
		while (head != nullptr) {
			std::cout << "level: " << head->level << " duration: " << head->duration << std::endl;
			head = head->next;
		}
		std::cout << " {size: " << REAL_SIZE << "}" << std::endl << std::endl;
		std::cout << std::endl;
	}

	void Binary_Signal::ShowClassAsString (void) const noexcept { 
		if (REAL_SIZE == 0) {
			std::cout << "Your class is empty" << std::endl;
			return;
		}
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

	int Binary_Signal::CheckAString (const char* string) const noexcept { 
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

	Binary_Signal::Binary_Signal (const char* signal) { // enter only in this format: 18020515 1/0 -level, 1-9 - duration
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
		if (bin_level != 0 && bin_level != 1) {
			return;
		}
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
			signals->level = bin_level;
			signals->duration = duration;
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
				REAL_SIZE = size;
			}
		}
	}

	Binary_Signal& Binary_Signal::SignalInversion (void) noexcept {
		if (REAL_SIZE == 0) {
			return *this;
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
		return *this;
	}

	Binary_Signal::~Binary_Signal (void) noexcept {
		FreeClass();
	}

	void Binary_Signal::SetSignal (const int bin_level, const char signal_duration) {
		int BAD_ALLOC = 0;
		if (bin_level != 1 && bin_level != 0) {
			return;
		}
		if (REAL_SIZE == 0) {
			try {
				signals = new Signal_Parameter;
			} catch (const std::bad_alloc& str) {
				std::cout << "Allocation failed: " << str.what() << std::endl;
				BAD_ALLOC = 1;
			}
			if (BAD_ALLOC == 1) {
				return;
			}
			signals->level = bin_level;
			signals->duration = signal_duration;
			signals->next = nullptr;
			REAL_SIZE++;
			return;	
		}
		Signal_Parameter* head = signals;
		while (signals->next) {
			signals = signals->next;
		}
		try {
			signals->next = new Signal_Parameter;
		} catch (const std::bad_alloc& str) {
			std::cout << "Allocation failed: " << str.what() << std::endl;
			BAD_ALLOC = 1;
		}
		if (BAD_ALLOC == 1) {
			return;
		}
		signals = signals->next;
		signals->level = bin_level;
		signals->duration = signal_duration;
		signals->next = nullptr;
		REAL_SIZE++;
		signals = head;
	}

	void Binary_Signal::SetSignal (const char* signal) {
		if (REAL_SIZE != 0) {
			FreeClass();
		}
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

	void Binary_Signal::FreeClass (void) noexcept {
		if (REAL_SIZE == 0) {
			return;
		}
		Signal_Parameter* to_delete;
		while (signals) {
			to_delete = signals;
			signals = signals->next;
			delete to_delete;
		}
		signals = nullptr;
		REAL_SIZE = 0;
	}

	Binary_Signal::Binary_Signal (const Binary_Signal& a) {
		REAL_SIZE = a.REAL_SIZE;
		if (REAL_SIZE == 0) {
			return;
		}
		int BAD_ALLOC = 0;
		Signal_Parameter* head;
		Signal_Parameter* a_head = a.signals;
		try {
			signals = new Signal_Parameter;
		} catch (const std::bad_alloc& str) {
			std::cout << "Allocation failed: " << str.what() << std::endl;
			BAD_ALLOC = 1;
		}
		if (BAD_ALLOC == 0) {
			head = signals;
			signals->level = a_head->level;
			signals->duration = a_head->duration;
			for (int i = 1; i < REAL_SIZE; i++) {
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
					a_head = a_head->next;
					signals = signals->next;
					signals->level = a_head->level;
					signals->duration = a_head->duration;
				}
			}
			if (BAD_ALLOC == 0) {
				signals->next = nullptr;
				signals = head;
			}
		}
	}

	Binary_Signal::Binary_Signal (const Binary_Signal& a, const int N) {
		if (a.GetSizeNow() == 0) {
			return;
		}
		REAL_SIZE = N * a.REAL_SIZE;
		int BAD_ALLOC = 0;
		Signal_Parameter* head;
		Signal_Parameter* a_head = a.signals;
		try {
			signals = new Signal_Parameter;
		} catch (const std::bad_alloc& str) {
			std::cout << "Allocation failed: " << str.what() << std::endl;
			BAD_ALLOC = 1;
		}
		if (BAD_ALLOC == 0) {
			head = signals;
			signals->level = a_head->level;
			signals->duration = a_head->duration;
			a_head = a_head->next;
			for (int i = 1; i < REAL_SIZE; i++) {
				if (i%a.REAL_SIZE == 0) {
					a_head = a.signals;
				}
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
					signals->level = a_head->level;
					signals->duration = a_head->duration;
					a_head = a_head->next;
				}
			}
			if (BAD_ALLOC == 0) {
				signals->next = nullptr;
				signals = head;
			}
		}
	}

	void Binary_Signal::SetSignalInTime (const int time, const Binary_Signal& to_add) {
		if (to_add.REAL_SIZE == 0 || time < 0) {
			std::cout << "Invalid argument time or nothing to add" << std::endl;
			return;
		}
		if (REAL_SIZE == 0) {
			std::cout << "Your signal is empty" << std::endl;
			return;
		}
		int BAD_ALLOC = 0;
		int sum = 0;
		int sum_of_del = 0;
		Signal_Parameter* head = signals;
		Signal_Parameter* to_add_head = to_add.signals;
		while (sum < time && head->next != nullptr) {
			sum += head->duration - '0';
			head = head->next;
		}
		if (head != nullptr && head->next != nullptr) {
			Signal_Parameter* to_delete;
			while (head) {
				sum_of_del++;
				to_delete = head;
				head = head->next;
				delete to_delete;
			}
		}
		head = signals;
		for (int i = 0; i < REAL_SIZE - sum_of_del - 1; i++) {
			head = head->next;
		}
		for (int i = 0; i < to_add.REAL_SIZE; i++) {
			try {
				head->next = new Signal_Parameter;
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
				head = head->next;
				head->level = to_add_head->level;
				head->duration = to_add_head->duration;
				to_add_head = to_add_head->next;
			}
		}
		if (BAD_ALLOC == 0) {
			head->next = nullptr;
		}
		REAL_SIZE = REAL_SIZE - sum_of_del + to_add.REAL_SIZE;
	}

	int Binary_Signal::GetFullSignalDuration (void) const noexcept {
		if (REAL_SIZE == 0) {
			return 0;
		}
		int sum = 0;
		Signal_Parameter* head = signals;
		for (int i = 0; i < REAL_SIZE; i++) {
			sum += head->duration - '0';
			head = head->next;
		}
		return sum;
	}

	void Binary_Signal::DeleteSignal (const int time, const char signal_duration) {
		if (REAL_SIZE == 0) {
			return;
		}
		if (time <= 0) {
			std::cout << ("Invalid argument time") << std::endl;
			return;
		}
		int sum = 0;
		int steps = 0;
		Signal_Parameter* head = signals;
		Signal_Parameter* to_connection_1;
		Signal_Parameter* to_connection_2;
		while (sum < time && head->next != nullptr) {
			sum += head->duration - '0';
			head = head->next;
			steps++;
		}
		if (head->next == nullptr) {
			sum += head->duration -'0';
			steps++;
		}
		if (sum < time) {
			std::cout << "No such signal" << std::endl;
			return;
		}
		to_connection_1 = signals;
		for (int i = 0; i < steps - 2; i++) {
			to_connection_1 = to_connection_1->next;
		}
		if (steps == 1) {
			head = to_connection_1;
		} else {
			head = to_connection_1->next;
		}
		if (head->duration == signal_duration) {
			if (steps == 1) {
				signals = head->next;
				delete head;
				REAL_SIZE--;
			} else {
				to_connection_2 = head->next;
				to_connection_1->next = to_connection_2;
				delete head;
				REAL_SIZE--;
			}
		} else {
			std::cout << "No such signal" << std::endl;
			return;			
		}
	}

	Binary_Signal Binary_Signal::SignalAddition (const Binary_Signal& to_add) {
		int a = GetFullSignalDuration();
		SetSignalInTime(a, to_add);
		return *this;
	}

	std::ostream& Binary_Signal::print (std::ostream &s) const noexcept {
		puts("\n===========================First print===========================\n");
		ShowClassAsString();
		puts("\n===========================Second print===========================\n");
		ShowClassAsTable();
		return s;
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

	std::ostream& operator << (std::ostream& out, const Binary_Signal& a) noexcept {
		a.print(out);
		return out;
	}

	Binary_Signal operator + (const Binary_Signal& signal1, const Binary_Signal& signal2) {
		Binary_Signal b(signal1);
		b.SignalAddition(signal2);
		return b;
	}

	Binary_Signal& Binary_Signal::operator ~ (void) noexcept {
		SignalInversion();
		return *this;
	}

	bool operator == (const Binary_Signal& signal1, const Binary_Signal& signal2) noexcept {
		if (signal1.GetSizeNow() != signal2.GetSizeNow()) {
			return false;
		}
		bool result;
		Signal_Parameter* head1 = signal1.signals;
		Signal_Parameter* head2 = signal2.signals;
		for (int i = 0; i < signal1.GetSizeNow(); i++) {
			if ((head1->level == head2->level) && (head1->duration == head2->duration)) {
				result = true;
			} else {
				result = false;
			}
			head1 = head1->next;
			head2 = head2->next;
		}
		return result;
	}

	Binary_Signal& Binary_Signal::operator = (const Binary_Signal& a) {
		REAL_SIZE = a.GetSizeNow();
		if (a.GetSizeNow() == 0) {
			puts("here");
			return *this;
		}
		int BAD_ALLOC = 0;
		Signal_Parameter* head;
		Signal_Parameter* a_head = a.signals;
		try {
			signals = new Signal_Parameter;
		} catch (const std::bad_alloc& str) {
			std::cout << "Allocation failed: " << str.what() << std::endl;
			BAD_ALLOC = 1;
		}
		if (BAD_ALLOC == 0) {
			head = signals;
			signals->level = a_head->level;
			signals->duration = a_head->duration;
			for (int i = 1; i < REAL_SIZE; i++) {
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
					a_head = a_head->next;
					signals = signals->next;
					signals->level = a_head->level;
					signals->duration = a_head->duration;
				}
			}
			if (BAD_ALLOC == 0) {
				signals->next = nullptr;
				signals = head;
			}
		}
		return *this;
	}

	Binary_Signal operator * (int N, const Binary_Signal& signal1) {
		Binary_Signal a(signal1, N);
		return a;
	}
}