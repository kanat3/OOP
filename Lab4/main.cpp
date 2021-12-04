#include "assembler.hpp"
#include <iostream>
#include "map.hpp"

int main (int argc, char *argv[]) {
    if (argc == 1) {
        puts("No file. Work with console.");
        puts("..........Soon.............");
    } else {
        Assembler run(argc, argv);
        run.WriteInstruction();
        run.DisplayInfo();
    }
    return 0;
}