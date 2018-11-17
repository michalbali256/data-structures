#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

def loadplot(fnames, label_offset = 4, special = False, logx = False):
    fig, ax = plt.subplots()
    

    for fname in fnames:
        multis = []
        x = []
        y = []
        file = open(fname)
        for line in file:
            spl = line.split(" ")
            
            xv = float(spl[0])
            yv = float(spl[1])
            
            x.append(xv)
            y.append(yv)

        file.close()  
        
        if special:
            lab = ''
            if fname[label_offset] == 'o':
                lab = "Cache oblivious implementácia"
            elif fname[label_offset] == 'n':
                lab = "Naivná implementácia"
            ax.plot(x,y, label=lab)
        else:
            ax.plot(x,y, label=fname[label_offset:])
        xlabel = "Veľkosť matice"
        if logx:
            ax.set_xscale("log", basex=2)
            plt.xticks(list(np.power(2, range(6,16))), list(np.power(2, range(6,18))))

            xlabel = xlabel + " (logaritmická mierka)"
        ax.set_xlabel(xlabel)
        ax.set_ylabel("Priemerný čas výmeny dvoch prvkov (ns)")
        
    ax.legend()
    #box = ax.get_position()
    #ax.set_position([box.x0, box.y0 + box.height * 0.2,
    #             box.width, box.height * 0.80])

    #ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.13),
    #      fancybox=True, shadow=True, ncol=2)
        
    
    return ax


ax = loadplot(["res_time_naive", "res_time_obl"], 9, logx = True, special=True);
plt.title("Meranie času")
plt.savefig("time.pdf", format='pdf')
plt.show()
