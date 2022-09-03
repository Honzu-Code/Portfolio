import enum

def multiply_list(numbers):
    match numbers:
        case []:
            return 1
        case [int(first) | float(first),*rest]:
            return first * multiply_list(rest)
        case _:
            wrong_type = numbers.__class__.__name__
            raise ValueError(f"Can only multiply lists, not {wrong_type!r}")

#multiply_list(["1","2"])
print(f"Multiply list: {multiply_list([1,3,4.4])}")


#fizbuzz program with match statement
def fizzbuzz(number):
    mod_3 = number % 3
    mod_5 = number % 5

    match (mod_3, mod_5):
        case (0, 0):
            return "fizzbuzz"
        case (0, _):
            return "fizz"
        case (_, 0):
            return "buzz"
        case _:
            return str(number)

print(f"Fizbuzz program: {fizzbuzz(11)}")

class Pythonista(str, enum.Enum):
    BDFL = "Guido"
    FLUFL = "Barry"

def greet(name):
    match name:
        case Pythonista.BDFL:
            return "Hi, Guido!"
        case _:
            return "Howdy, stranger!"

print(f"Greetings programmer: {greet('Guido')}")
