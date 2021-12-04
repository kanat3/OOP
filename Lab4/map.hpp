#pragma once
#include <map>
#include "operands.hpp"
#include <string>

class Table {

public:
	Table() {};
	~Table() {};

	void AddSymbol(const int a_loc, Operator_Container* a_operator);
	void PrintTable(void) const;
    Operator_Container& FindSymbol (const int address) const;
    void DeleteSymbol (const int address);
	
private:
	std::map<int, Operator_Container*> m_Table;
};