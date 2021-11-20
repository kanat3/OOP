//Table class
#pragma once
#include <map>
#include <any>
#include <string>

class Table {

public:
	Table() {};
	~Table() {};

	// Add a new symbol to the symbol table.
	void AddSymbol(std::string &a_symbol, int a_loc);
	// Display the symbol table.
	void DisplaySymbolTable() const;
	// Lookup a symbol in the symbol table.
	bool LookupSymbol(const std::string &a_symbol, int &a_loc);
    // Find symbol by address
    std::any FindSymbol (const std::string& address) const;
    // Delete symbol by address
    void DeleteSymbol (const std::string& address);
private:
	// Mb not using map?
	std::map<std::string, std::any> m_Table;
};