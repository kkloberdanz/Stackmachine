#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 200
#define PROG_SIZE  200

int program[PROG_SIZE];
int stack[STACK_SIZE];

int pc = 0;
int sp = 0;

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

enum {
    NOOP,
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
};

void print_stack() {
    printf("*** PRINTING STACK ***\n");
    int i;
    printf("SP: %d\n", sp);
    printf("PC: %d\n", pc);
    for (i = 0; i <= sp; ++i) {
        if (i == sp) { printf("%2d: %d*\n", i, stack[i]);
        } else {
            printf("%2d: %d\n", i, stack[i]);
        }
    }
    printf("*** DONE PRINTING ***\n");
}

int execute(int inst) {

    if (pc > PROG_SIZE) {
        printf("ERROR: PC out of bounds\n");
        print_stack();
        exit(EXIT_FAILURE);
    }

    if (sp > STACK_SIZE) {
        printf("ERROR: SP out of bounds\n");
        print_stack();
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    printf("%d\n", inst);
    if (inst != HALT) {
        printf("INST: %s, PC: %d, TOP: %d\n", inst_names[inst], pc, stack[sp]);
    }
#endif

    switch (inst) {

        case NOOP:
            break;

        case PUSH:
            sp++;
            stack[sp] = program[++pc];
            break;
            
        case LOAD: 
            stack[sp] = stack[program[++pc]];
            break;

        case STORE: 
            stack[program[++pc]] = stack[sp];
            break;

        case J:
            pc = program[pc+1];
            return 1;
            break;

        case JZ:
            if (stack[sp] == 0) {
                pc = program[pc+1];
                return 1;
            } else {
                pc++;
            }
            break;

        case JLEZ:
            if (stack[sp] <= 0) {
                pc = program[pc+1];
                return 1;
            } else {
                pc++;
            }
            break;

        case ADD:
            stack[sp] = stack[sp] + stack[sp-1];
            break;

        case SUB:
            stack[sp] = stack[sp] - stack[sp-1];
            break;

        case MUL:
            stack[sp] = stack[sp] * stack[sp-1];
            break;

        case DIV:
            stack[sp] = stack[sp] / stack[sp-1];
            break;


        case MOD:
            stack[sp] = stack[sp] % stack[sp-1];
            break;

        case PRINTI:
            printf("%d", stack[sp]);
            break;

        case READI:
            scanf("%d", &stack[sp]);
            break;

        case PRINTC: 
            printf("%c", stack[sp]);
            break;

        case READC:
            stack[sp] = getchar();
            break; 

        case POP:
            sp--;
            break;

        case HALT:
            printf("### HALTING ###\n");
            return 0;
            break;

        default:
            printf("ERROR: unknown instruction: %d\n", inst);
            print_stack();
            exit(EXIT_FAILURE);
    }
    ++pc;
    return 1;
}

void loop() {
    int inst = NOOP;
    for (pc = 0; execute(program[pc]); ) {
#ifdef DEBUG
        print_stack();
#endif
    }
}

int main(int argc, char** argv) { 

    /*
    int code[] = { PUSH, 2,     // Push 2
                   PUSH, 3,     // Push 3
                   ADD,          // 2 + 3 = 5
                   PRINTI,       // Print 5
                   PUSH, 10,    // Push \n
                   PRINTC,       // Print \n
                   POP,          // POP \n
                   PUSH, 17,    // Push 17
                   PRINTI,       // Print 12
                   PUSH, 10,    // Push \n
                   PRINTC,       // Print \n
                   POP,          // Pop \n
                   MOD,          // 12 % 5 = 2
                   PRINTI,       // Print 2
                   PUSH, 10,    // Push \n
                   PRINTC,       // Print \n
                   POP,          // Pop \n
                   LOAD, 2,      // Load 5
                   ADD,          // 5 + 5 = 10
                   PRINTI,
                   PRINTC,
                   HALT          // End
    };
    */

    /*
    int code[] = { 
        PUSH, 1,    
        PUSH, -3,    
        ADD,
        PRINTI,      
        PUSH, '\n',
        PRINTC,
        POP,
        JLEZ, 4,
        HALT         
    };
    */

    int code[] = { 
        PUSH, 1,       /* Used for loop */
        PUSH, -3,    
        STORE, 100,
        STORE, 101,

        PUSH, 2,       /* Mul 2 * 5 four times*/
        PUSH, 5,
        MUL,

        PRINTI,        /* Print results */
        PUSH, '\n',
        PRINTC,
        POP,

        LOAD, 100,
        LOAD, 101,

        ADD,
        JLEZ, 4,
        HALT         
    };

    printf("*** LOADING ***\n");
    int i;
    for (i = 0; code[i] != HALT; ++i) {
        program[i] = code[i];
#ifdef DEBUG
        printf("i = %d, Pushing: %s\n", i, inst_names[program[i]]);
#endif
    }
    program[i] = HALT;

    printf("*** DONE LOADING ***\n");
    printf("### RUNNING ###\n");

    loop();
    print_stack();
    return 0;
}
