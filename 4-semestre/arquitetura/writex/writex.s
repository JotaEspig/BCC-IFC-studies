/**
    * \author: Éder Augusto Penharbel
    * \date: February, 2022
    * \version: September 6, 2024     
**/

# generate 16-bit code
.code16 			    
# executable code location
.text 				    
# global makes a symbol visible to the linker and available to other 
# linking object modules 
.globl _start
# ld looks for this _start label as the default entry point of a program
_start:				
    # move one byte to register al, lower part of register ax, in AT&T 
    # syntax register are preceded by % symbol, literals are preceded 
    # by $ symbol
    movb $'x' , %al		# character to print
    # move one byte to register ah, higher part of register ax
    movb $0x0e, %ah		
    # The architecture of IBM-PC AT/XT model uses sofware interrupt to
    # provide some services, int 0x10 is related to VIDEO services, 
    # BIOS services
    int  $0x10		    # bios service (interrupt) 
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
