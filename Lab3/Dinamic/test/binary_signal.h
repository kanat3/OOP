#pragma once
#include <istream>

namespace Binary_Signal {
	static const int MAX_DURATION = 9; // can be 1 - 9
	static const int STANDART_SIZE = 10;
	static const char* STANDART_SIGNAL = "1203140615";

	typedef struct Signal_Parameter {
		int level; // 0 or 1
		char duration; // 49-57
		Signal_Parameter* next;
	} Signal_Parameter;

	class Binary_Signal {
	private:
		int REAL_SIZE = 0;
		Signal_Parameter* signals;
		int CheckAString (const char* signal) const noexcept;
	public:
		Binary_Signal (void) { REAL_SIZE = 0; };
		Binary_Signal (const int bin_level, const char duration = 49, const int size = STANDART_SIZE);
		explicit Binary_Signal (const char* signal); // string 180214 1 - lvl, 8 - duration
		Binary_Signal (const Binary_Signal& a); //копирование сигнала
		Binary_Signal (const Binary_Signal& a, const int N); //копирование сигнала n раз
		int GetSizeNow (void) const { return REAL_SIZE; };
		int GetFullSignalDuration (void) const noexcept;
		void SetSignal (const int bin_level = 0, const char signal_duration = 49);
		void SetSignal (const char* signal);
		void SetSignalInTime (const int time, const Binary_Signal& to_add);
		Binary_Signal& SignalInversion (void) noexcept;
		Binary_Signal SignalAddition (const Binary_Signal& to_add);
		void DeleteSignal (const int time, const char signal_duration);
		void ShowClassAsTable (void) const noexcept;
		void ShowClassAsString (void) const noexcept;
		std::ostream& print(std::ostream&) const noexcept; //2 вывода
		void FreeClass (void) noexcept;
		~Binary_Signal (void) noexcept;

		friend std::istream& operator >> (std::istream& in, Binary_Signal& a);
		friend std::ostream& operator << (std::ostream& out, const Binary_Signal& a) noexcept;
		friend Binary_Signal operator + (const Binary_Signal& signal1, const Binary_Signal& signal2);
		friend Binary_Signal operator * (int N, const Binary_Signal& signal1);
		Binary_Signal& operator ~ (void) noexcept;
		friend bool operator == (const Binary_Signal& signal1, const Binary_Signal& signal2) noexcept;
		Binary_Signal& operator = (const Binary_Signal& a);
	};
}