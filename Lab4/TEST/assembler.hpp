#pragma once
#include "file_access.hpp"
#include "map.hpp"
#include <iostream>
#include <array>
#include <sstream>
#include "operands.hpp"

class Assembler {
public:
	const static int MAX_MEMORY = 1000;
	const static int REGISTERS_COUNT = 16;
	Assembler (void) {};
	Assembler (int argc, char *argv[]) : m_facc(argc, argv) { 
		for (int i = 0; i < REGISTERS_COUNT; i++) { m_registers.at(i) = " "; }; 
	};
	void DisplayInfo (void) const { m_symtab.PrintTable(); };
	std::string ParseInstruction(std::string& my_str, const int numb_str);
	bool WriteInstruction (void);
	void CreateOperands (const std::string& info, const std::string& line, const std::string& label, int& adr);
	void RunAssembler (void);
	void SetRegistor (const std::string& info, const int position) { m_registers.at(position) = info; };
	std::string GetRegister (const int position) const { return m_registers.at(position); };
	void DisplayMemory (void) const {
		int count = -1;
		for (const auto& it : m_registers) {
			count++;
			if (it != " ") {
				std::cout << "0x" << count << "  - >    " << it << std::endl;
			}
		}
	};
	bool AssignMemory (const std::string& info);
private:
	std::array<std::string, REGISTERS_COUNT> m_registers;
	FileAccess m_facc;
	Table m_symtab;
};