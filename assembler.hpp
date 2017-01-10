#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

class Assembler {
    private:
        bool debug = false;

        std::map<std::string, int64_t> inst_m = {
            {"NOOP",    0},
            {"PUSH",    1},
            {"ADD",     2},
            {"SUB",     3},
            {"MUL",     4},
            {"DIV",     5},
            {"MOD",     6},
            {"PRINTI",  7},
            {"READI",   8},
            {"PRINTC",  9},
            {"READC",  10},
            {"POP",    11},
            {"LOAD",   12},
            {"STORE",  13},
            {"J",      14},
            {"JZ",     15},
            {"JLEZ",   16},
            {"HALT",   999999}
        };

        std::vector<std::string> input_v;
        std::vector<int64_t>     inst_v;

        // get instruction
        // if not a valid instruction, returns -1 and logs to stderr
        //     error: not a valid instruction
        int64_t translate(const std::string inst) {
            if (inst_m.find(inst) != inst_m.end()) {
                return inst_m.find(inst)->second;
            } else {
                std::cerr << "error: not a valid instruction" << std::endl;
                return -1;
            }
        }

        bool requires_immediate(const std::string inst) {
            return (inst == "PUSH")  ||
                   (inst == "STORE") ||
                   (inst == "LOAD")  ||
                   (inst == "J")     ||
                   (inst == "JZ")    ||
                   (inst == "JLEZ");
        }

    public:
        bool set_debug() {
            debug = true;
        }

        Assembler() {
            //
        }

        void from_file(const char* filename) {
            std::string line;
            std::ifstream in_f(filename);
            while (getline(in_f, line)) {
                input_v.push_back(line);
            }
        }

        void to_file(const char* filename) {
            std::ofstream out_f(filename);
            for (const int64_t& inst : inst_v) { 
                out_f << inst << std::endl;
            }
        }

        void assemble() {
            for (size_t i = 0; i < input_v.size(); ++i) {
                if (this->requires_immediate(input_v.at(i))) {
                    // load instruction
                    inst_v.push_back(translate(input_v.at(i)));
                    i++;
                    // load immediate
                    inst_v.push_back(atol(input_v.at(i).c_str()));
                } else {
                    // load instruction
                    inst_v.push_back(translate(input_v.at(i)));
                }
            }
        }
}; 

#endif
