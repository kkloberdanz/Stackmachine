#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 200
#define PROG_SIZE  200

int *program;
int stack[STACK_SIZE];

/* Registers */
int pc = 0; /* Program Counter */
int sp = 0; /* Stack Pointer */
int ra = 0; /* Return address returns address 
               after jump instructions */

int sr = PROG_SIZE; /* Stack Register 
                       Used for saving data to the stack */

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
    "LOADRA",
    "STORE",
    "STORERA",
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
    LOADRA,
    STORE,
    STORERA,
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
        if (i == sp) { 
            printf("%2d: %d*\n", i, stack[i]);
        } else {
            printf("%2d: %d\n", i, stack[i]);
        }
    }
    printf("*** DONE PRINTING ***\n");
}

int get_num_lines(char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    int count = 0;
    char c;
    while ( (c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(fp);
    return count;
}

void load_code_from_file(int *code, char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");

    char buff[255];
    char c;
    int  count = 0, i = 0;
    printf("Reading from: %s\n", filename);
    while ( (c = fgetc(fp)) != EOF) { 
        if (c == '\n') {
            buff[count] = '\0';
            count = 0;
            /*printf("CODE: '%s'\n", buff);*/
            code[i] = atoi(buff);
            i++;
        }
        buff[count] = c;
        count++;
    }
    fclose(fp);
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
    /*printf("%d\n", inst);*/
    if (inst != HALT) {
        printf("\nINST: %s, PC: %d, SP: %d, TOP: %d\n", inst_names[inst], pc, sp, stack[sp]);
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

        case LOADRA:
             ra = stack[sr];
             sr++;
             break;

        case STORE: 
            stack[program[++pc]] = stack[sp];
            break;

        case STORERA:
            stack[sr] = ra;
            sr--;
            break;

        case J:
            ra = pc+1;
            pc = program[pc+1]; 
#ifdef DEBUG
            printf("J target: %d\n", pc);
#endif
            return 1;
            break;

        case JZ:
            ra = pc+1;
            if (stack[sp] == 0) {
                pc = program[pc+1];
#ifdef DEBUG
                printf("JZ target: %d\n", pc);
#endif
                return 1;
            } else {
                pc++;
            }
#ifdef DEBUG
            printf("JZ target: %d\n", pc);
#endif
            break;

        case JLEZ:
            ra = pc+1;
            if (stack[sp] <= 0) {
                pc = program[pc+1];
#ifdef DEBUG
                printf("JLEZ target: %d\n", pc);
#endif
                return 1;
            } else {
                pc++;
            }
#ifdef DEBUG
            printf("JLEZ target: %d\n", pc);
#endif
            break;

/*
        case JRA:
            pc = ra+1;
#ifdef DEBUG
            printf("JRA target: %d\n", pc);
#endif
            break;
*/

        case ADD:
            {
            int a = stack[sp--];
            int b = stack[sp];
            stack[sp] = a + b;
            }
            break;

        case SUB:
            {
            int a = stack[sp--];
            int b = stack[sp];
            stack[sp] = a - b;
            }
            break;

        case MUL:
            {
            int a = stack[sp--];
            int b = stack[sp];
            stack[sp] = a * b;
            }
            break;

        case DIV:
            {
            int a = stack[sp--];
            int b = stack[sp];
            stack[sp] = a / b;
            }
            break;


        case MOD:
            {
            int a = stack[sp--];
            int b = stack[sp];
            stack[sp] = a % b;
            }
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

void print_array(int* arr, int size) {
    int i;
    printf("[");
    for (i = 0; i < size - 1; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[i]);
}

int main(int argc, char** argv) { 

    if (argc < 2) {
        fprintf(stderr, "error: specify the file name");
        exit(EXIT_FAILURE);
    } 

    printf("*** LOADING ***\n");
    int num_lines = get_num_lines(argv[1]);
    program = malloc(num_lines * sizeof(int));

    load_code_from_file(program, argv[1]);
#ifdef DEBUG
    print_array(program, num_lines);
#endif

    printf("*** DONE LOADING ***\n");
    printf("### RUNNING ###\n");

    loop();
    print_stack();
    free(program);
    return 0;
}
