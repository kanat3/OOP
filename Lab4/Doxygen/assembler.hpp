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
	 * @param MAX_MEMORY Maximum memory of the processor emulator
	 * 
	 */
	const static int MAX_MEMORY = 1000;
	/**
	 * @param REGISTERS_COUNT Number of registers in the processor
	 * 
	 */
	const static int REGISTERS_COUNT = 16;
	/**
	 * @brief Construct a new Assembler object
	 * 
	 */

	Assembler (void) {};
	/**
	 * @brief Construct a new Assembler object
	 * 
	 * @param argc The number of arguments at the input
	 * @param argv The array of arguments must contain two values:
	 * the command to run the executable file and the full name of the file in which the text/code is analyzed
	 */
	Assembler (int argc, char *argv[]) : m_facc(argc, argv) { 
		for (int i = 0; i < REGISTERS_COUNT; i++) { m_registers.at(i) = " "; }; 
	};
	/**
	 * @brief Output of the entire contents of the operand table
	 * 
	 */
	void DisplayInfo (void) const { m_symtab.PrintTable(); };
	/**
	 * @brief Parsing the line from file. In case of an error during parsing, returns the value ERROR
	 * 
	 * @param my_str Retrieves a string from a file for parsing
	 * @param numb_str We get the line number in the file, in case of an error, we output the line number and the line itself
	 * @return std::string returns the received instruction
	 */
	std::string ParseInstruction(std::string& my_str, const int numb_str);
	/**
	 * @brief Parsing the entire file
	 * 
	 * @return true Success parsing
	 * @return false Parsing error, output
	 */
	bool WriteInstruction (void);
	/**
	 * @brief Create a Operands object. Adding to the table.
	 * 
	 * @param info Name of the instruction
	 * @param line A string for entering data into the class
	 * @param label Code label, if available
	 * @param adr Address of the memory location to write to
	 */
	void CreateOperands (const std::string& info, const std::string& line, const std::string& label, int& adr);
	/**
	 * @brief Launching the Emulator
	 * 
	 */
	void RunAssembler (void);
	/**
	 * @brief Set the Registor object. In case of errors when parsing the file, exit the program with the corresponding message
	 * 
	 * @param info Information to be entered into the memory register
	 * @param position Register number
	 */
	void SetRegistor (const std::string& info, const int position) { m_registers.at(position) = info; };
	/**
	 * @brief Get the Register object. New information in memory array
	 * 
	 * @param position Register number
	 * @return std::string Information
	 */
	std::string GetRegister (const int position) const { return m_registers.at(position); };
	/**
	 * @brief Output of information in registers
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
	 * @brief Filling in registers
	 * 
	 * @param info 
	 * @return true Successful completion
	 * @return false Error while adding or memory overflow
	 */
	bool AssignMemory (const std::string& info);
private:
	/**
	 * @param m_registers Array of registers. Emulates memory cells
	 * 
	 */
	std::array<std::string, REGISTERS_COUNT> m_registers;
	/**
	 * @param m_facc File to read. This file contains the code for analysis
	 * 
	 */
	FileAccess m_facc;
	/**
	 * @param m_symtab Operand table, two implementations: via STL and via a custom template. All registers loaded from the file are stored
	 * 
	 */
	Table m_symtab;
};