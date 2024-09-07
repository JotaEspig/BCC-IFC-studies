.code16

.text

.globl _start
_start:
    movb $0x0e, %ah	# BIOS teletype output function
    movb $'j' , %al		# character to print
    int  $0x10		    # bios service (interrupt) 
    call new_line

    # Add
    movb (in1), %al
    addb (in2), %al
    movb %al, (out1)
    call int_to_char
    call new_line

    # Sub
    # push 2 bytes, first input goes to less significant byte and second input
    # goes to most significant byte
    push (in1)
    call subtrair
    pop %ax
    movb %al, (out2)
    call int_to_char
    call new_line

    jmp loop_final


int_to_char:
    pusha                  # Save all registers
    mov $0, %ah            # Ensure AH is 0 for division
    mov $10, %bx           # BX = 10 for division
    mov $0, %cx            # CX will count digits (optional)

convert_loop:
    xor %dx, %dx           # Clear DX before DIV (DX:AX is divided by BX)
    div %bx                # Divide AX by BX -> quotient in AL, remainder in DL
    add $48, %dl           # Convert remainder (in DL) to ASCII by adding 48
    push %dx               # Save remainder (digit) on stack
    inc %cx                # Increment digit counter (optional)
    cmp $0, %al            # Check if quotient is zero
    jne convert_loop       # If not, repeat

print_digits:
    pop %ax                # Pop a digit from the stack
    mov $0x0E, %ah         # BIOS teletype function
    int $0x10              # Print character in AL
    loop print_digits      # Loop until all digits are printed
    popa                   # Restore all registers
    ret                    # Return to the caller


new_line:
    pusha
    # new line
    movb $0x0a, %al
    movb $0x0e, %ah
    int $0x10
    # move cursor to the beginning of the line
    movb $0x0d, %al
    int $0x10
    popa
    ret


subtrair:
    # Pega o argumento da stack
    # e retorna o valor para a stack
    # uso:
    # push <2 bytes, first byte being the first operand and the second the second operand>
    # call subtrair
    # pop <register> to get the result
    pusha
    # Pega argumento
    push %bp
    mov %sp, %bp
    mov 20(%bp), %ax

    # Subtrai with add
    not %ah
    inc %ah
    add %ah, %al
    xor %ah, %ah

    # Modifica a stack para "retornar" o valor
    mov %ax, 20(%bp)
    pop %bp
    popa
    ret


loop_final:
    hlt
    jmp loop_final

. = _start + 400

in1: .byte 10
in2: .byte 3
out1: .byte
out2: .byte
out3: .byte
out4: .byte
aux1: .byte
aux2: .byte

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
