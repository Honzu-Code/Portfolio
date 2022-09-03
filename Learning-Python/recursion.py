from functools import lru_cache
import timeit
import numpy as np
import sys
print(sys.getrecursionlimit())



@lru_cache(maxsize=None)
def power(v,n):
    if n == 1:
        return v
    else:
        return np.multiply(v,power(v,n-1))

starttime = timeit.default_timer()
power(123456789,400)
endtime = timeit.default_timer()

print("Execute power recursion without numpy = ",endtime-starttime)

starttime = timeit.default_timer()
z = 123456789**400
endtime = timeit.default_timer()

print("Execute power (**) = ",endtime-starttime)
