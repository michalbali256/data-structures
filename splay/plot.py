#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

def loadplot(fnames, label_offset = 4, special = False, subset = False, logx = False):
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
            
            multis.append(yv/np.log2(xv))
            
            x.append(xv)
            y.append(yv)
            
        file.close()
        
        print(fname + " " + str(np.mean(multis)))    
        
        if special:
            lab = ''
            if fname[label_offset] == 's':
                lab = "Štandardná impl. "
            elif fname[label_offset] == 'o':
                lab = "Staticky optimálny strom "
            elif fname[label_offset] == 'n':
                lab = "Naivná impl. "
            if subset:
                lab = lab + fname[label_offset+2:]
            ax.plot(x,y, label=lab)
        else:
            ax.plot(x,y, label=fname[label_offset:])
        xlabel = "Počet prvkov v strome"
        if logx:
            ax.set_xscale("log")
            xlabel = xlabel + " (logaritmická mierka)"
        ax.set_xlabel(xlabel)
        ax.set_ylabel("Priemerná hĺbka vyhľadávaného prvku")
        
    ax.legend()
    box = ax.get_position()
    ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * 0.80])

    ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.13),
          fancybox=True, shadow=True, ncol=2)
        
    
    return ax

interactive = False
if len(sys.argv) > 1 and sys.argv[1] == '-i':
    interactive = True
############### 1. plot ################
case1 = ["res_s_T10","res_s_T100","res_s_T1000","res_s_T10000","res_s_T100000","res_s_T1000000"]

ax = loadplot(case1, 6, False)
plt.title("Štandardná implementácia splay stromu - podmnožinový test")
plt.savefig("1.pdf", format='pdf')
if interactive:
    plt.show()

############### 1. log plot ################
case1 = ["res_s_T10","res_s_T100","res_s_T1000","res_s_T10000","res_s_T100000","res_s_T1000000"]

ax = loadplot(case1, 6, False, logx = True)
plt.title("Štandardná implementácia splay stromu - podmnožinový test")

plt.savefig("1log.pdf", format='pdf')
if interactive:
    plt.show()

############### 2. plot ################
case2 = ["res_n_T10","res_n_T100","res_n_T1000","res_n_T10000","res_n_T100000","res_n_T1000000"]
ax = loadplot(case2,6)
plt.title("Naivná implementácia splay stromu - podmnožinový test")

plt.savefig("2.pdf", format='pdf')
if interactive:
    plt.show()


############### 3. plot ################
case3 = ["res_s_T100","res_s_T10000","res_s_T1000000","res_n_T100","res_n_T10000","res_n_T1000000"]
ax = loadplot(case3, 4, True, True)
plt.title("Porovnanie naivnej a štandardnej implementácie - podmnožinový test")

plt.savefig("3.pdf", format='pdf')
if interactive:
    plt.show()

############### 4. plot ################
case4 = ["res_s_uniform","res_o_uniform"]
ax = loadplot(case4, logx = True, special = True)
plt.title("Porovnanie štandardnej implementácie \n a staticky optimálneho stromu - uniformný test")

plt.savefig("4.pdf", format='pdf')
if interactive:
    plt.show()

############### 5. plot ################
case5 = ["res_s_nonuniform","res_o_nonuniform"]
ax = loadplot(case5, logx = True, special = True)
plt.title("Porovnanie štandardnej implementácie \n a staticky optimálneho stromu - neuniformný test")

plt.savefig("5.pdf", format='pdf')
if interactive:
    plt.show()

############### 6. plot ################
case6 = ["res_s_seq","res_n_seq"]
ax = loadplot(case6, special = True)
plt.title("Porovnanie štandardnej a naivnej implementácie - sekvenčný test")

plt.savefig("6.pdf", format='pdf')
if interactive:
    plt.show()

############### 7. plot ################
case7 = ["res_s_seq","res_o_seq"]
ax = loadplot(case7, special = True)
plt.title("Porovnanie štandardnej implementácie \n a staticky optimálneho stromu - sekvenčný test")

plt.savefig("7.pdf", format='pdf')
if interactive:
    plt.show()
    