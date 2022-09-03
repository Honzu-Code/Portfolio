import functools

def extend():
    print("First1")
    def second():
        print("Second")
    def third():
        print("Third\n")
    second()
    third()

extend()

def extend2(num):
    print("First2")
    def second2():
        print("Second")
    def third2():
        print("Third\n")
    if num == 1:
        return second2
    else:
        return third2

next_example = extend2(2)
next_example()

def extend3(func):
    print("First3")
    def show():
        print("Second")
        func()
        print("Third\n")
    return show

def show():
    print("behind")

next_example2 = extend3(show)
next_example2()

#so now i can show how decorators work in python

@extend3
def new_show():
    print("Iam decorator")

@extend3
def new_show2():
    print("Iam decorator2")

new_show2()


#so if we add new wrapper with parameters we will have problem in function where will be execute so the solve problem with parameters is *args,**kwargs

def say_two_time(func):
    @functools.wraps(func)
    def inside(*args,**kwargs):
        func(*args,**kwargs)
        return func(*args,**kwargs)
    return inside

@say_two_time
def with_parameter(z):
    print(f"with {z}")
    return f"hi {z}"

@say_two_time
def without_parameter():
    print("without parameter")

print(with_parameter(10))
#without_parameter()


print(without_parameter.__name__)





