import numpy as np


def gauss_jacobi(A, b, x0, tol, maxiter):
    # Gauss-Jacobi
    n = len(b)
    x = np.copy(x0)
    for k in range(1, maxiter+1):
        x_new = np.copy(x)
        for i in range(n):
            s = 0
            for j in range(n):
                if j != i:
                    s += A[i, j] * x_new[j]

            x_new[i] = (b[i] - s) / A[i, i]

        if np.linalg.norm(x_new - x) < tol:
            print(k)
            return x_new
        x = np.copy(x_new)

    print(maxiter)
    return x


def gauss_seigel(A, b, x0, tol, maxiter):
    # Gauss-Seigel
    n = len(b)
    x = np.copy(x0)
    for k in range(1, maxiter+1):
        for i in range(n):
            s = 0
            for j in range(n):
                if j != i:
                    s += A[i, j] * x[j]

            x[i] = (b[i] - s) / A[i, i]

        if np.linalg.norm(A @ x - b) < tol:
            print(k)
            return x

    print(maxiter)
    return x


if __name__ == "__main__":
    a = np.array([[10, 2, 1], [1, 5, 1], [2, 3, 10]], dtype=float)
    b = np.array([7, -8, 6], dtype=float)
    x0 = np.array([0.7, -1.6, 0.6], dtype=float)
    tol = 1e-8
    maxiter = 1000
    x = gauss_jacobi(a, b, x0, tol, maxiter)
    x2 = gauss_seigel(a, b, x0, tol, maxiter)
    print(x)
    print(x2)
    print(np.linalg.solve(a, b))
