#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

class Assembler {
    private:
        bool debug;

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
            {"LOADRA", 13},
            {"STORE",  14},
            {"STORERA",15},
            {"J",      16},
            {"JZ",     17},
            {"JLEZ",   18},
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
            return (inst == "PUSH")    ||
                   (inst == "STORE")   ||
                   (inst == "STORERA") ||
                   (inst == "LOAD")    ||
                   (inst == "LOADRA")  ||
                   (inst == "J")       ||
                   (inst == "JZ")      ||
                   (inst == "JLEZ");
        }

        std::string process(std::string s) {
            std::string ret_s;
            // process out comments and whitespace
            int i = 0;
            while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')) {
                i++;
            }
            char c;
            for (; i < s.size(); ++i) {
                c = s[i];
                if ((c != ';') && (c != '#') && (c != ' ') && (c != '\t') && (c != '\n')) {
                    ret_s += c;
                } else {
                    return ret_s;
                }
            }
            return ret_s;
        }

        void assign_labels(std::vector<std::string>& v) {
            std::map<std::string, int64_t> label_m;
            std::string inst;
            int found;
            for (int64_t i = 0; i < v.size(); ++i) {
                inst = v.at(i);

                found = inst.find(':');
                if (found != std::string::npos) {
                    // then inst is label
                    //std::cout << inst.substr(0, found) << std::endl;
                    label_m[inst.substr(0, found)] = i;
                    v.erase(v.begin() + i); // remove label from vector
                }
            }

            for (int64_t i = 0; i < v.size(); ++i) {
                inst = v.at(i);
                if (label_m.find(inst) != label_m.end()) {
                    v.at(i) = std::to_string(label_m.find(inst)->second);
                }
            }
        }

    public:
        bool set_debug() {
            debug = true;
        }

        Assembler() {
            debug = false;
        }

        void from_file(const char* filename) {
            std::string line;
            std::ifstream in_f(filename);
            while (getline(in_f, line)) {
                line = process(line);
                if (!line.empty()) {
                    input_v.push_back(line);
                }
            }
        }

        void to_file(const char* filename) {
            std::ofstream out_f(filename);
            for (const int64_t& inst : inst_v) { 
                out_f << inst << std::endl;
            }
        }

        void assemble() {
            assign_labels(input_v);
            for (size_t i = 0; i < input_v.size(); ++i) {
                if (debug) {
                    std::cout << input_v.at(i) << std::endl;
                }
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
