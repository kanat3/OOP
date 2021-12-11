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
    void DeleteSymbol (const int address) {
		Operator_Container* op = FindSymbolByAddress(address);
		if (op != nullptr) {
			delete m_Table.find(address)->second;
			m_Table.erase(address);
		}
	};
	Operator_Container* FindSymbolByAddress (const int address) {
		if (m_Table.find(address) != m_Table.end()) {
			return m_Table.find(address)->second;
		} else {
			return nullptr;
		}
	};
private:
	std::map<int, Operator_Container*> m_Table;
};