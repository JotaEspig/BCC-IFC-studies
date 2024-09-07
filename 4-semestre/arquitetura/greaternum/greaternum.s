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

    movb (v1), %bl
    movb (v2), %cl
    cmpb %bl, %cl
    jl next1

    movb %cl, %bl

next1:
    movb (v3), %cl
    cmpb %bl, %cl
    jl next2

    movb %cl, %bl

next2:
    movb %bl, %al
    add $0x30, %al
    movb $0x0e, %ah
    int $0x10

loop_final:
    hlt
    jmp loop_final

. = _start + 300

v1: .byte 0x09 # Hardcoded
v2: .byte 0x07 # Hardcoded
v3: .byte 0x05 # Hardcoded

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
