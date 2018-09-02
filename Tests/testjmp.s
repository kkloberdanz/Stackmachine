;PUSH    ; This pushes 10 to the stack
;10

;PUSH
;1

READI

READI

SUB     ; Sub the two top elements of stack, then push result

PRINTI  ; print integer

J
_PrintNewline

JLEZ
_AddRoutine

_Halt_success:
    PUSH
    0
    HALT

_Halt_failure:
    PUSH
    1
    HALT

; Adds 1 to the top of stack, prints the sum,
; then prints a new line
_AddRoutine:

    PUSH            ; Add 1 to top of stack
    1
    ADD

    PRINTI          ; Print integer

    J               ; Print newline
    _PrintNewline

    JLEZ
    _AddRoutine 

    RET

_PrintNewline:
    PUSH            ; Print Newline
    10
    PRINTC
    POP
    RET

; Not yet working
; Prints a NULL terminated string to the console
_PrintASCII:

    ; TODO Bring data from string pointer to the top of stack

    PRINTC          ; Print char then pop
    POP

    JNZ             ; Print until 0 on top of stack (0 is end of string)
    _PrintASCII
    RET
