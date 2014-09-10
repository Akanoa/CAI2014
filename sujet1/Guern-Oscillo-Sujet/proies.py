# -*- coding: utf-8 -*-
# José OUIN : algorithmique et calcul numérique, ellipses 2013
import matplotlib.pyplot as plt
import numpy as np


def proies(u, v, a, b):
    return u*(a - b*v)


def predateurs(u, v, c, d):
    return v*(-c + d*u)

if __name__ == "__main__":
    a, b = 0.8, 0.4
    c, d = 0.6, 0.2
    u0, v0 = 3, 5
    t_debut, t_fin = 0.0, 20.0
    n = 200

    h = (t_fin - t_debut)/n
    t = np.zeros(n+1)
    u = np.zeros(n+1)
    v = np.zeros(n+1)

    t[0], u[0], v[0] = t_debut, u0, v0
    for i in range(n):
        t[i+1] = t[0] + h*(i+1)
        u[i+1] = u[i] + h*proies(u[i], v[i], a, b)
        v[i+1] = v[i] + h*predateurs(u[i], v[i], a, b)

    plt.plot(t, u, "+b")
    plt.plot(t, v, "*r")
    plt.show()
