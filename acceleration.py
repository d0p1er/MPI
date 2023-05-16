import os
import subprocess
import matplotlib.pyplot as plt
import numpy as np


os.system("make")
accelerations = []
efficiencies = []
sizes = []
threads = 1


cmd = 'make run IN="sol_par {} {}" NP={} \n'.format(4000, 2000, threads)
result = subprocess.check_output(cmd, shell=True, text=True).split('\n')[-1]
sizes.append(threads)
accelerations.append(1.0)
efficiencies.append(1.0)
seq = float(result)
threads = 2
while threads < 32:
    cmd = 'make run IN="sol_par {} {}" NP={} \n'.format(4000, 2000, threads)
    result = subprocess.check_output(cmd, shell=True, text=True).split('\n')[-1]
    print("n_proc = %s, time = %ss" % (str(threads), result))
    sizes.append(threads)
    accelerations.append(seq / float(result))
    efficiencies.append(seq / (float(result) * threads))
    threads += 1

plt.figure(figsize=[12, 5], dpi=100)
plt.plot(list(sizes), accelerations, '-o', markersize=4, linewidth=2, label='y1')

plt.xlabel("n_proc")
plt.ylabel("t_con / t_par")
plt.title("Ускорение")
plt.minorticks_on()
plt.grid()

os.chdir("TransportEquation/data")
current_dir = os.getcwd()
print("Save {}/acceleration.png".format(current_dir))
plt.savefig('acceleration.png')

plt.figure(figsize=[12, 5], dpi=100)
plt.plot(list(sizes), efficiencies, '-o', markersize=4, linewidth=2, label='y1')
plt.xlabel("n_proc")
plt.ylabel("t_con / (t_par * n_proc)")
plt.title("Эффективность")
plt.minorticks_on()
plt.grid()
current_dir = os.getcwd()
print("Save {}/efficiency.png".format(current_dir))
plt.savefig('efficiency.png')