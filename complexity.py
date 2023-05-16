import os
import subprocess
import matplotlib.pyplot as plt


size = 50
threads= 5

os.system("make")
resultes = []
sizes = []
while size <= 2500:
    cmd = 'make run IN="sol_par {} {}" NP={} \n'.format(2 * size, size, threads)
    result = subprocess.check_output(cmd, shell=True, text=True).split('\n')[-1]
    print("matrix_size 2n x n = {} x {}, time = {}s".format(2 * size, size, result))
    sizes.append(2 * size * size)
    resultes.append(float(result))
    size += 50

plt.figure(figsize=[12, 5], dpi=100)
plt.plot(list(sizes), resultes, linewidth=2, label='y1')

plt.xlabel("matrix_size 2n x n")
plt.ylabel("time")
plt.title("Сложность")
plt.minorticks_on()
plt.grid()
os.chdir("TransportEquation/data")
current_dir = os.getcwd()
print("Save {}/complexity.png".format(current_dir))
plt.savefig('complexity.png')