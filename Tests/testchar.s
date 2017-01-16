PUSH                    ; End of string
0
                        ; String gets pushed backwards (This spells AND)

PUSH                    ; Just like in C, an ascii char surrounded by
'D'                     ; single quotes is replaced by its ascii value

PUSH
'N'

PUSH
'A'

J                       ; Print from top of stack until o (NULL) as ASCII
_PrintASCII

J                       ; Print Newline
_PrintNewline

PRINTI                  ; Print top of stack (0/NULL)

J                       ; Print Newline
_PrintNewline

J
_LoadString

J
_PrintASCII

J
_PrintNewline

HALT                    ; Terminate


; ########## Subroutines ########## 

; Prints a newline to stdout
_PrintNewline:
    PUSH
    10
    PRINTC
    POP
    RET


; "Forgets" most recent call
; Essentially used to jump back to the call before
; the most recent call
_POPC_and_RET:
    POPC
    RET



; Generic return subroutine
; Useful to break out of subroutines without linking
_Ret:
    RET



; Prints 0/NULL terminated ascii string to stdout
_PrintASCII:
    JZWL        ; if 0 at top of stack (i.e. NULL, end of string)
    _Ret        ; Return to previous call

    PRINTC      ; Print char
    POP         ; Remove from stack

    JNZWL       ; If 0 is not on top of stack (i.e. chars are left in string)
    _PrintASCII ; recursive call

    RET         ; return to caller



; Load string from stdin to the stack
_LoadString:
    PUSH                ; Terminating NULL at end of string
    0

    __RecLoadString__:     ; Read until RETURN is pressed
        READC

        JNZWL           ; recursive call, if top is not 0, keep reading
        __RecLoadString__

    POP                 ; Top NULL char is not needed
    RET
