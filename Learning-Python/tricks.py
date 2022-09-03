import timeit

#merge dictionairies
x = {'a': 1, 'b': 3}
y = {'b': 1, 'c': 3}

z = {**x,**y}
print("#1 ",z)


#test multiply flags at once
a,b,c = 0,0,1
if 1 in (a,b,c):
    print("True")
if a or b or c:
    print("True")
if any((a,b,c)):
    print("True")


#sort dict by value
xs = {'a': 4, 'b': 3, 'c': 2, 'd': 1}

print("#3 ",sorted(xs.items(), key=lambda x: x[1]))

#or

import operator
print("#3.1 ",sorted(xs.items(), key=operator.itemgetter(1)))

#function unpacking tuple and dictionairies
def myfunc(x, y, z):
    print("#4 ",x, y, z)

tuple_vec = (1, 0, 1)
dict_vec = {'x': 1, 'y': 0, 'z': 1}

myfunc(*tuple_vec)

myfunc(**dict_vec)

#measure time
print(timeit.timeit('"-".join(map(str, range(100)))',
                  number=10000))

#swap two values: 23 and 42
#instead use temporary variable we can use in python syntax like:
a = 23
b = 42
a,b = b,a
print(f"a = {a}, b = {b}")

#differenet between == and is:
#is return True if object have the same reference to object, == don't need this but need this

a = [1,2,3]
b = list(a)
print(f"is = {a is b}")
print(f"'==' = {a == b}")

#functions and run in array
def function_in_array(a,b):
    return a+b

array = [function_in_array]
print(array[0](2,3))








