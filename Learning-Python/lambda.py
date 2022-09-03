import numpy as np

simple_list = [np.multiply(x,x) for x in range(10)]
print(simple_list)

first = lambda x : x + 1
print(first(5))

print((lambda x: x+1)(3))

#function lambda

second = lambda x, func : x + func(x)
print(second(5,lambda x : x+1))
