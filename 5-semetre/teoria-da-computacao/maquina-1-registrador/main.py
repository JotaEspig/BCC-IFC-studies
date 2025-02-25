class Machine:
    def __init__(self, *, reg: int = 0):
        self.reg = reg

    def dec(self):
        self.reg -= 1

    def inc(self):
        self.reg += 1

    def is_zero(self):
        return self.reg == 0


def op(m: Machine):
    if not m.is_zero():
        m.dec()
        op(m)
        m.inc()
        m.inc()


if __name__ == "__main__":
    m = Machine(reg=2)

    op(m)
    print(m.reg)
