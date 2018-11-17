#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt


fig, ax = plt.subplots(figsize=(8, 16))

fnames = ["res_naive_0064_0064", "res_naive_0064_1024", "res_naive_0064_4096", "res_naive_0512_0512", "res_naive_4096_0064", "res_obl_0064_0064", "res_obl_0064_1024", "res_obl_0064_4096", "res_obl_0512_0512", "res_obl_4096_0064"]
label_offset = 4

for fname in fnames:
    multis = []
    x = []
    y = []
    file = open(fname)
    lines = file.read().splitlines()
    i = 0
    while i < len(lines):
        elements = float(lines[i].split(" ")[1])
        accesses = float(lines[i+1].split(" ")[1])
        misses = float(lines[i+2].split(" ")[1])
        missed_bytes = float(lines[i+3].split(" ")[1])
        
        
        x.append(np.sqrt(elements))
        y.append(misses / accesses * 2)
        i += 5

    file.close()
    label = ""
    linestyle = ""
    if fname[label_offset] == "n":
        label = "Naivná impl. "
        off = label_offset + 6
        linestyle = "-."
    elif fname[label_offset] == "o":
        label = "Rekurzívna impl. "
        off = label_offset + 4
        linestyle = "-"
    b = int(fname[off:off+4])
    m = int(fname[off+5:off+9])
    label += "B="+str(b)
    label += " M="+str(m)
    ax.plot(x,y, label=label, linestyle=linestyle)




ax.set_xscale("log", basex=2)
ax.set_yscale("log")
ax.set_xlabel("Veľkosť matice (logaritmická mierka)")
ax.set_ylabel("Počet načítaných blokov na výmenu dvoch prvkov")
        

box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
             box.width, box.height * 0.80])

ax.legend(loc='center',  bbox_to_anchor=(0.5, -0.13), #prop={'size': 5},
      fancybox=True, ncol=2)
#plt.xticks([])
plt.xticks(list(np.power(2, range(6,14))), list(np.power(2, range(6,18))))
plt.yticks([1, 0.1, 0.01],[1, 0.1, 0.01])
plt.title("Simulacia")
plt.savefig("sim.pdf", format='pdf')
plt.show()
