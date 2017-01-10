#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#define STACK_SIZE 200
#define PROG_SIZE  200

char inst_names[50][50] = {
    "NOOP",
    "PUSH",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "PRINTI",
    "READI",
    "PRINTC",
    "READC",
    "POP",
    "LOAD",
    "STORE",
    "J",
    "JZ",
    "JLEZ",
    "HALT"
};

typedef enum {
    NOOP = 0,
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINTI,
    READI,
    PRINTC,
    READC,
    POP,
    LOAD,
    STORE,
    J,
    JZ,
    JLEZ,
    HALT = 999999
} INST;
#endif /* INSTRUCTIONS_H */
