#pragma once
#include "file_access.hpp"
#include "map.hpp"
#include <iostream>
#pragma once
#include <sstream>
#include "operands.hpp"

class Assembler {
public:
	const static int MAX_MEMORY = 1000;

	Assembler (int argc, char *argv[]) : m_facc(argc, argv) {} ;
	void DisplayInfo (void) const { m_symtab.PrintTable(); };
	std::string ParseInstruction(std::string& my_str);
	void WriteInstruction (void);
	void CreateOperands (const std::string info, const std::string line, const std::string label, int& adr);
private:
	FileAccess m_facc;
	Table m_symtab;
};