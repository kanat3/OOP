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
		int CheckAString (const char* signal) const noexcept;
	public:
		explicit Binary_Signal (void) { size_now = 0; };
		explicit Binary_Signal (const int bin_level, const char duration = 49);
		explicit Binary_Signal (const char* signal); // string 180214
		Binary_Signal (const Binary_Signal& a); //копирование сигнала
		Binary_Signal (const Binary_Signal& a, const int N); //копирование сигнала n раз

		int GetSizeNow (void) const noexcept { return size_now; };
		void SetSizeNow (const int s) noexcept { size_now = s; };
		int GetFullSignalDuration (void) const noexcept;

		Binary_Signal GetBinarySignal (void);
		void GetSignal (Signal_Parameter& a, int index) const noexcept; //получить сигнал по индексу
		void GetSignal (Signal_Parameter& a, int bin_level, const char str) const noexcept; //получить определенный сигнал
		void SetSignal (const int bin_level = 0, const char signal_duration = 49) noexcept; //добавление сигнала в конец
		void SetSignal (const char* signal);
		//вставка сигнала в момент времени time
		void SetSignalInTime (const int time, const Binary_Signal& to_add);
		void SignalInversion (void) noexcept; //инверсия сигнала
		Binary_Signal SignalAddition (const Binary_Signal& to_add) noexcept;
		// удаление фрагмента сигнала в определенное время time определённой длительности
		void DeleteSignal (const int time, const char signal_duration) noexcept;
		void ShowClassAsTable (void) const noexcept; // level/duration as table
		void ShowClassAsString (void) const noexcept;
		std::ostream& print(std::ostream&) const; //2 вывода
		void Test_Class (void) noexcept; //тестовый экземпяр
		void FreeClass (void) noexcept { size_now = 0; };

		friend Binary_Signal operator + (const Binary_Signal& signal1, const Binary_Signal& signal2) noexcept;
		friend std::istream& operator >> (std::istream& in, Binary_Signal& a);
		friend std::ostream& operator << (std::ostream& out, const Binary_Signal& a) noexcept;
		Binary_Signal& operator ~ (void) noexcept;
	};
}