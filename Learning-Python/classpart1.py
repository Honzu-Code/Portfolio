#class example


class Car:
    def __init__(self,color,mileage):
        self.color = color
        self.mileage = mileage
    def __str__(self):
        return f"The {self.color} car has {self.mileage:,} miles"

car = Car("blue",20000)
car2 = Car("red",30000)

print(car)
print(car2)

class Dog:
    species = "Canis familiaris"

    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __str__(self):
        return f"{self.name} is {self.age} years old"

    def speak(self, sound):
        return f"{self.name} says {sound}"

class GoldenRetriever(Dog):
    def speak(self,sound="Bark"):
        return super().speak(sound)

class GoodDog(Dog):
    def __init__(self,name,age,good=True):
        super().__init__(name,age)
        self.good = good

dog1 = Dog("Latek",12)
print(dog1.speak("Arr"))
dog2 = GoldenRetriever("Krake",10)
print(dog2.speak())
dog3 = GoodDog("Atar",14,True)

print(isinstance(dog2,GoodDog))
print(issubclass(Dog,GoodDog))
print(dog3)
print(dog3.good)
