#!/bin/python3.8
import sys
from random import randint

from neander import Neander


def test(n, i, i2, i3):
    try:
        if (i > 127 or i2 > 127):
            assert n.tape[131] == 0
            assert n.tape[132] == 1
            return False

        if (i3 < 1 or i3 > 4):
            assert n.tape[131] == 0
            assert n.tape[132] == 2
            return False

        if (i2 == 0 and i3 == 4):
            assert n.tape[131] == 0
            assert n.tape[132] == 3
            return False

        if (i3 == 1):
            assert (i + i2) & 255 == n.tape[131]
        elif (i3 == 2):
            assert (i - i2) & 255 == n.tape[131]
        elif (i3 == 3):
            assert (i * i2) & 255 == n.tape[131]
        elif (i3 == 4):
            assert (i // i2) & 255 == n.tape[131]

        return False

    except:
        print(i, i2, i3)
        return True


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

    print("Default tests:")
    errors = 0
    # Do a lot of tests
    for i in range(-100, 256):
        for i2 in range(-10, 256):
            for i3 in range(-1, 6):
                i = i & 255
                i2 = i2 & 255
                n.pc = 0
                n.tape[128] = i
                n.tape[129] = i2
                n.tape[130] = i3
                sys.stdout.write(f"Running default test: {i}, {i2}, {i3}   \r")
                sys.stdout.flush()
                try:
                    n.run()
                except:
                    print(f"\nErro: {i}, {i2}, {i3}")
                    errors += 1
                    continue

                errors += int(test(n, i, i2, i3))

    print("\nRandom tests:")
    for i in range(1_000_000):
        n.pc = 0
        j = randint(-1000, 1000) & 255
        j2 = randint(-1000, 1000) & 255
        j3 = randint(-1000, 1000) & 255
        n.tape[128] = j
        n.tape[129] = j2
        n.tape[130] = j3
        sys.stdout.write(f"Running random test: {i}      \r")
        sys.stdout.flush()
        try:
            n.run()
        except:
            print(f"\nErro: {j}, {j2}, {j3}")
            errors += 1
            continue

        errors += int(test(n, j, j2, j3))

    print()
    print(f"quantidade de erros: {errors}")


if __name__ == "__main__":
    main()
