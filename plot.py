import os
import sys
import matplotlib.pyplot as plt
import numpy as np



def calculate_sol(file = "../ParallelSolution/data/solution.txt"):
    u = np.genfromtxt(file, delimiter=' ')
    print(u)

    ts = np.linspace(0, 1, len(u))
    xs = np.linspace(0, 1, len(u[0]))
    return u, ts, xs


def calculate_sol_par(file = "../ParallelSolution/data/solution.txt"):
    with open(file, 'r') as f:
        lines = f.readlines()
    first_part = list(map(float, lines[0].split()))
    u = np.zeros((len(lines), len(first_part)))

    for i in range(len(lines)):
        u[i] = np.array(list(map(float, lines[i].split())))
    print(u)

    ts = np.linspace(0, 1, len(u))
    xs = np.linspace(0, 1, len(u[0]))
    return u, ts, xs



def make_surface(u, t, x, title=''):
    fig = plt.figure(figsize=(20, 20))
    ax = plt.axes(projection='3d')
    ts, xs = np.meshgrid(t, x)
    ax.plot_surface(ts, xs, u.T, rstride=1, cstride=1, cmap='jet', edgecolor='none')
    ax.view_init(20, -130)
    size=22
    if title != '':
        ax.set_title(title, fontsize=size)
    ax.set_xlabel('t', fontsize=size)
    ax.set_ylabel('x', fontsize=size)
    ax.set_zlabel('u(t, x)', fontsize=size)

    # plt.show()


# u, ts, xs = calculate_sol()
u, ts, xs = calculate_sol_par()

make_surface(u, ts, xs)

# os.chdir("./TransportEquation/ConsistentSolution/data/")
os.chdir("./TransportEquation/ParallelSolution/data/")
current_dir = os.getcwd()
print("{}/solution.png".format(current_dir))
plt.savefig('solution.png')