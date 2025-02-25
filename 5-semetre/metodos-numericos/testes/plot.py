# Make a plot of a curve given by a function
import numpy as np
import matplotlib.pyplot as plt


def plot_curve(f, a, b, n):
    x = np.linspace(a, b, n)
    y = f(x)
    plt.plot(x, y)
    plt.xlabel('x-axis')
    plt.ylabel('y-axis')
    plt.show()


def f(x):
    return x**2 - 1


plot_curve(f, -10, 10, 100)
