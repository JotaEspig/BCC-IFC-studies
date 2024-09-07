# generate 16-bit code
.code16 			    
# executable code location
.text

# global makes a symbol visible to the linker and available to other 
# linking object modules 
.globl _start

# ld looks for this _start label as the default entry point of a program
_start:				
    # move one byte to register ah, higher part of register ax
    movb $0x0e, %ah	# BIOS teletype output function

    # move one byte to register al, lower part of register ax, in AT&T 
    # syntax register are preceded by % symbol, literals are preceded 
    # by $ symbol
    movb $'j' , %al		# character to print
    # The architecture of IBM-PC AT/XT model uses sofware interrupt to
    # provide some services, int 0x10 is related to VIDEO services, 
    # BIOS services
    int  $0x10		    # bios service (interrupt) 

    movb $'o', %al
    int $0x10
    movb $'t', %al
    int $0x10
    movb $'a', %al
    int $0x10
    # new line
    movb $0x0a, %al
    int $0x10
    # move cursor to the beginning of the next line
    movb $0x0d, %al
    int $0x10

    mov $42, %al
    call int_to_char

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

loop_final:
    # halt instruction in 8086 processor causes to enter in the halt state,
    # the processor leaves this state upon the activation of the RESET line,
    # upon receipt a non-maskable interuption requested on NMI, or, if 
    # interruption are enabled, upon receipt of a maskable interuption 
    # request on INTR. HLT does not affect any processor flags. It may be
    # used as an alternative to endless software loop in situation where
    # a program must wait for an interruption.
    hlt
    # if the processor receive a interrupt it will leave halt state then
    # it must jump to a halt state again
    jmp loop_final

# `.` (dot) symbol represents the current location counter, which holds the 
# memory address of the instruction or data being assembled at that moment. It 
# can be used to refer to the current position in code or data.

# this line will move the current location to counter to the 510th byte
# counting from 0 
. = _start + 510	    # mov to 510th byte from 0 pos

# this program will be loaded by BIOS. This code will be loaded at position
# 0x7c00, in order to this program be recognized as a MBR signature it will
# be necessary to have two bytes at 510 and 511 position with values 0x55 and
# 0xaa

# MBR boot signature
.byte 0x55		        
.byte 0xaa		        
