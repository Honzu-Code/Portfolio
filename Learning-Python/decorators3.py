#nested decorators

import functools

def first(func):
    @functools.wraps(func)
    def show1(*args,**kwargs):
        print("In first = ",func(*args,**kwargs))
        return func(*args,**kwargs)
    return show1

def second(func):
    @functools.wraps(func)
    def show2(*args,**kwargs):
        print("In second = ",func(*args,**kwargs))
        return func(*args,**kwargs)
    return show2

@second
@first
def value():
    return 5

def third(times):
    def decorator_third(func):
        @functools.wraps(func)
        def show3(*args,**kwargs):
            for _ in range(times):
                print("Number: ", func(*args,**kwargs))
        return show3
    return decorator_third

@third(times=5)
def value2():
    return 9




value()
value2()
