#pragma once
#include <map>
#include "operands.hpp"
#include <string>

class Table {

public:
	Table() {};
	~Table();

	void AddSymbol(const int a_loc, Operator_Container* a_operator);
	void PrintTable(void) const;
    void DeleteSymbol (const int address) { m_Table.erase(address); };
	/*Operator_Container* FindSymbol (const int address) {
		Operator_Container* a;
		a = m_Table.find(address);
		return a;
	};*/ 
private:
	std::map<int, Operator_Container*> m_Table;
};