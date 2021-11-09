#pragma once
#include <istream>

namespace Binary_Signal {
	static const int MAX_DURATION = 9; // can be 1 - 9
	static const int STANDART_SIZE = 10;

	typedef struct Signal_Parameter {
		int level; // 0 or 1
		char duration; // 49-57
		Signal_Parameter* next;
	} Signal_Parameter;

	class Binary_Signal {
	private:
		int REAL_SIZE = 0;
		Signal_Parameter* signals;
		int SetRealSize (const int size) const;
		int CheckAString (const char* signal) const;
	public:
		Binary_Signal (void);
		Binary_Signal (const int bin_level = 0, const char duration = 49, const int size = STANDART_SIZE);
		explicit Binary_Signal (const char* signal); // string 180214 1 - lvl, 8 - duration
		Binary_Signal (const Binary_Signal& a); //копирование сигнала
		Binary_Signal (const Binary_Signal& a, const int N); //копирование сигнала n раз
		int GetSizeNow (void) const { return REAL_SIZE; };
		int GetFullSignalDuration (void) const;
		Binary_Signal GetBinarySignal (void);
		Signal_Parameter GetSignal (int index) const;
		Signal_Parameter GetSignal (int bin_level, const char str) const;
		void SetSignal (const int bin_level = 0, const char signal_duration = 49);
		void SetSignal (const char* signal);
		void SetSignalInTime (const int time, const Binary_Signal& to_add);
		void SignalInversion (void);
		Binary_Signal SignalAddition (const Binary_Signal& to_add);
		void DeleteSignal (const int time, const char signal_duration);
		void ShowClassAsTable (void) const;
		void ShowClassAsString (void) const;
		std::ostream& print(std::ostream&) const; //2 вывода
		void FreeClass (void);
		~Binary_Signal (void);
	};
}