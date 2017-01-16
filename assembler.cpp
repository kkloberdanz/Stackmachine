#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdint>

#include "assembler.hpp"

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "error: no input file specified" << std::endl;
        exit(EXIT_FAILURE);
    }

    Assembler asmblr;

#ifdef DEBUG
    asmblr.set_debug();
#endif

    asmblr.from_file(argv[1]);
    asmblr.assemble();
    asmblr.to_file(argv[2]);

    return 0;
}
