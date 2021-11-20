#pragma once
#include "file_access.hpp"
#include "map.hpp"
#include "instructions.hpp"

class Assembler {

public:
	Assembler(int argc, char *argv[]);
	// establish the locations of the symbols
	void Step1();
	// generate a translation
	void Step2();
	// Display the symbols in the symbol table.
	void DisplaySymbolTable() const { m_symtab.DisplaySymbolTable(); }

private:
	FileAccess m_facc;	    // File Access object
	Table m_symtab;	// Symbol table object
	Instruction m_inst;	    // Instruction object
};