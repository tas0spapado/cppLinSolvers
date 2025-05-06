#!/usr/bin/env python3
"""
A script to plot the iso-u contour.
Needs files: u, coordinates
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as mtri


def load_solution(filename):
    data = np.loadtxt(filename)
    if data.ndim == 1 or data.shape[-1] == 1:
        return data.flatten()
    return data[:, 1]


def load_coordinates(filename):
    data = np.loadtxt(filename)
    if data.ndim == 1 or data.shape[1] == 2:
        x, y = data[:, 0], data[:, 1]
    else:
        x, y = data[:, 1], data[:, 2]
    return x, y


def main():
    u = load_solution("u")
    x, y = load_coordinates("coordinates")

    triang = mtri.Triangulation(x, y)

    num_levels = 15
    levels = np.linspace(u.min(), u.max(), num_levels)

    fig, ax = plt.subplots(figsize=(6, 5))
    cf = ax.tricontourf(triang, u, levels=levels, cmap="viridis")

    cb = fig.colorbar(cf, ax=ax, orientation="vertical")
    cb.set_label("u value")

    ax.set_title("Iso-u Contour")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_aspect("equal", "box")

    plt.tight_layout()
    plt.savefig("contour.png", dpi=300)
    plt.show()


if __name__ == "__main__":
    main()
