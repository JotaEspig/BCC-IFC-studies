.code16

.text
.globl _start
_start:
    call clear_screen

    xorw %cx, %cx
    movw $0x001, %ax
    cmpb $0, (ships)
    je draw_ships
    movw $0x0100, %ax

draw_ships:
    movw (ships + 1), %dx

_draw_ships_loop:
    push $254
    push %dx
    push $2
    call print_char_at
    add $6, %sp # Remove the arguments from the stack
    add %ax, %dx
    cmpw (ships + 3), %dx
    jle _draw_ships_loop

    # Move the cursor to the initial position
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


check_ship:



move_left:
    subb $0x1, cursor_position
    jmp main_loop

move_right:
    addb $0x01, cursor_position
    jmp main_loop

move_up:
    subb $0x1, cursor_position + 1
    jmp main_loop

move_down:
    addb $0x01, cursor_position + 1
    jmp main_loop

try:
    movb $0x06, %ah # Scroll up window
    xorb %al, %al # Clear the screen
    movw (cursor_position), %cx # Upper left corner
    movw (cursor_position), %dx # Lower right corner
    movb $0x1c, %bh # Red on Blue
    int $0x10

    movb $'X', %al
    movb $0x0e, %ah
    int $0x10
    jmp main_loop

move_cursor:
    pusha
    movb $0x02, %ah
    movb $0, %bh
    movw cursor_position, %dx
    int $0x10
    popa
    ret


main_loop:
    call move_cursor

    # Gets the key pressed
    movb $0x0, %ah
    xorb %al, %al
    int $0x16

    cmp $0x48, %ah
    je move_up
    cmp $0x50, %ah
    je move_down
    cmp $0x4b, %ah
    je move_left
    cmp $0x4d, %ah
    je move_right
    cmp $0x1c, %ah
    je try

    jmp main_loop


# Variables
. = _start + 450
cursor_position:
    .byte 0
    .byte 0
ships:
    # Ship 1
    .byte 0 # Is vertical
    .word 0x0a0c # Initial Position
    .word 0x0a12 # Final Position


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
