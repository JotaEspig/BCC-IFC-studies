.code16

.text
.globl _start
_start:
    call clear_screen

    movw $0x0a0a, %dx
    push $254
    push %dx
    push $2
    call print_char_at
    add $6, %sp # Remove the arguments from the stack


    jmp loop_final


clear_screen:
    pusha
    movb $0x06, %ah # Scroll up window
    xorb %al, %al # Clear the screen
    xorw %cx, %cx # Upper left corner
    movw $0x184f, %dx # Lower right corner
    movb $0x9f, %bh # Yellow on blue
    int $0x10
    popa
    ret


print_char_at:
    # Usage:
    #  push %ax # Character to print (Should be on the Low byte)
    #  push %dx # Coordinates x and y (Low byte is x, High byte is y)
    #  push $3 # number of arguments
    #  call print_char_at
    #  pop %ax # Return code (it replaces the value of the number of arguments)
    #  add $6, %sp # Remove the left argument from the stack
    pusha

    # Gets the arguments from the stack
    movw %sp, %bp
    movw 18(%bp), %ax
    cmp $2, %ax
    je _print_char_at_args_ok
    movw $1, 18(%bp) # Return code (1 = error in the number of arguments)
    popa
    ret

_print_char_at_args_ok:
    # Go to coordinates
    movw 20(%bp), %dx
    movb $2, %ah
    movb $0, %bh
    int $0x10

    # Print the character
    movw 22(%bp), %ax
    movb $0x0e, %ah
    int $0x10
    popa
    movw $0, 18(%bp) # Return code (0 = success)
    ret


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
