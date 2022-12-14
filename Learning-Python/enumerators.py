from enum import Enum

class Physics(Enum):
    LIGHT_SPEED = 299_792_458
    GRAVITATION = 6.67430e-11

print(Physics.LIGHT_SPEED)
print(Physics.GRAVITATION.value)

#we can use for loop for print all values
#also we can change values and use auto() for value we don't care about type

Vehicle = dict()
Vehicle["Speed"] = Physics.LIGHT_SPEED
print(Vehicle)

#we can use @unique if we don't want to have the same values in enum
#example enumerator with method property

class Planet(Enum):
     MERCURY = (3.303e+23, 2.4397e6)
     VENUS   = (4.869e+24, 6.0518e6)
     EARTH   = (5.976e+24, 6.37814e6)
     MARS    = (6.421e+23, 3.3972e6)
     JUPITER = (1.9e+27,   7.1492e7)
     SATURN  = (5.688e+26, 6.0268e7)
     URANUS  = (8.686e+25, 2.5559e7)
     NEPTUNE = (1.024e+26, 2.4746e7)
     def __init__(self, mass, radius):
         self.mass = mass       # in kilograms
         self.radius = radius   # in meters
     @property
     def surface_gravity(self):
         # universal gravitational constant  (m3 kg-1 s-2)
         G = 6.67300E-11
         return G * self.mass / (self.radius * self.radius)

print(Planet.MARS.surface_gravity)
