#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

def loadplot(fnames, logx = False, logy = False, test = False, type = False, labelmaxavg = False, diffstyle=[]):
    fig, ax = plt.subplots(figsize=(8,4.5))
    

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
        lab = ''
        if test:
            
            if fname[0] == 'r':
                lab = "Rovnomerný test"
            elif fname[0] == 'b':
                lab = "Nevyvážený test"
            elif fname[0] == 'x':
                lab = "Zákerný test"
            elif fname[0] == 'p':
                lab = "Hlboký test"
        if type:
            if fname[2] == 's':
                lab = lab + "Štandardná implementácia"
            if fname[2] == 'n':
                lab = lab + "Naivná implementácia"

        
        


        xlabel = "Počet prvkov v halde"
        if labelmaxavg:
            ylabel = "Počet prvkov"

            if fname[-3:] == "avg":
                lab = lab + " - priemer"
            if fname[-3:] == "max":
                lab = lab + " - maximum"
        else:
            if fname[-3:] == "avg":
                ylabel = "Priemerný"
            if fname[-3:] == "max":
                ylabel = "Maximálny"
            ylabel += " počet prvkov"

        linestyle = '-'
        if(fname in diffstyle):
            linestyle = '--'
            
        ax.plot(x,y, label=lab, linestyle=linestyle)


        if logy:
            ax.set_yscale("log")
            ylabel = ylabel + " (logaritmická mierka)"

        if logx:
            ax.set_xscale("log")
            xlabel = xlabel + " (logaritmická mierka)"

        ax.set_xlabel(xlabel)
        ax.set_ylabel(ylabel)
        

    ax.legend()
    #box = ax.get_position()
    #ax.set_position([box.x0, box.y0 + box.height * 0.2,
    #             box.width, box.height * 0.80])

    #ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.13),
    #      fancybox=True, shadow=True, ncol=2)
        
    
    return ax


ax = loadplot(["r_stand_delete_avg", "b_stand_delete_avg"], logx = False, logy = False, test = True);
plt.title("Porovnanie rovnomerného a nevyváženého testu - štandardná implementácia")
plt.savefig("1.pdf", format='pdf')
plt.show()

ax = loadplot(["x_stand_delete_avg", "x_naive_delete_avg"], logx = False, logy = False, type = True);
plt.title("Porovnanie delete min naivnej a štandardnej implementácie v zákernom teste")
plt.savefig("2.pdf", format='pdf')
plt.show()

ax = loadplot(["p_stand_delete_avg", "p_stand_delete_max", "p_naive_delete_avg", "p_naive_delete_max"], logx = False, logy = True, type = True, labelmaxavg=True);
plt.title("Porovnanie maximálneho a priemerného počtu krokov\noperácie delete min naivnej a štandardnej implementácie v hlbokom teste")
plt.savefig("3.pdf", format='pdf')
plt.show()

ax = loadplot(["p_stand_decrease_avg", "p_stand_decrease_max", "p_naive_decrease_avg", "p_naive_decrease_max"], logx = False, logy = True, type = True, labelmaxavg=True, diffstyle = ["p_naive_decrease_max"]);
plt.title("Porovnanie maximálneho a priemerného počtu krokov\noperácie decrease naivnej a štandardnej implementácie v hlbokom teste")
plt.savefig("4.pdf", format='pdf')
plt.show()
