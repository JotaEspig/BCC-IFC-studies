# Copyright (c) 2023 João Vitor Espig. All Rights Reserved.
from __future__ import annotations


class Neander:
    def __init__(self) -> None:
        self.tape: list[int] = [0] * 256
        self.pc: int = 0
        self.ac: int = 0
        self.instructions = {
                0: self.NOP,
                16: self.STA,
                32: self.LDA,
                48: self.ADD,
                64: self.OR,
                80: self.AND,
                96: self.NOT,
                128: self.JMP,
                144: self.JN,
                160: self.JZ
                }

    def read_hex_code(self, hex_code: str) -> None:
        hex_code = hex_code.replace("\n", "")
        for i in range(8, len(hex_code), 4):
            self.tape[(i - 8) // 4] = int(hex_code[i:i+2], base=16)
    
    def generate_mnemonics_list(self) -> str:
        mnemonics = ""
        is_value = False
        for idx, elem in enumerate(self.tape):
            mnemonics += f"{idx} - "
            if is_value:
                mnemonics += f"{elem}\n"
                is_value = False
            else:
                if elem != 96 and elem != 0 and elem != 240:
                    is_value = True

                if elem == 240:
                    mnemonics += "HLT\n"
                    continue

                try:
                    mnemonics += f"{self._get_instruction(elem).__name__}\n"
                except:
                    mnemonics += f"{elem}\n"

        return mnemonics[:-1]

    def _get_instruction(self, num: int):
        instruction = self.instructions[num]
        if instruction == None:
            raise "Invalid Opcode"

        return instruction

    def run(self) -> None:
        is_value = False
        while True:
            elem = self.tape[self.pc]
            if is_value:
                is_value = False
                self.pc += 1
                continue

            if elem == 240:
                return

            self.pc += 1
            instruction = self._get_instruction(elem)
            if elem == 96:
                is_value = instruction()
            else:
                is_value = instruction(self.tape[self.pc])

    def NOP(self):
        return False

    def STA(self, end):
        self.tape[end] = self.ac
        return True

    def LDA(self, end):
        self.ac = self.tape[end]
        return True

    def ADD(self, end):
        self.ac = (self.ac + self.tape[end]) & 255 

        return True

    def OR(self, end):
        self.ac = self.ac | self.tape[end]
        return True

    def AND(self, end):
        self.ac = self.ac & self.tape[end]
        return True

    def NOT(self):
        self.ac = ~self.ac
        return False

    def JMP(self, end):
        self.pc = end
        return False

    def JN(self, end):
        if (self.ac > 127):
            self.pc = end
            return False

        return True

    def JZ(self, end):
        if (self.ac == 0):
            self.pc = end
            return False

        return True
