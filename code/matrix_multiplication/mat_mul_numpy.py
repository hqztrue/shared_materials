import numpy as np
a=np.random.randn(5000,5000)
print(a.dtype)
import time
t=time.time()
#for i in range(10):
a.T.dot(a).shape
print(time.time()-t,'s=',a.sum())

b=a.astype(np.float32)
print(b.dtype)
t=time.time()
#for i in range(10):
b.T.dot(b).shape
print(time.time()-t,'s=',b.sum())
