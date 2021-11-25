#include "assembler.hpp"
#include "instructions.hpp"
#include <iostream>
#include "map.hpp"

int main (int argc, char *argv[]) {
    Table tb;
    Operator_Typedef d, c;
    std::cin >> d >> c;
    tb.AddSymbol(34, &d);
    tb.AddSymbol(4, &c);
    tb.PrintTable();
    return 0;
}