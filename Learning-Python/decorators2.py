import functools
import math
import numpy as np
import time


def calculate_figure(func):
    @functools.wraps(func)
    def calculate(*args,**kwargs):
        start = time.perf_counter()
        value =  func(*args,**kwargs)
        end = time.perf_counter()
        run_time = end - start
        print(f"Function {func.__name__!r} executed in {run_time:.4f} seconds")
        return value
    return calculate

class decorators:
    def __init__(self,a,b):
        self.a = a
        self.b = b

    @calculate_figure
    def square(self):
        return np.multiply(self.a,self.a)

    @calculate_figure
    def rectangle(self):
        return np.multiply(self.a,self.b)

dec = decorators(2,3)

print("Box of square = ",dec.square())
print("Box of rectangle = ",dec.rectangle())


class Cube:
    def __init__(self,edge):
        self._edge = edge

    @property
    def edge(self):
        return self._edge

    @edge.setter
    def edge(self,value):
        if value > 0:
            self._edge = value
        else:
            raise ValueError("Edge have to be more than 0")

    @property
    def basearea(self):
        return np.multiply(self.edge,self.edge)

    def area_figure(self):
        return np.multiply(self.basearea,6)

    def volume(self):
        return np.power(self.edge,3)

    def diagonal_figure(self):
        return np.multiply(np.sqrt(3),self.edge)

    @classmethod
    def create(cls):
        return cls(2)

cube = Cube(10)
print(cube.edge)
cube.edge = 11
print(cube.edge)
print("Cube base area = ",cube.basearea)
print("Cube area = ",cube.area_figure())
print("Cube volume = ",cube.volume())
print("Cube diagonal_figure = ",cube.diagonal_figure())

cube2 = Cube.create()
print("Cube2 base area = ",cube2.basearea)
