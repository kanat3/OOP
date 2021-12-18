#pragma once
#include "file_access.hpp"
#include "map.hpp"
#include <iostream>
#include <array>
#include <sstream>
#include "operands.hpp"


class Assembler {
public:
	/**
	 * @param MAX_MEMORY Максимальная память у эмулятора процессора
	 * @param REGISTERS_COUNT Количество регистров в процессоре 
	 * 
	 */
	const static int MAX_MEMORY = 1000;
	const static int REGISTERS_COUNT = 16;
	/**
	 * @brief Construct a new Assembler object
	 * 
	 */

	Assembler (void) {};
	/**
	 * @brief Construct a new Assembler object
	 * 
	 * @param argc Количество аргументов на входе
	 * @param argv Массив аргументов, должен содержать два значения:
	 * команда запуска исполняемого файла и полное имя файла в котором анализируется текст/код
	 */
	Assembler (int argc, char *argv[]) : m_facc(argc, argv) { 
		for (int i = 0; i < REGISTERS_COUNT; i++) { m_registers.at(i) = " "; }; 
	};
	/**
	 * @brief Вывод всего содержимого таблицы операндов 
	 * 
	 */
	void DisplayInfo (void) const { m_symtab.PrintTable(); };
	/**
	 * @brief 
	 * 
	 * @param my_str Получает строку из файла для парсинга 
	 * @param numb_str Получаем номер строки в файле, в случае ошибки выводим номер строки и ее саму
	 * @return std::string возвращает полученную инструкцию
	 */
	std::string ParseInstruction(std::string& my_str, const int numb_str);
	/**
	 * @brief Парсинг всего файла
	 * 
	 * @return true 
	 * @return false Ошибка парсинга, выход
	 */
	bool WriteInstruction (void);
	/**
	 * @brief Create a Operands object
	 * 
	 * @param info Название инструкции
	 * @param line Строка для занесения в класс данных
	 * @param label Метка кода в случае ее наличия
	 * @param adr Адрес ячейки памяти для записи
	 */
	void CreateOperands (const std::string& info, const std::string& line, const std::string& label, int& adr);
	/**
	 * @brief Запуск эмулятора
	 * 
	 */
	void RunAssembler (void);
	/**
	 * @brief Set the Registor object
	 * 
	 * @param info Информация для занесения в регистр памяти
	 * @param position Номер регистра
	 */
	void SetRegistor (const std::string& info, const int position) { m_registers.at(position) = info; };
	/**
	 * @brief Get the Register object
	 * 
	 * @param position Номер регистра
	 * @return std::string Информация
	 */
	std::string GetRegister (const int position) const { return m_registers.at(position); };
	/**
	 * @brief Вывод информации в регистрах
	 * 
	 */
	void DisplayMemory (void) const {
		int count = -1;
		for (const auto& it : m_registers) {
			count++;
			if (it != " ") {
				std::cout << "0x" << count << "  - >    " << it << std::endl;
			}
		}
	};
	/**
	 * @brief Заполнение регистров
	 * 
	 * @param info 
	 * @return true Успешное завершение
	 * @return false Ошибка, возможно "переполнение"
	 */
	bool AssignMemory (const std::string& info);
private:
	/**
	 * @param m_registers Массив регистров
	 * 
	 */
	std::array<std::string, REGISTERS_COUNT> m_registers;
	/**
	 * @param m_facc Файл для считывания
	 * 
	 */
	FileAccess m_facc;
	/**
	 * @param m_symtab Таблица операндов, две реализации: через STL и через собственный шаблон
	 * 
	 */
	Table m_symtab;
};