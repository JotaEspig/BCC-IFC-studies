#!/bin/python3.8
import sys

from neander import Neander


def main() -> None:
    if len(sys.argv) < 2:
        print("Usage: python3 main.py <filename>")
        return

    filename = sys.argv[1]
    content = ""
    with open(filename, "r") as file:
        content = "".join(file.readlines())

    n = Neander()
    n.read_hex_code(content)
    print(n.generate_mnemonics_list())
    input()

    # Do a lot of tests
    for i in range(-100, 256):
        for i2 in range(-10, 256):
            for i3 in range(-10, 10):
                i = i & 255
                i2 = i2 & 255
                n.pc = 0
                n.tape[128] = i
                n.tape[129] = i2
                n.tape[130] = i3
                n.run()
                try:
                    if (i > 127 or i2 > 127):
                        assert n.tape[131] == 0
                        assert n.tape[132] == 1
                        continue

                    if (i3 < 1 or i3 > 4):
                        assert n.tape[131] == 0
                        assert n.tape[132] == 2
                        continue

                    if (i2 == 0 and i3 == 4):
                        assert n.tape[131] == 0
                        assert n.tape[132] == 3
                        continue

                    if (i3 == 1):
                        assert (i + i2) & 255 == n.tape[131]
                    elif (i3 == 2):
                        assert (i - i2) & 255 == n.tape[131]
                    elif (i3 == 3):
                        assert (i * i2) & 255 == n.tape[131]
                    elif (i3 == 4):
                        assert (i // i2) & 255 == n.tape[131]

                except:
                    print(i, i2, i3)


if __name__ == "__main__":
    main()
