#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <map>
#include <regex>

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
            {"STORE",  13},
            {"J",      14},
            {"JZ",     15},
            {"JLEZ",   16}, 
            {"JNZ",    17}, 
            {"JWL",    18}, 
            {"JZWL",   19},
            {"JLEZWL", 20}, 
            {"JNZWL",  21}, 
            {"RET",    22},
            {"POPC",   23},
            {"HALT",   999999}
        };

        std::vector<std::string> input_v;
        std::vector<int64_t>     inst_v; 


        bool is_char(std::string inst) {
            std::regex char_regex("\'[a-zA-Z]\'");
            return regex_match(inst, char_regex);
        }

        // get instruction
        // if not a valid instruction, returns -1 and logs to stderr
        //     error: not a valid instruction
        int64_t translate(const std::string inst) {
            if (debug) {
                std::cout << "INST: " << inst << std::endl;
            }
            if (inst_m.find(inst) != inst_m.end()) {
                return inst_m.find(inst)->second;

            } else {
                std::cerr << "error: not a valid instruction '" << inst << "'" << std::endl;
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
                   (inst == "JNZ")     ||
                   (inst == "JLEZ")    ||
                   (inst == "JWL")     ||
                   (inst == "JZWL")    ||
                   (inst == "JNZWL")   ||
                   (inst == "JLEZWL");
        }

        bool is_jump(const std::string inst) {
            return (inst == "J")     ||
                   (inst == "JZ")    ||
                   (inst == "JNZ")   ||
                   (inst == "JLEZ")  ||
                   (inst == "JWL")   ||
                   (inst == "JZWL")    ||
                   (inst == "JNZWL")   ||
                   (inst == "JLEZWL");
        }

        std::string process(std::string s) {
            std::string ret_s;
            if (is_char(s)) {
                int n = s[1];
                //return std::string(s[1]);
                //std::cout << "HERE: " << s[1] << std::endl;;
                ret_s += std::to_string(n);
                return ret_s;
            }
            // process out comments and whitespace
            size_t i = 0;
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
            bool error = false;

            // Find labels
            for (size_t i = 0; i < v.size(); ++i) {
                inst = v.at(i);

                found = inst.find(':');
                if (found != std::string::npos) {
                    // then inst is label
                    //std::cout << inst.substr(0, found) << std::endl;
                    label_m[inst.substr(0, found)] = i;
                    v.erase(v.begin() + i); // remove label from vector
                }
            }

            // Replace jump targets with actual numbers
            for (size_t i = 0; i < v.size(); ++i) {
                inst = v.at(i);
                std::map<std::string, int64_t>::iterator it;
                it = label_m.find(inst);

                // if previous instruction is a jump,
                // then it MUST be followed by a label
                if ((i > 0) && (is_jump(v.at(i-1)))) {
                    if (it == label_m.end()) {
                        error = true;
                        std::cerr << "error: no matching label for jump target '" 
                            << inst << "'" << std::endl;
                    }
                }

                // If label was found, then replace instances of it with
                // the proper numerical value
                if (it != label_m.end()) {
                    v.at(i) = std::to_string(it->second);
                    //label_m.erase(it);
                }

                if (error) {
                    std::cerr << "error: Fatal error" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            /*
            if (!label_m.empty()) {
                std::cerr << "warning: unused labels" << std::endl;
            }
            */
        }

    public:
        void set_debug(bool d) {
            debug = d;
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
            int64_t immd;
            int64_t inst_as_long;
            bool error = false;
            for (size_t i = 0; i < input_v.size(); ++i) {

                inst_as_long = translate(input_v.at(i));
                if (inst_as_long == -1) { 
                    error = true;
                }

                if (debug) {
                    std::cout << input_v.at(i) << std::endl;
                }

                if (this->requires_immediate(input_v.at(i))) {
                    // load instruction
                    inst_v.push_back(inst_as_long);

                    // load immediate
                    i++;
                    immd = atol(input_v.at(i).c_str());
                    inst_v.push_back(immd);

                } else {
                    // load instruction
                    inst_v.push_back(inst_as_long);
                }
            }
            if (error) {
                std::cerr << "error: fatal error" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
}; 

#endif
