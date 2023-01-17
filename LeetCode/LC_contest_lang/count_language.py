from collections import Counter,defaultdict
f=open("weekly-contest-327_lang_P1.txt")
rank=defaultdict(list)
a=[]
for s in f.readlines():
    l,r=s.split(',')[0],int(s.split(',')[1][1:])
    a.append(l)
    rank[l].append(r)

c=Counter(a)
print('total=',sum(c.values()))
print(c)
#print(rank)

import matplotlib.pyplot as plt
lang=['cpp','java','python','golang']
rank['python']+=rank['python3']
#plt.hist([rank[s] for s in lang], 20, label=lang) #histtype='step'
plt.hist([rank[s] for s in lang], 1000, histtype='step', cumulative=True, label=lang)
plt.legend()
plt.show()

