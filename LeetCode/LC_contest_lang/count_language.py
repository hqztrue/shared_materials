from collections import Counter,defaultdict
import matplotlib.pyplot as plt
import numpy as np
def draw(name):
    f=open(name)
    rank=defaultdict(list)
    a=[]
    for s in f.readlines():
        l,r=s.split(',')[0],int(s.split(',')[1][1:])
        a.append(l)
        rank[l].append(r)
    f.close()
    
    c=Counter(a)
    print('total =',sum(c.values()))
    print(c)
    #print(rank)

    lang=['cpp','java','python','golang','javascript']
    rank['python']+=rank['python3']
    plt.figure()
    plt.title(name.split('.')[0])
    #plt.hist([rank[s] for s in lang], 20, label=lang) #histtype='step'
    plt.hist([rank[s] for s in lang], 1000, histtype='step', cumulative=True, label=lang)
    plt.xlabel('contest ranking')
    plt.ylabel('#users')
    plt.legend()
    
    #for s in lang: print(s,np.mean(rank[s]),np.std(rank[s]))

draw("weekly-contest-326_lang_P1.txt")
draw("weekly-contest-326_lang_P2.txt")
draw("weekly-contest-326_lang_P3.txt")
draw("weekly-contest-326_lang_P4.txt")
#draw("weekly-contest-326_lang_P1_US.txt")
#draw("weekly-contest-326_lang_P4_US.txt")
plt.show()
