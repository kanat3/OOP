#include "map.hpp"
#include <iostream>

/********************************/
//			STL MAP
/*********************************/

/*
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

Table::~Table (void) {
	for (auto it = m_Table.begin(); it != m_Table.end(); ++it) {
        Operator_Container* a = it->second;
		delete a;
	}	
}
*/

/*****************************************/
//				MY MAP
/*****************************************/

void Table::AddSymbol(const int a_loc, Operator_Container* a_operator) {
	m_Table.insert(a_loc, a_operator);
}

void Table::PrintTable (void) const {
	int index = 0;
	const Map<int, Operator_Container*>::iterator it;
	std::cout << "Symbol#    Address    Operator name" << std::endl;
	for (auto it = m_Table.m_begin(); it != m_Table.m_end(); ++it) {
        Operator_Container* a = it._node->data;
		std::cout << "   " << index++ << "\t    " << it._node->key << "\t      " << a->GetCode() << std::endl;
	}
}

Table::~Table (void) {
	for (auto it = m_Table.m_begin(); it != m_Table.m_end(); ++it) {
        Operator_Container* a = it._node->data;
		delete a;
	}	
}