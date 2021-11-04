#pragma once

namespace Binary_Signal {
	const int MAX_DURATION = 9; // can be 1 to 9
	const int SIZE = 15;

	typedef struct Signal_Parameter {
		int level; // 0 or 1
		char duration; // 49-57
	} Signal_Parameter;

	class Binary_Signal {
	private:
		int size_now; // размер сигнала по факту
		Signal_Parameter signals[SIZE];
		int CheckAString (const char* signal) const;
	public:
		explicit Binary_Signal (void) { size_now = 0; };
		explicit Binary_Signal (const int bin_level, const char duration = 49);
		explicit Binary_Signal (const char* signal); // string 180214
		explicit Binary_Signal (const Binary_Signal& a); //копирование сигнала
		explicit Binary_Signal (const Binary_Signal& a, const int N); //копирование сигнала n раз

		void GetSignal (Signal_Parameter& a, int index) const; //получить сигнал по индексу
		void GetSignal (Signal_Parameter& a, int bin_level, const char str) const; //получить определенный сигнал
		void SetSignal (const int bin_level = 0, const char signal_duration = 49); //добавление сигнала в конец
		void SetSignal (const char* signal);
		//вставка сигнала в момент времени time
		void SetSignalInTime (const int time, const Binary_Signal& to_add);
		void SignalInversion (void); //инверсия сигнала
		void SignalAddition (const Binary_Signal to_add);
		// удаление фрагмента сигнала в определенное время time определённой длительности
		void DeleteSignal (const int time, const char signal_duration);
		void ShowClassAsTable (void) const; // level/duration as table
		void ShowClassAsString (void) const;
		std::ostream & print(std::ostream&) const; //2 вывода
		void Test_Class (void); //тестовый экземпяр
		void FreeClass (void) { size_now = 0; };
	};
}