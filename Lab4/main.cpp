#include "assembler.hpp"
#include <iostream>
#include "map.hpp"

int main (int argc, char *argv[]) {
    if (argc == 1) {
        puts("Usage: ./<*.exe> <file>");
    } else {
        Assembler run(argc, argv);
        run.RunAssembler();
        /**********************************************/
        // cat text.txt
        std::cout << std::endl << "Original statement: " << std::endl;
        system("cat text.txt");
        std::cout << std::endl;
        /*********************************************/
    }
    return 0;
}