#map is alternative for list comprehension and generators
import math
from itertools import starmap

def square(number):
    return number ** 2

numbers = [1,2,3,4,-5]
words = ["first","second","third"]

#for power
print("#1 ",list(map(square,numbers)))

#for converting to float
print("#2 ",list(map(float,numbers)))

#and we can also operate on strings (example counting len of every item)
print("#3 ",list(map(len,words)))

#if we have 2 lists map work only to the len shortest list
numbers2 = [1,2,3]
print("#4 ",list(map(pow,numbers,numbers2)))

#also we can use map with lambda functions (example add 2 two every numbers for list numbers)
print("#5 ",list(map(lambda x: x+2,numbers)))

#so we can filter every numbers if are positive to avoid value error :)
print("#6 ",list(map(math.sqrt,filter(lambda x: x >= 0,numbers))))

#also we can use reduce but its no much supporting (alternative is example for counting bytes is sum())
print("#7 ",list(starmap(pow,[(2,3),(3,4)])))



