#using metaclasses define the class

def f(obj):
    print("atr = ",obj.attr)

Example = type("Example",(),{
    "attr": 100,
    "attr_val": f
    })

x = Example()
print(x.attr)
x.attr_val()

#using normal classes
class Example2:
    attr = 100
    attr_val = f

y = Example2()
print(y.attr)
y.attr_val()

#every build in classes are type
print(type(str),type(int))

#we can't overwrite type metaclass new method
#def new(cls):
#    pass
#type.__new__ = new

#define custom metaclass
class Meta(type):
    def __init__(cls,name,bases,dct):
        cls.attr = 100

class X(metaclass=Meta):
    pass
class Y(metaclass=Meta):
    pass
class Z(metaclass=Meta):
    pass

print(X.attr,Y.attr,Z.attr)

#we can achieve the same result in other methods than using metaclasses

