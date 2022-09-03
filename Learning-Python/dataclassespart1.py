from dataclasses import dataclass , make_dataclass , field
from collections import namedtuple
from typing import Any , List

#example how to make dataclass width default values

@dataclass
class Triangles:
    width: int = 0
    height: int = 0

class trianglesRegular:
    def __init__(self,width,height):
        self.width = width
        self.height = height

#compare instances to itself (return True if have the same values,regular class return False)
triangle1 = Triangles(1,2)
triangle2 = Triangles(1,2)
print(f"compare 2 triangles (dataclasses) to itself {triangle1 == triangle2}")
triangle3 = trianglesRegular(1,2)
triangle4 = trianglesRegular(1,2)
print(f"compare 2 triangles (regular) to itself {triangle3 == triangle4}")

#because dataclass have implement instead you __init__, __repr__, __eq__

#we can create also tuple using namedtuple from collections and we can get value by .name

NamedTuple = namedtuple("NamedTuple",["width","height"])
exampletuple1 = NamedTuple(10,20)
print(f"example value from (exampletuple1) {exampletuple1.width}")

#compare this objects also return True if this objects have the same values

#its possible also make class using make_dataclass
Triangles2 = make_dataclass("Triangles2",["width","height"])
triangle5 = Triangles2("somethink",3)
print(f"Triangles2 dataclass: {triangle5}")

#this int or str or other type don't mean like in C or C++ its only this type (Python is dynamicly typing)
#so we can use Any if we don't know which type we will use in this place

@dataclass
class AnyClassTyping:
    name: Any
    number: Any = 10

AnyObject = AnyClassTyping("somethink")
print(f"AnyClassTyping: {AnyObject}")

#and also we can define our methods (its almost the same like in regular class)

@dataclass
class Triangles3:
    width: int = 0
    height: int = 0

    def area(self):
        return (self.width * self.height) / 2

triangle6 = Triangles3(1,3)
print(f"Area of triangle6 {triangle6} is equal: {triangle6.area()}")

#so we can use field if we want to prevent change mutable default arguments
widths = [1,2,3]
heights = [1,2,3]

def make_collection():
    return [Triangles3(w,h) for w in widths for h in heights]

@dataclass
class DeckTriangles:
    triangles: List[Triangles3] = field(default_factory=make_collection)

exampleDeckTraingles = DeckTriangles()
print(f"exampleDeckTraingles: {exampleDeckTraingles}")

#also we can use field with default for default value and also metadata={'key': value}

#if we want to make immutable dataclass we can use frozen as parameter for decorator and set this to True
#this work if we don't use lists or dictionaires

@dataclass(frozen=True)
class ImmutableSquare:
    edge: int

sampleSquare = ImmutableSquare(2)
#this will cause error that object is frozen
#sampleSquare.edge = 5
print(f"{sampleSquare}")

#inherence from dataclasses
#if we use in base class default parameters we have to use this parameters in the child classes
#and also child class overwrite value of field from base class

#in this example we inherence "what" from Figure

@dataclass
class Figure:
    name: str = "Unknown"
    what: str = "Figure"

@dataclass
class Octagon(Figure):
    name: str = "Octagon"
    size: int = 20

sampleOctagon = Octagon()

print(sampleOctagon)

#we can also optimizing speed of dataclasses using __slots__ +35%

@dataclass
class FasterClass:
    __slots__ = ["some","think"]
    some: int
    think: float

class SlowerClass:
    def __init__(self,some,think):
        self.some = some
        self.think = think

fasterclass = FasterClass(10,12.3)
slowerclass = SlowerClass(10,12.3)

print(dir(fasterclass),"\n")
print(slowerclass.__dict__)



