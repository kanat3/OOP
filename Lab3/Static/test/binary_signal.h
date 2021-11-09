#pragma once
#include <istream>

namespace Binary_Signal {
	static const int MAX_DURATION = 9; // can be 1 to 9
	static const int SIZE = 15;

	typedef struct Signal_Parameter {
		int level; // 0 or 1
		char duration; // 49-57
	} Signal_Parameter;

	class Binary_Signal {
	private:
		int size_now; // размер сигнала по факту
		Signal_Parameter signals[SIZE];
		int CheckAString (const char* signal) const;
		void SetSizeNow (const int s) { size_now = s; };
	public:
		Binary_Signal (void) { size_now = 0; };
		Binary_Signal (const int bin_level, const char duration = 49);
		explicit Binary_Signal (const char* signal); // string 180214
		Binary_Signal (const Binary_Signal& a); //копирование сигнала
		Binary_Signal (const Binary_Signal& a, const int N); //копирование сигнала n раз

		int GetSizeNow (void) const { return size_now; };
		int GetFullSignalDuration (void) const;

		Binary_Signal GetBinarySignal (void);
		void GetSignal (Signal_Parameter& a, int index) const; //получить сигнал по индексу
		void GetSignal (Signal_Parameter& a, int bin_level, const char str) const; //получить определенный сигнал
		void SetSignal (const int bin_level = 0, const char signal_duration = 49); //добавление сигнала в конец
		void SetSignal (const char* signal);
		//вставка сигнала в момент времени time
		void SetSignalInTime (const int time, const Binary_Signal& to_add);
		void SignalInversion (void); //инверсия сигнала
		Binary_Signal SignalAddition (const Binary_Signal& to_add);
		// удаление фрагмента сигнала в определенное время time определённой длительности
		void DeleteSignal (const int time, const char signal_duration);
		void ShowClassAsTable (void) const; // level/duration as table
		void ShowClassAsString (void) const;
		std::ostream& print(std::ostream&) const; //2 вывода
		void FreeClass (void) { size_now = 0; };
		void Test_Class (void); //тестовый экземпяр

		friend Binary_Signal operator + (const Binary_Signal& signal1, const Binary_Signal& signal2);
		friend bool operator == (const Binary_Signal& signal1, const Binary_Signal& signal2);
		friend std::istream& operator >> (std::istream& in, Binary_Signal& a);
		friend std::ostream& operator << (std::ostream& out, const Binary_Signal& a);
		Binary_Signal& operator ~ (void);
		Binary_Signal& operator = (const Binary_Signal& a);
	};
}