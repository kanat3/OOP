#include "map.hpp"
#include <map>
#include <iostream>

void Table::AddSymbol(const int a_loc, Operator_Container* a_operator) {
	std::map<int, Operator_Container*>::iterator st;
	st = m_Table.find(a_loc);
	m_Table[a_loc] = a_operator;
}

void Table::PrintTable (void) const {
	int index = 0;
	std::cout << "Symbol#    Address    Operator name" << std::endl;
	for (auto it = m_Table.begin(); it != m_Table.end(); ++it) {
        Operator_Container* a = it->second;
		std::cout << "   " << index++ << "\t    " << it->first << "\t      " << a->GetCode() << std::endl;
	}
}
