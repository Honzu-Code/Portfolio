import sys

example_list = [x * 2 for x in range(10000)]
print(sys.getsizeof(example_list))
example_generator = (x ** 2 for x in range(10000))
print(sys.getsizeof(example_generator))

def multi_yield():
    first = "First"
    yield first
    second = "Second"
    yield second

objects = multi_yield()

print(next(objects))
print(next(objects))
#print(next(objects))

def is_palindrome(num):
    # Skip single-digit inputs
    if num // 10 == 0:
        return False
    temp = num
    reversed_num = 0
    while temp != 0:
        reversed_num = (reversed_num * 10) + (temp % 10)
        temp = temp // 10
    if num == reversed_num:
        return True
    else:
        return False


def infinite_palindromes():
    num = 0
    while True:
        if is_palindrome(num):
            i = (yield num)
            if i is not None:
                num = i
        num += 1


pal_gen = infinite_palindromes()
for i in pal_gen:
    print(i)
    digits = len(str(i))
    if digits == 5:
        pal_gen.throw(ValueError("We don't like large polidrones"))
    pal_gen.send(10 ** (digits))
