PUSH    ; This pushes 10 to the stack
10

PUSH
1

SUB     ; Add the two top elements of stack, then push result

PRINTI  ; print integer

PUSH
10

PRINTC

POP

_Return:
    JLEZ
    _AddRoutine



HALT

_AddRoutine:

    PUSH            ; Add 1 to top of stack
    1
    ADD

    PRINTI          ; Print integer
    PUSH            ; Print Newline
    10
    PRINTC
    POP

    J
    _Return
