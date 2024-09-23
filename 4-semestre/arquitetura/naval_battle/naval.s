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

    movw $0x0a0b, %dx
    push $254
    push %dx
    push $2
    call print_char_at
    add $6, %sp # Remove the arguments from the stack

    movw $0x0a0c, %dx
    push $254
    push %dx
    push $2
    call print_char_at
    add $6, %sp # Remove the arguments from the stack

    movw $0x0, %dx
    movb $2, %ah
    movb $0, %bh
    int $0x10

    jmp main_loop


clear_screen:
    pusha
    movb $0x06, %ah # Scroll up window
    xorb %al, %al # Clear the screen
    xorw %cx, %cx # Upper left corner
    movw $0x184f, %dx # Lower right corner
    movb $0x1f, %bh # White on Blue
    int $0x10
    popa
    ret


# Usage:
#  push %ax # Character to print (Should be on the Low byte)
#  push %dx # Coordinates x and y (Low byte is x, High byte is y)
#  push $2 # number of arguments
#  call print_char_at
#  pop %ax # Return code (it replaces the value of the number of arguments)
#  add $4, %sp # Remove the left argument from the stack
print_char_at:
    pusha
    # Gets the arguments from the stack
    movw %sp, %bp
    movw 18(%bp), %ax
    cmp $2, %ax
    jne _print_char_at_error
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

_print_char_at_error:
    movw $1, 18(%bp) # Return code (1 = error in the number of arguments)
    popa
    ret


move_left:
    addb $0xff, cursor_position
    jmp main_loop

move_right:
    addb $0x01, cursor_position
    jmp main_loop

move_up:
    addb $0xff, cursor_position + 1
    jmp main_loop

move_down:
    addb $0x01, cursor_position + 1
    jmp main_loop

move_cursor:
    pusha
    movb $0x02, %ah
    movb $0, %bh
    movb cursor_position, %dl
    movb cursor_position + 1, %dh
    int $0x10
    popa
    ret


main_loop:
    call move_cursor

    # Gets the key pressed
    movb $0x0, %ah
    xorb %al, %al
    int $0x16

    cmp $0x77, %al
    # Push current program counter to the stack
    je move_up
    cmp $0x73, %al
    je move_down
    cmp $0x61, %al
    je move_left
    cmp $0x64, %al
    je move_right

    jmp main_loop


. = _start + 450
cursor_position:
    .byte 0
    .byte 0

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
