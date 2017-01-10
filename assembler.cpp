#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdint>

#include "instructions.h"
#include "assembler.hpp"

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "error: no input file specified" << std::endl;
        exit(EXIT_FAILURE);
    }

    Assembler asmblr;
    asmblr.set_debug();

    asmblr.from_file(argv[1]);
    asmblr.assemble();
    asmblr.to_file(argv[2]);

    return 0;
}
