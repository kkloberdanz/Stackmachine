# Stackmahine

To build the assembler

```bash
$ make assembler
```

To build the stackmachine

```bash
$ make
```

Instruction Set:

#Immediate

PUSH        : Pushes immediate value, i.e. value below this instruction
              onto the top of the stack

STORE       : Stores top of stack to the specified memory location

LOAD        : Load the instruction at specifeid memory location to 
              top of stack

J           : Jump to specified label/memory address

JZ          : Conditional jump, jump if top of stack is 0

JLEZ        : Conditional jump, jump if top of stack is <= 0


#Stack

ADD         : Add top 2 numbers on stack, then push result to the top

SUB         : Subtract top 2 numbers on stack, then push result to the top

MUL         : Multiply

DIV         : Divide

MOD         : Modulus

PRINTI      : print top of stack as an integer

PRINTC      : print top of stack as character

READI       : Read an integer from stdin, put on top of stack

READC       : Read 1 character from stdin, put on top of stack

POP         : Pop top item off of stack

#System

HALT        : Terminate the program

NOOP        : No operation, do nothing

