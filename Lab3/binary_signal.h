#pragma once

namespace Binary_Signal {
	const int MAX_DURATION = 10;
	const int SIZE = 10;

	typedef struct Signal_Parameter {
		int level; // 0 or 1
		char duration[MAX_DURATION];
	} Signal_Parameter;

	class Binary_Signal {
	private:
		int size_now; // размер сигнала по факту
		Signal_Parameter signals[SIZE];
	public:
		Binary_Signal (void) { size_now = 0; };
		Binary_Signal (int bin_level);
		Binary_Signal (int bin_level, const char signal_duration[5]);
		Binary_Signal (const Binary_Signal& a); //копирование сигнала

		void GetSignal (Signal_Parameter& a, int index) const; //получить сигнал по индексу
		void GetSignal (Signal_Parameter& a, int bin_level, const char str[5]) const; //получить определенный сигнал
		void SetSignal (int bin_level = 0, const char* signal_duration = "1\n"); //добавление сигнала в конец
		//вставка сигнала в момент времени time
		void SetSignalInTime (int time, Binary_Signal to_add);
		void SignalInversion (void); //инверсия сигнала
		void SignalAddition (const Binary_Signal to_add);
		// удаление фрагмента сигнала в определенное время time определённой длительности
		void DeleteSignal (int time, char* signal_duration);
		void ShowClass (void) const;
		void Test_Class (void); //заполение адекватными числами
		void FreeClass (void) { size_now = 0; };
	};
}