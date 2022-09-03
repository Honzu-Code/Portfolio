import numpy as np

a = np.arange(10).reshape(5,2)
print(f"a array = {a}")

b = np.array([1.2,1,2])
print(f"b array = {b}")

c = np.ones((2,3))
print(f"c array = {c}")
print(f"c-3 array = {c-3}")

#indexing examples

print('\n')
print(f"a = {a} \n ")
print(f"a[2] = {a[2]}")
print(f"a[2:] = {a[2:]}")
print(f"a[:2] = {a[:2]}")
print(f"a[2:3] = {a[2:3]}")
print(f"a[::3] = {a[::3]}")
print(f"a[::-1] = {a[::-1]}")

#we can combinate with , operator
print(f"a[2] = {a[2,1]}")
