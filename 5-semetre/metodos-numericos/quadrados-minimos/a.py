from typing import Callable
import numpy as np


class MathFn:
    def __init__(self, fn: Callable, a1, a2):
        self.fn = fn
        self.a1 = a1
        self.a2 = a2

    def __call__(self, x: float) -> float:
        return self.fn(x)

    def __str__(self) -> str:
        return f"{self.a2:.3f}x + {self.a1:.3f}"


def linear_interpolation(points: list[tuple[float, float]]) -> MathFn:
    gs = [lambda _: 1, lambda x: x]
    m = [[0, 0]] * len(gs)
    mat = np.matrix(m)
    b = [0.0] * len(gs)

    mat[0, 0] = len(points)
    for p in points:
        mat[1, 0] += gs[1](p[0])
        mat[0, 1] += gs[1](p[0])
        mat[1, 1] += gs[1](p[0]) ** 2
        b[0] += p[1]
        b[1] += gs[1](p[0]) * p[1]

    sol = np.linalg.solve(mat, b)
    return MathFn(lambda x: sol[0] + x * sol[1], *sol)


p = [
    (1, 0.5), (2, 0.6), (3, 0.9), (4, 0.8), (5, 1.2), (6, 1.5), (7, 1.7), (8, 2)
]
f = linear_interpolation(p)
print("FUNCTION:", f)

p = []
for i in range(1, 10):
    p.append((i, i*2))

f = linear_interpolation(p)
print("FUNCTION:", f)
